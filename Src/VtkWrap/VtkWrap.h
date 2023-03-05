#pragma once

#include "vtkwrap_global.h"

#include "QVTKOpenGLWidget.h"
#include "vtkChartXY.h"
#include "vtkContextScene.h"
#include "vtkContextView.h"
#include "vtkFloatArray.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkMath.h"
#include "vtkNew.h"
#include "vtkPlot.h"
#include "vtkQtTableView.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkTable.h"
#include "vtkTimerLog.h"
#include "vtkNamedColors.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2);     // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);    // Build with vtkTextActor
VTK_MODULE_INIT(vtkRenderingContextOpenGL2)

MYVTK_NAMESPACE_BEGIN
VTKWRAP_NAMESPACE_BEGIN

class VTKWRAP_EXPORT VtkWrap
{
public:
	VtkWrap();
	QVTKOpenGLWidget* test();
private:
	
};

VTKWRAP_NAMESPACE_END
MYVTK_NAMESPACE_END
