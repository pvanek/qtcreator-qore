#pragma once

#include <texteditor/texteditor.h>

namespace Qore {
namespace Internal {

class QoreEditorFactory : public TextEditor::TextEditorFactory
{
    Q_OBJECT

public:
    QoreEditorFactory();

    Core::IEditor *createEditor() override;
    static void decorateEditor(TextEditor::TextEditorWidget *editor);
};

} // namespace Internal
} // namespace Qore

