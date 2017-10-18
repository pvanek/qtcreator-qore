#pragma once

#include <texteditor/texteditor.h>


namespace Qore {
namespace Internal {

class QoreEditor : public TextEditor::BaseTextEditor
{
    Q_OBJECT
public:
    QoreEditor();
};

} // namespace Internal
} // namespace Qore
