#include "qoreplugin.h"
#include "qoreconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>
#include <QUrl>
#include <QDesktopServices>

namespace Qore {
namespace Internal {

QorePlugin::QorePlugin()
{
    // Create your members
}

QorePlugin::~QorePlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool QorePlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("Qore Language"));

    auto action = new QAction(tr("Qore Wiki"), this);
    Core::Command *cmd = Core::ActionManager::registerAction(action, Constants::WIKI_ACTION_ID,
                                                             Core::Context(Core::Constants::C_GLOBAL));
    menu->addAction(cmd);
    //cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
    connect(action, &QAction::triggered, this, &QorePlugin::triggerWikiAction);

    action = new QAction(tr("Qore Development"), this);
    cmd = Core::ActionManager::registerAction(action, Constants::DEVELOPMENT_ACTION_ID,
                                              Core::Context(Core::Constants::C_GLOBAL));
    connect(action, &QAction::triggered, this, &QorePlugin::triggerDevelopmentAction);
    menu->addAction(cmd);

    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    return true;
}

void QorePlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag QorePlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void QorePlugin::triggerWikiAction()
{
    QDesktopServices::openUrl(QUrl("https://github.com/qorelanguage/qore/wiki"));
}

void QorePlugin::triggerDevelopmentAction()
{
    QDesktopServices::openUrl(QUrl("https://github.com/qorelanguage/qore"));
}

} // namespace Internal
} // namespace Qore
