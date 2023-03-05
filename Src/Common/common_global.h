#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COMMON_LIB)
#  define COMMON_EXPORT Q_DECL_EXPORT
# else
#  define COMMON_EXPORT Q_DECL_IMPORT
# endif
#else
# define COMMON_EXPORT
#endif

#define MYVTK_NAMESPACE_BEGIN namespace MyVtk {
#define MYVTK_NAMESPACE_END }
#define COMMON_NAMESPACE_BEGIN namespace Common {
#define COMMON_NAMESPACE_END }

MYVTK_NAMESPACE_BEGIN
COMMON_NAMESPACE_BEGIN



COMMON_NAMESPACE_END
MYVTK_NAMESPACE_END