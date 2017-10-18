#include "qoreoutlinemodel.h"
#include "qoredocument.h"


namespace Qore {
namespace Internal {

QoreOutlineModel::QoreOutlineModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    m_rootItem = new QoreOutlineItem(0, "Name", 0, 0);
}

QoreOutlineModel::~QoreOutlineModel()
{
    delete m_rootItem;
}

QModelIndex QoreOutlineModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    QoreOutlineItem *parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<QoreOutlineItem*>(parent.internalPointer());

    QoreOutlineItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex QoreOutlineModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    QoreOutlineItem *childItem = static_cast<QoreOutlineItem*>(index.internalPointer());
    QoreOutlineItem *parentItem = childItem->parentItem();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int QoreOutlineModel::rowCount(const QModelIndex &parent) const
{
    QoreOutlineItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<QoreOutlineItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int QoreOutlineModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<QoreOutlineItem*>(parent.internalPointer())->columnCount();
    else
        return m_rootItem->columnCount();
}

QVariant QoreOutlineModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

//    if (role != Qt::DisplayRole)
//        return QVariant();

    QoreOutlineItem *item = static_cast<QoreOutlineItem*>(index.internalPointer());
    return item->data(role);
}

Qt::ItemFlags QoreOutlineModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant QoreOutlineModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_rootItem->data(section);

    return QVariant();
}

int QoreOutlineModel::lineForIndex(const QModelIndex &ix)
{
    QoreOutlineItem *item = static_cast<QoreOutlineItem*>(ix.internalPointer());
    return item->data(2).toInt();
}


void QoreOutlineModel::setRootItem(QoreOutlineItem *item)
{
    beginResetModel();

    m_rootItem->clear();
    delete m_rootItem;
    m_rootItem = item;

    endResetModel();
}

} // namespace Internal
} // namespace Qore
