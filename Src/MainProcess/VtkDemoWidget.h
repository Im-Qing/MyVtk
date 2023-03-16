#pragma once

#include <QWidget>
#include <QDebug>
#include <QListWidget>

#include "ui_VtkDemoWidget.h"

//vtk
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
#include "vtkLine.h"
#include "vtkPointData.h"
#include "vtkCellData.h"
#include "vtkPolygon.h"
#include "vtkTriangle.h"
#include "vtkCamera.h"
#include "vtkPNGWriter.h"
#include "vtkJPEGReader.h"
#include "vtkImageViewer2.h"
#include "vtkStripper.h"
#include "vtkMarchingCubes.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2);     // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);    // Build with vtkTextActor
VTK_MODULE_INIT(vtkRenderingContextOpenGL2)

//itk
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkGDCMImageIO.h"
#include "itkImageToVTKImageFilter.h"
#include "itkImageSeriesReader.h"		//用于读取图像序列
#include "itkGDCMSeriesFileNames.h"		//用于读取序列文件名

class VtkDemoWidget : public QWidget
{
	Q_OBJECT

public:
	VtkDemoWidget(QWidget *parent = Q_NULLPTR);
	~VtkDemoWidget();
public slots:
	void onListItemClicked(QListWidgetItem* item);
private:
	Ui::VtkDemoWidget ui;
	QVTKOpenGLWidget* m_pVTKOpenGLWidget{nullptr};
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_pRenderwindow{nullptr};
	vtkSmartPointer<vtkRenderer> m_pRenderer{nullptr};
};
