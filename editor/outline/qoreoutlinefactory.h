#pragma once

#include <texteditor/outlinefactory.h>

namespace Qore {
namespace Internal {

class QoreOutlineFactory : public TextEditor::IOutlineWidgetFactory
{
    Q_OBJECT
public:
    bool supportsEditor(Core::IEditor *editor) const;
    TextEditor::IOutlineWidget *createWidget(Core::IEditor *editor);
};

} // namespace Internal
} // namespace Qore
