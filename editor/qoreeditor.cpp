#include "qoreeditor.h"
#include "qoreconstants.h"

namespace Qore {
namespace Internal {

QoreEditor::QoreEditor()
{
    addContext(Qore::Constants::LANGUAGE_ID);
}

} // namespace Internal
} // namespace Qore
