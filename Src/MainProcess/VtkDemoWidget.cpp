#include "VtkDemoWidget.h"

VtkDemoWidget::VtkDemoWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_pVTKOpenGLWidget = new QVTKOpenGLWidget(this);
	ui.gridLayout_2->addWidget(m_pVTKOpenGLWidget);
	m_pRenderwindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	m_pVTKOpenGLWidget->SetRenderWindow(m_pRenderwindow);
	m_pRenderer = vtkSmartPointer<vtkRenderer>::New();
	m_pRenderer->SetBackground(51.0 / 255, 51.0 / 255, 102.0 / 255);
	m_pRenderer->GetActiveCamera()->SetPosition(0, 0, 6);
	m_pRenderwindow->AddRenderer(m_pRenderer);

	connect(ui.listWidget, &QListWidget::itemClicked, this, &VtkDemoWidget::onListItemClicked);
}

VtkDemoWidget::~VtkDemoWidget()
{

}

void VtkDemoWidget::onListItemClicked(QListWidgetItem* item)
{
	int index = ui.listWidget->currentRow();

	switch (index)
	{
	case 0:		//使用几何结构+拓扑结构+属性数据
	{
		/***** 几何结构 *****/
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
		points->InsertNextPoint(0.0, 0.0, 0.0);
		points->InsertNextPoint(1.0, 0.0, 0.0);
		points->InsertNextPoint(1.0, 1.0, 0.0);
		points->InsertNextPoint(0.0, 1.0, 0.0);
		points->InsertNextPoint(2.0, 0.0, 0.0);

		/***** 拓扑结构 *****/
		//四边形
		vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();
		polygon->GetPointIds()->SetNumberOfIds(4);
		polygon->GetPointIds()->SetId(0, 0);
		polygon->GetPointIds()->SetId(1, 1);
		polygon->GetPointIds()->SetId(2, 2);
		polygon->GetPointIds()->SetId(3, 3);
		//三角形
		vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
		triangle->GetPointIds()->SetId(0, 1);
		triangle->GetPointIds()->SetId(1, 2);
		triangle->GetPointIds()->SetId(2, 4);
		//添加拓扑结构
		vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
		cells->InsertNextCell(polygon);
		cells->InsertNextCell(triangle);

		/***** 属性数据 *****/
		float red[3] = { 255, 0, 0 };
		float green[3] = { 0, 255, 0 };
		float blue[3] = { 0, 0, 255 };
		vtkSmartPointer<vtkUnsignedCharArray> ptColor = vtkSmartPointer<vtkUnsignedCharArray>::New();
		ptColor->SetNumberOfComponents(3);
		ptColor->InsertNextTuple(red);
		ptColor->InsertNextTuple(green);
		ptColor->InsertNextTuple(blue);
		ptColor->InsertNextTuple(red);
		ptColor->InsertNextTuple(green);

		/***** 数据集 *****/
		vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
		polyData->SetPoints(points);
		polyData->SetPolys(cells);
		polyData->GetPointData()->SetScalars(ptColor);

		/******* mapper *******/
		vtkSmartPointer<vtkPolyDataMapper> pMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		pMapper->SetInputData(polyData);

		/******* actor *******/
		vtkSmartPointer<vtkActor> pActor = vtkSmartPointer<vtkActor>::New();
		pActor->SetMapper(pMapper);

		/******* render *******/
		m_pRenderer->AddActor(pActor);
	}break;
	case 1:		//使用vtk......Source系列数据源
	{
		/******* source *******/
		vtkSmartPointer<vtkSphereSource> pSource = vtkSmartPointer<vtkSphereSource>::New();

		/***** 属性数据 *****/

		/******* mapper *******/
		vtkSmartPointer<vtkPolyDataMapper> pMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		pMapper->SetInputConnection(pSource->GetOutputPort());

		/******* actor *******/
		vtkSmartPointer<vtkActor> pActor = vtkSmartPointer<vtkActor>::New();
		pActor->SetMapper(pMapper);
		// 设置颜色
		pActor->GetProperty()->SetColor(100.0 / 255, 25.0 / 255, 102.0 / 255);

		/******* render *******/
		m_pRenderer->AddActor(pActor);	
	}break;
	default:
		break;
	}

	m_pRenderwindow->Render();
}
