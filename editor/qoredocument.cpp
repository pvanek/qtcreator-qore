#include "qoredocument.h"

#include "qoreconstants.h"

#include "qoreindenter.h"

#include <qore/Qore.h>

#include <QtDebug>
#include <QDateTime>
#include <QTextDocument>
#include <QIcon>

namespace Qore {
namespace Internal {

// code-block.svg  code-class.svg  code-context.svg  code-function.svg  code-typedef.svg  code-variable.svg
std::map<int, QString> icon_map = {
    {1, "code-class"},
    {3, "code-variable"}, // TODO/FIXME
    {4, "code-function"},
    {8, "code-context"}
};

std::map<int, QString> type_map = {
    {1, "Class"},
    {3, "Constant"},
    {4, "Function"},
    {8, "Namespace"}
};
/*
kinds[1] = "Class"; // ADK_Class
kinds[3] = "Constant"; // ADK_Constant
kinds[4] = "Function"; // ADK_Function
kinds[8] = "Namespace"; // ADK_Namespace
*/


QoreOutlineItem::QoreOutlineItem(int itemType,
                                 const QString &itemText,
                                 int row,
                                 QoreOutlineItem *parent)
{
    m_parentItem = parent;
    m_itemType = itemType;
    m_itemText = itemText;
    m_row = row;
}

QoreOutlineItem::~QoreOutlineItem()
{
    clear();
}

void QoreOutlineItem::appendChild(QoreOutlineItem *item)
{
    m_childItems.append(item);
}

QoreOutlineItem *QoreOutlineItem::child(int row)
{
    return m_childItems.value(row);
}

int QoreOutlineItem::childCount() const
{
    return m_childItems.count();
}

int QoreOutlineItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<QoreOutlineItem*>(this));

    return 0;
}

int QoreOutlineItem::columnCount() const
{
    return 1;
}

QVariant QoreOutlineItem::data(int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        return m_itemText;
    case Qt::ToolTipRole:
        return type_map[m_itemType];
    case Qt::DecorationRole:
        return QIcon::fromTheme(icon_map[m_itemType],
                                QIcon(QString(":/images/%1.png").arg(icon_map[m_itemType]))
                               );
    case Qt::UserRole:
        return m_row;
    default:
        return QVariant();
    }
}

QoreOutlineItem *QoreOutlineItem::parentItem()
{
    return m_parentItem;
}

void QoreOutlineItem::clear()
{
    qDeleteAll(m_childItems);
}



QoreDocument::QoreDocument()
    : TextEditor::TextDocument(),
      m_currentRevision(-1)
{
    setId(Qore::Constants::EDITOR_ID);
    setMimeType(Qore::Constants::MIMETYPE);
    // TODO setIndenter(new QoreIndenter);

    m_timer.setInterval(100000);
    connect(&m_timer, &QTimer::timeout,
            this, &QoreDocument::m_timer_timeout);
}

void QoreDocument::m_timer_timeout()
{
    if (isModified())
        return;

    int rev = document()->revision();
    if (rev != m_currentRevision)
    {
        m_timer.stop();
        m_currentRevision = rev;
        emit outlineAboutToChange();
    }
}

QoreOutlineItem* QoreDocument::outline()
{
    qDebug() << "QoreDocument::outline()" << QDateTime::currentDateTime();

    QoreOutlineItem *root = new QoreOutlineItem(0, "Root", 0);

    const char* code = "%new-style\n"
            "%requires astparser\n"
            "AstParser p();\n"
            "our string filecontent;\n"
            "auto tree = p.parseString(filecontent);\n"
            "our auto nodes = exists tree ? tree.getNodesInfo() : list();\n";

    ExceptionSink xsink, wsink;

    // creates and manages a QoreProgram object
    QoreProgramHelper pgm(PO_DEFAULT, xsink);
    // parses a file with all warnings enabled
    pgm->parse(code, "filecontent", &xsink, &wsink, QP_WARN_ALL);

    pgm->setGlobalVarValue("filecontent", new QoreStringNode(plainText().toUtf8().data()), &xsink);
    // display any warnings immediately
    wsink.handleWarnings();
    // execute program if there were no parse exceptions
    if (!xsink)
        pgm->run(&xsink);

    xsink.handleExceptions();
    xsink.handleWarnings();

    bool check;

    AbstractQoreNode* nodes = pgm->getGlobalVariableValue("nodes", check);
    if (nodes->getType() != NT_LIST)
    {
            qDebug() << "NODES IS NOT A LIST!" << nodes->getTypeName();
    }
    else
    {
        QoreListNode *l = reinterpret_cast<QoreListNode*>(nodes);
        addListToItem(root, l);
    }

    m_timer.start();
    return root;
}

void QoreDocument::addListToItem(QoreOutlineItem *item, QoreListNode *list)
{
    // https://gist.github.com/omusil24/97769ae831478aac57880a84331424ec

    for (qore_size_t i = 0; i < list->size(); ++i)
    {
        AbstractQoreNode *n = list->retrieve_entry(i);
        if (n->getType() == NT_HASH)
        {
            QoreHashNode *h = reinterpret_cast<QoreHashNode*>(n);
            bool check;
            AbstractQoreNode *val = h->getKeyValueExistence("nodetype", check);
            if (!check)
            {
                continue;
            }

            if (val->getAsInt() != 1) // || val->getAsInt() != 4) // ANT_Declaration
            {
                //qDebug() << "not a declaration" << val->getAsInt();
                continue;
            }

            int64 kind = h->getKeyValue("kind")->getAsInt();
            if (type_map.count(kind))
            {
                QoreHashNode *namenode = reinterpret_cast<QoreHashNode*>(h->getKeyValue("name"));

                QString name = QString::fromUtf8(QoreStringValueHelper(namenode->getKeyValue("name"))->getBuffer());
                QoreHashNode *locnode = reinterpret_cast<QoreHashNode*>(namenode->getKeyValue("loc"));
                int line = locnode->getKeyValue("start_line")->getAsInt();

                QoreOutlineItem *new_item = new QoreOutlineItem(kind, name, line, item);
                item->appendChild(new_item);
                //qDebug() << "new_item:" << name << kind << line;

                AbstractQoreNode *l = h->getKeyValueExistence("declarations", check);
                if (!check)
                {
                    continue;
                }
                QoreListNode *new_list = reinterpret_cast<QoreListNode*>(l);

                addListToItem(new_item, new_list);
            }
            else
            {
                //qDebug() << "ignored kind: " << kind;
                continue;
            }
        }
        else if (n->getType() == NT_LIST)
        {
            addListToItem(item, reinterpret_cast<QoreListNode*>(n));
        }
        else
        {
            qDebug() << "QoreOutlineModel::addListToItem: unknown node to build a tree: " << n->getTypeName();
        }
    }
}

} // namespace Internal
} // namespace Qore
