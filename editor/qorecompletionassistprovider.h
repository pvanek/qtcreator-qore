#pragma once

#include <texteditor/codeassist/completionassistprovider.h>
#include <texteditor/codeassist/keywordscompletionassist.h>

namespace Qore {
namespace Internal {

class QoreCompletionAssist : public TextEditor::KeywordsCompletionAssistProcessor
{
public:
    QoreCompletionAssist();

    // IAssistProcessor interface
    TextEditor::IAssistProposal *perform(const TextEditor::AssistInterface *interface) override;
};


class QoreCompletionAssistProvider : public TextEditor::CompletionAssistProvider
{
    Q_OBJECT

public:
    TextEditor::IAssistProcessor *createProcessor() const override;

    int activationCharSequenceLength() const override;
};

} // namespace Internal
} // namespace Qore
