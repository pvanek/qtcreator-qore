#include "qorecompletionassistprovider.h"
#include "qoreconstants.h"


namespace Qore {
namespace Internal {


QoreCompletionAssist::QoreCompletionAssist() :
    KeywordsCompletionAssistProcessor(TextEditor::Keywords())
{
    setSnippetGroup(Qore::Constants::SNIPPETSGROUPID);
}

TextEditor::IAssistProposal *QoreCompletionAssist::perform(const TextEditor::AssistInterface *interface)
{
    // TODO/FIXME: real completion
    return KeywordsCompletionAssistProcessor::perform(interface);
}


TextEditor::IAssistProcessor *QoreCompletionAssistProvider::createProcessor() const
{
    return new QoreCompletionAssist;
}

int QoreCompletionAssistProvider::activationCharSequenceLength() const
{
    return 1;
}


} // namespace Internal
} // namespace Qore
