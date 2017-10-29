#include "qoreoutlinefactory.h"
#include "qoreoutlinewidget.h"
#include "qoreeditor.h"
#include "qoredocument.h"

#include <QtDebug>

namespace Qore {
namespace Internal {

bool QoreOutlineFactory::supportsEditor(Core::IEditor *editor) const
{
    if (qobject_cast<QoreEditor*>(editor))
        return true;
    return false;
}

TextEditor::IOutlineWidget *QoreOutlineFactory::createWidget(Core::IEditor *editor)
{
    QoreEditor *e = qobject_cast<QoreEditor*>(editor);
    Q_ASSERT(e);

    QoreDocument *d = qobject_cast<QoreDocument*>(e->document());
    Q_ASSERT(d);

    QoreOutlineWidget *widget = new QoreOutlineWidget(e);
    widget->setDocument(d);
    return widget;
}

} // namespace Internal
} // namespace Qore
