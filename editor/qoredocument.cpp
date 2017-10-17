#include "qoredocument.h"

#include "../qoreconstants.h"

namespace Qore {
namespace Internal {


QoreDocument::QoreDocument()
    : TextEditor::TextDocument()
{
    setId(Qore::Constants::EDITOR_ID);
    setMimeType(Qore::Constants::MIMETYPE);

    //setSyntaxHighlighter(new QoreHighlighter());
    //setIndenter(new CppTools::QoreStyleIndenter);
}

} // namespace Internal
} // namespace Qore
