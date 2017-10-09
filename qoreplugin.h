#pragma once

#include "qore_global.h"

#include <extensionsystem/iplugin.h>

namespace Qore {
namespace Internal {

class QorePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "Qore.json")

public:
    QorePlugin();
    ~QorePlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:
    void triggerWikiAction();
    void triggerDevelopmentAction();
};

} // namespace Internal
} // namespace Qore
