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
	case 0:
	{
		
	}break;
	case 1:		//使用几何结构+拓扑结构+属性数据
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
	case 2:		//使用vtk......Source系列数据源
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
	case 3:		//读取、显示、保存图片
	{
		//生成文件序列组名
		vtkSmartPointer <vtkStringArray> fileArray = vtkSmartPointer <vtkStringArray>::New();
		char fileName[128];
		for (int i = 1; i <= 3; i++)
		{
			sprintf(fileName, "Data/Images/%03d.jpg", i);
			fileArray->InsertNextValue(std::string(fileName));
		}
		//读取JPG序列图像
		vtkSmartPointer <vtkJPEGReader> reader = vtkSmartPointer <vtkJPEGReader>::New();
		reader->SetFileNames(fileArray);
		reader->Update();

		//显示
		vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
		viewer->SetInputConnection(reader->GetOutputPort());
		vtkSmartPointer<vtkRenderWindowInteractor> interact = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		//默认选择第50张切片
		viewer->SetSlice(2);
		//viewer->SetSliceOrientationToXY();
		//viewer->SetSliceOrientationToXZ();
		viewer->SetSliceOrientationToYZ();
		viewer->SetupInteractor(interact);
		viewer->Render();

		interact->Start();

		////writer
		//vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
		//writer->SetFileName("Data/Images/wukong.png");
		//writer->SetInputConnection(reader->GetOutputPort());
		//writer->Write();
	}break;
	case 4:		//读取CT DCM
	{
		using PixelType = unsigned int;
		using ImageType = itk::Image<PixelType, 3>;
		using ImageReader = itk::ImageFileReader<ImageType>;
		ImageReader::Pointer reader = ImageReader::New();
		// 此处是我 CT Dicom 文件的路径，请根据实际情况修改
		reader->SetFileName("Data/Dcm/series-000001/image-000001.dcm");
		reader->Update();
		ImageType::Pointer image = reader->GetOutput();
		// 到此处，使用 ITK 读取 dicom 文件已经结束

		// 此处开始使用 VTK 显示读取的 CT 图像
		using ConnectorType = itk::ImageToVTKImageFilter<ImageType>;  //VTK和ITK链接器
		ConnectorType::Pointer connector = ConnectorType::New();
		connector->SetInput(image);
		connector->Update();

		//vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkRenderWindowInteractor::New();
		vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
		viewer->SetInputData(connector->GetOutput());
		//viewer->SetupInteractor(interactor);
		viewer->SetSize(800, 600);
		viewer->SetColorWindow(255); //设置窗宽
		viewer->SetColorLevel(500);   //设置窗位
		viewer->SetSliceOrientationToXY();
		viewer->SetSlice(1);

		viewer->SetRenderWindow(m_pRenderwindow);
		viewer->Render();


		//interactor->Initialize();
		//interactor->Start();
	}break;
	default:
		break;
	}

	m_pRenderwindow->Render();
}
