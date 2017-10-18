#pragma once

#include <utils/navigationtreeview.h>

namespace Qore {
namespace Internal {


class QoreOutlineTreeView : public Utils::NavigationTreeView
{
    Q_OBJECT
public:
    explicit QoreOutlineTreeView(QWidget *parent = 0);

    void contextMenuEvent(QContextMenuEvent *event);

private:
    void collapseAllExceptRoot();
};

} // namespace Internal
} // namespace Qore
