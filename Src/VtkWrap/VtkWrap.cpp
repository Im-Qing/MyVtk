#include "VtkWrap.h"

MYVTK_NAMESPACE_BEGIN
VTKWRAP_NAMESPACE_BEGIN

VtkWrap::VtkWrap()
{
}

QVTKOpenGLWidget* VtkWrap::test()
{
	vtkNew<vtkNamedColors> colors;
	vtkNew<vtkSphereSource> shereSource;

	vtkNew<vtkPolyDataMapper> shereMapper;
	shereMapper->SetInputConnection(shereSource->GetOutputPort());
	// 声明一个actor 类，然后使用这个类来显示球体
	vtkNew<vtkActor> shereActor;
	shereActor->SetMapper(shereMapper);
	// 设置颜色
	shereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());
	// 渲染
	vtkNew<vtkRenderer> renderer;
	renderer->AddActor(shereActor);
	renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
	// 显示renderer 的窗口
	vtkNew<vtkGenericOpenGLRenderWindow> renderwindow;

	renderwindow->AddRenderer(renderer);
	renderwindow->SetWindowName("RenderWindowNoUIFile");

	QVTKOpenGLWidget* qvtkWidget = new QVTKOpenGLWidget;
	qvtkWidget->SetRenderWindow(renderwindow);

	return qvtkWidget;
}

VTKWRAP_NAMESPACE_END
MYVTK_NAMESPACE_END