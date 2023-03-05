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
	// ����һ��actor �࣬Ȼ��ʹ�����������ʾ����
	vtkNew<vtkActor> shereActor;
	shereActor->SetMapper(shereMapper);
	// ������ɫ
	shereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());
	// ��Ⱦ
	vtkNew<vtkRenderer> renderer;
	renderer->AddActor(shereActor);
	renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
	// ��ʾrenderer �Ĵ���
	vtkNew<vtkGenericOpenGLRenderWindow> renderwindow;

	renderwindow->AddRenderer(renderer);
	renderwindow->SetWindowName("RenderWindowNoUIFile");

	QVTKOpenGLWidget* qvtkWidget = new QVTKOpenGLWidget;
	qvtkWidget->SetRenderWindow(renderwindow);

	return qvtkWidget;
}

VTKWRAP_NAMESPACE_END
MYVTK_NAMESPACE_END