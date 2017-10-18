#pragma once

#include <QAbstractItemModel>

namespace Qore {
namespace Internal {

class QoreOutlineItem;


class QoreOutlineModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit QoreOutlineModel(QObject *parent);
    ~QoreOutlineModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int lineForIndex(const QModelIndex &ix);

    void setRootItem(QoreOutlineItem *item);
signals:

public slots:

private:
    QoreOutlineItem* m_rootItem;
};

} // namespace Internal
} // namespace Qore
