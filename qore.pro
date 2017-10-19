DEFINES += QORE_LIBRARY

# Qore files
RESOURCES += qore.qrc

SOURCES += qoreplugin.cpp \
        editor/qoreeditorfactory.cpp \
        editor/qoredocument.cpp \
    editor/outline/qoreoutlinefactory.cpp \
    editor/outline/qoreoutlinewidget.cpp \
    editor/qoreeditor.cpp \
    editor/outline/qoreoutlinetreeview.cpp \
    editor/outline/qoreoutlinemodel.cpp \
    editor/qorecompletionassistprovider.cpp

HEADERS += qoreplugin.h \
        qore_global.h \
        qoreconstants.h \
        editor/qoreeditorfactory.h \
        editor/qoredocument.h \
    editor/outline/qoreoutlinefactory.h \
    editor/outline/qoreoutlinewidget.h \
    editor/qoreeditor.h \
    editor/outline/qoreoutlinetreeview.h \
    editor/outline/qoreoutlinemodel.h \
    editor/qorecompletionassistprovider.h

DISTFILES += Qore.json.in \
        editor/generic-highlighter/qore.xml \
        editor/snippets/qore.xml \
        wizards/qore-class/wizard.json \
        wizards/qore-class/file.qc \
        wizards/qore-script/file.q \
        wizards/qore-script/wizard.json \
        wizards/qore-qtest/file.qtest \
        wizards/qore-qtest/wizard.json \
        wizards/qore-module/file.qm \
        wizards/qore-module/wizard.json

INCLUDEPATH += $$PWD\
        editor \
        editor/outline

LIBS += -lqore

# Qt Creator linking

## Either set the IDE_SOURCE_TREE when running qmake,
## or set the QTC_SOURCE environment variable, to override the default setting
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = $$(QTC_SOURCE)
isEmpty(IDE_SOURCE_TREE): IDE_SOURCE_TREE = "/export/home/pvanek/src/ide/qt-creator"

## Either set the IDE_BUILD_TREE when running qmake,
## or set the QTC_BUILD environment variable, to override the default setting
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE): IDE_BUILD_TREE = "/export/home/pvanek/src/ide/build-qtcreator-qt5-Debug"

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on OS X
USE_USER_DESTDIR = yes

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = Qore
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin projectexplorer texteditor

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)


# copy static files
syntaxfile.commands = $(COPY_DIR) $$PWD/editor/generic-highlighter/qore.xml $$IDE_BUILD_TREE/share/qtcreator/generic-highlighter
export(syntaxfile.commands)

snippetfile.commands = $(COPY_DIR) $$PWD/editor/snippets/qore.xml $$IDE_BUILD_TREE/share/qtcreator/snippets
export(snippetfile.commands)

wizards.commands = $(COPY_DIR) $$PWD/wizards/ $$IDE_BUILD_TREE/share/qtcreator/templates/
export(wizards.commands)

first.depends = $(first) syntaxfile snippetfile wizards
export(first.depends)

QMAKE_EXTRA_TARGETS += first syntaxfile snippetfile wizards

