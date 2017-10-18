#pragma once

#include <texteditor/textdocument.h>

#include <QTimer>

class QoreListNode;

namespace Qore {
namespace Internal {


class QoreOutlineItem
{
public:
    explicit QoreOutlineItem(int itemType,
                             const QString &itemText,
                             int row,
                             QoreOutlineItem *parentItem = 0);
    ~QoreOutlineItem();

    void appendChild(QoreOutlineItem *child);

    QoreOutlineItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    QoreOutlineItem *parentItem();

    void clear();

private:
    QList<QoreOutlineItem*> m_childItems;

    int m_itemType;
    QString m_itemText;
    int m_row;

    QoreOutlineItem *m_parentItem;
};


class QoreDocument : public TextEditor::TextDocument
{
    Q_OBJECT

public:
    explicit QoreDocument();

    QoreOutlineItem* outline();

signals:
    void outlineAboutToChange();

private:
    QTimer m_timer;
    int m_currentRevision;

    void addListToItem(QoreOutlineItem *item, QoreListNode *list);

private slots:
    void m_timer_timeout();
};

} // namespace Internal
} // namespace Qore
