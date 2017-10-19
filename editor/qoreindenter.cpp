#include "qoreindenter.h"
#include <texteditor/tabsettings.h>

#include <QTextDocument>

namespace Qore {
namespace Internal {

QoreIndenter::QoreIndenter()
{
    m_electricChars << '{' << '}';
}

QoreIndenter::~QoreIndenter()
{
}


bool QoreIndenter::isElectricCharacter(const QChar &ch) const
{
    return m_electricChars.contains(ch);
}

void QoreIndenter::indentBlock(QTextDocument *doc,
                               const QTextBlock &block,
                               const QChar &typedChar,
                               const TextEditor::TabSettings &tabSettings)
{
    Q_UNUSED(doc);
    int indent = indentFor(block, tabSettings);
    if (typedChar == QLatin1Char('}'))
        indent -= tabSettings.m_indentSize;
    tabSettings.indentLine(block, qMax(0, indent));
}

int QoreIndenter::indentFor(const QTextBlock &block,
                            const TextEditor::TabSettings &tabSettings)
{
    QTextBlock previous = block.previous();
    if (!previous.isValid())
        return 0;

    QString previousText = previous.text();
    while (previousText.trimmed().isEmpty()) {
        previous = previous.previous();
        if (!previous.isValid())
            return 0;
        previousText = previous.text();
    }

    int indent = tabSettings.indentationColumn(previousText);

    int adjust = previousText.count(QLatin1Char('{')) - previousText.count(QLatin1Char('}'));
    adjust *= tabSettings.m_indentSize;

    return qMax(0, indent + adjust);
}

} // namespace Internal
} // namespace Qore
