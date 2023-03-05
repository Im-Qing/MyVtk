#pragma once

#include <QtCore/qglobal.h>
#include "../Common/common_global.h"

#ifndef BUILD_STATIC
# if defined(UTILS_LIB)
#  define UTILS_EXPORT Q_DECL_EXPORT
# else
#  define UTILS_EXPORT Q_DECL_IMPORT
# endif
#else
# define UTILS_EXPORT
#endif

#define UTILS_NAMESPACE_BEGIN namespace Utils {
#define UTILS_NAMESPACE_END }

MYVTK_NAMESPACE_BEGIN
UTILS_NAMESPACE_BEGIN



UTILS_NAMESPACE_END
MYVTK_NAMESPACE_END