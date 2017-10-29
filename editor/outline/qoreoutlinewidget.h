#pragma once

#include <outline/qoreoutlinetreeview.h>
#include <texteditor/ioutlinewidget.h>

namespace Qore {
namespace Internal {

class QoreDocument;
class QoreOutlineModel;
class QoreEditor;

class QoreOutlineWidget : public TextEditor::IOutlineWidget
{
    Q_OBJECT

public:
    QoreOutlineWidget(QoreEditor * editor, QWidget *parent = 0);

    void setDocument(QoreDocument *doc);

    // IOutlineWidget
    virtual QList<QAction*> filterMenuActions() const override;
    virtual void setCursorSynchronization(bool syncWithCursor) override;

private:
    bool m_enableCursorSync = true;

    QoreEditor *m_editor;
    QoreOutlineTreeView *m_view;
    QoreDocument *m_doc;
    QoreOutlineModel *m_model;

private slots:
    void reloadOutline();
    void editorGoToLine(const QModelIndex &index);
};

} // namespace Internal
} // namespace Qore
