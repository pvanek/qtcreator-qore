#include "qoreeditorfactory.h"

#include "../qoreconstants.h"
#include "../qoreplugin.h"

#include "qoredocument.h"

#include <texteditor/texteditoractionhandler.h>
#include <texteditor/texteditorconstants.h>
#include <texteditor/textdocument.h>
#include <utils/qtcassert.h>

using namespace TextEditor;
using namespace Utils;

namespace Qore {
namespace Internal {

QoreEditorFactory::QoreEditorFactory()
{
    setId(Qore::Constants::EDITOR_ID);

    setDisplayName(tr(Qore::Constants::EDITOR_DISPLAY_NAME));

    addMimeType(QLatin1String(Qore::Constants::MIMETYPE));

    setEditorActionHandlers(TextEditorActionHandler::Format
                            | TextEditorActionHandler::UnCommentSelection
                            | TextEditorActionHandler::UnCollapseAll);

    setEditorWidgetCreator([]{
        auto result = new TextEditorWidget();
        result->setLanguageSettingsId(Qore::Constants::LANGUAGE_ID);
        return result;
    });
    setDocumentCreator([]() {
        return new QoreDocument;
    });
//    setIndenterCreator([]() {
//        return new QoreIndenter;
//    });
    setUseGenericHighlighter(true);
//    setSyntaxHighlighterCreator([]() {
//        return new QoreHighlighter;
//    });
    setCommentDefinition(CommentDefinition("#", "/*", "*/"));
    setParenthesesMatchingEnabled(true);
    setMarksVisible(false);
    setCodeFoldingSupported(true);
    setMarksVisible(true);
}

Core::IEditor *QoreEditorFactory::createEditor()
{
    return TextEditorFactory::createEditor();
}

void QoreEditorFactory::decorateEditor(TextEditorWidget *editor)
{
//    editor->textDocument()->setSyntaxHighlighter(new QoreHighlighter());
//    editor->textDocument()->setIndenter(new QoreIndenter());
}

} // namespace Internal
} // namespace Qore

