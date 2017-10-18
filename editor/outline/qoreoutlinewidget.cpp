#include "qoreoutlinewidget.h"
#include "qoredocument.h"
#include "qoreoutlinemodel.h"
#include <QVBoxLayout>
#include <coreplugin/find/itemviewfind.h>

namespace Qore {
namespace Internal {

QoreOutlineWidget::QoreOutlineWidget(QWidget *parent)
    : TextEditor::IOutlineWidget(parent),
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
}


} // namespace Internal
} // namespace Qore
