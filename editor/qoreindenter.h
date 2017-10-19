#pragma once

#include <texteditor/indenter.h>

namespace Qore {
namespace Internal {

class QoreIndenter : public TextEditor::Indenter
{
public:
    QoreIndenter();
    ~QoreIndenter() override;

    bool isElectricCharacter(const QChar &ch) const override;

    void indentBlock(QTextDocument *doc,
                     const QTextBlock &block,
                     const QChar &typedChar,
                     const TextEditor::TabSettings &tabSettings) override;

    int indentFor(const QTextBlock &block, const TextEditor::TabSettings &tabSettings) override;

private:
    QList<QChar> m_electricChars;
};

} // namespace Internal
} // namespace Qore
