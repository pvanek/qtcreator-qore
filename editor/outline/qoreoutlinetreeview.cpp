#include "qoreoutlinetreeview.h"
#include <utils/annotateditemdelegate.h>
#include <QMenu>

namespace Qore {
namespace Internal {

QoreOutlineTreeView::QoreOutlineTreeView(QWidget *parent) :
    Utils::NavigationTreeView(parent)
{
    setExpandsOnDoubleClick(false);

    setRootIsDecorated(false);
}

void QoreOutlineTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    if (!event)
        return;

    QMenu contextMenu;

    connect(contextMenu.addAction(tr("Expand All")), &QAction::triggered,
            this, &QoreOutlineTreeView::expandAll);
    connect(contextMenu.addAction(tr("Collapse All")), &QAction::triggered,
            this, &QoreOutlineTreeView::collapseAllExceptRoot);

    contextMenu.exec(event->globalPos());

    event->accept();
}

void QoreOutlineTreeView::collapseAllExceptRoot()
{
    if (!model())
        return;
    const QModelIndex rootElementIndex = model()->index(0, 0, rootIndex());
    int rowCount = model()->rowCount(rootElementIndex);
    for (int i = 0; i < rowCount; ++i) {
        collapse(model()->index(i, 0, rootElementIndex));
    }
}

} // namespace Internal
} // namespace Qore
