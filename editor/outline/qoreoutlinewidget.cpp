#include "qoreoutlinewidget.h"
#include "qoredocument.h"
#include "qoreeditor.h"
#include "qoreoutlinemodel.h"
#include <QVBoxLayout>
#include <coreplugin/find/itemviewfind.h>

namespace Qore {
namespace Internal {

QoreOutlineWidget::QoreOutlineWidget(QoreEditor * editor, QWidget *parent)
    : TextEditor::IOutlineWidget(parent),
      m_editor(editor),
      m_view(new QoreOutlineTreeView(this)),
      m_doc(0),
      m_model(new QoreOutlineModel(this))
{
    setFocusProxy(m_view);

    m_view->setModel(m_model);

    QVBoxLayout *layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(Core::ItemViewFind::createSearchableWrapper(m_view));
    setLayout(layout);

    connect(m_view, &QoreOutlineTreeView::activated,
            this, &QoreOutlineWidget::editorGoToLine);
}

QList<QAction*> QoreOutlineWidget::filterMenuActions() const
{
    return {};
}

void QoreOutlineWidget::setCursorSynchronization(bool syncWithCursor)
{
    m_enableCursorSync = syncWithCursor;
//    m_editor->updateOutlineIndexNow();
}

void QoreOutlineWidget::setDocument(QoreDocument *doc)
{
    m_doc = doc;
    connect(m_doc, &QoreDocument::outlineAboutToChange,
            this, &QoreOutlineWidget::reloadOutline);

    reloadOutline();
}

void QoreOutlineWidget::reloadOutline()
{
    m_model->setRootItem(m_doc->outline());
    m_view->expandAll();
}

void QoreOutlineWidget::editorGoToLine(const QModelIndex &index)
{
    int row = m_model->data(index, Qt::UserRole).toInt();
    m_editor->gotoLine(row);
}


} // namespace Internal
} // namespace Qore
