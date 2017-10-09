#pragma once

#include <QtGlobal>

#if defined(QORE_LIBRARY)
#  define QORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QORESHARED_EXPORT Q_DECL_IMPORT
#endif
