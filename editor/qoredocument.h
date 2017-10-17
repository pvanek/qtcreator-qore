#pragma once

#include <texteditor/textdocument.h>


namespace Qore {
namespace Internal {


class QoreDocument : public TextEditor::TextDocument
{
    Q_OBJECT

public:
    explicit QoreDocument();
};

} // namespace Internal
} // namespace Qore
