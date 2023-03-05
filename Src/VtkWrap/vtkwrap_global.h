#pragma once

#include <QtCore/qglobal.h>
#include "../Common/common_global.h"

#ifndef BUILD_STATIC
# if defined(VTKWRAP_LIB)
#  define VTKWRAP_EXPORT Q_DECL_EXPORT
# else
#  define VTKWRAP_EXPORT Q_DECL_IMPORT
# endif
#else
# define VTKWRAP_EXPORT
#endif

#define VTKWRAP_NAMESPACE_BEGIN namespace VtkWrap {
#define VTKWRAP_NAMESPACE_END }

MYVTK_NAMESPACE_BEGIN
VTKWRAP_NAMESPACE_BEGIN



VTKWRAP_NAMESPACE_END
MYVTK_NAMESPACE_END