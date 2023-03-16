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
		using PixelType = float;
		constexpr unsigned int Dimension = 3;
		using ImageType = itk::Image< PixelType, Dimension >;
		using ReaderType = itk::ImageSeriesReader< ImageType >;
		using ImageIOType = itk::GDCMImageIO;
		using NamesGeneratorType = itk::GDCMSeriesFileNames;
		ReaderType::Pointer reader = ReaderType::New();
		ImageIOType::Pointer dicomIO = ImageIOType::New();
		reader->SetImageIO(dicomIO);
		NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
		nameGenerator->SetUseSeriesDetails(true);
		nameGenerator->SetDirectory("Data/Dcm/series-000001");

		using SeriesIdContainer = std::vector< std::string >;
		const SeriesIdContainer& seriesUID = nameGenerator->GetSeriesUIDs();
		auto seriesItr = seriesUID.begin();
		auto seriesEnd = seriesUID.end();

		using FileNamesContainer = std::vector< std::string >;
		FileNamesContainer fileNames;
		std::string seriesIdentifier;
		while (seriesItr != seriesEnd)
		{

			seriesIdentifier = seriesItr->c_str();
			fileNames = nameGenerator->GetFileNames(seriesIdentifier);
			++seriesItr;
		}

		reader->SetFileNames(fileNames);

		try
		{
			reader->Update();
		}
		catch (itk::ExceptionObject& ex)
		{
			std::cout << ex << std::endl;
		}
		ImageType::SizeType imgSize = reader->GetOutput()->GetLargestPossibleRegion().GetSize();
		cout << "read done, Original size: " << imgSize << endl;

		typedef itk::ImageToVTKImageFilter< ImageType> itkTovtkFilterType;
		itkTovtkFilterType::Pointer itkTovtkImageFilter = itkTovtkFilterType::New();
		itkTovtkImageFilter->SetInput(reader->GetOutput());
		itkTovtkImageFilter->Update();

		vtkSmartPointer<vtkMarchingCubes> vesselExtractor = vtkMarchingCubes::New();
		vesselExtractor->SetInputData(itkTovtkImageFilter->GetOutput());
		vesselExtractor->SetNumberOfContours(10);
		vesselExtractor->SetValue(0, 1);   //轮廓

		//将提取的等值面拼接成连续的
		vtkSmartPointer<vtkStripper> vesselStripper = vtkStripper::New();                           //建立三角带对象
		vesselStripper->SetInputConnection(vesselExtractor->GetOutputPort());


		vtkSmartPointer<vtkPolyDataMapper>  vesselMapper = vtkPolyDataMapper::New();     //建立一个数据映射对象
		vesselMapper->SetInputConnection(vesselStripper->GetOutputPort());                     //将三角带映射为几何数据
		vesselMapper->SetScalarRange(0, 7);

		//对象和对象属性等设置
		vtkSmartPointer<vtkActor> vessel = vtkActor::New();
		vessel->SetMapper(vesselMapper);
		vessel->GetProperty()->SetColor(0, 0, 1);

		// A renderer and render window
		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
		renderWindow->AddRenderer(renderer);
		renderWindow->SetSize(1000, 1000);
		renderer->AddActor(vessel);

		// An interactor
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		renderWindowInteractor->SetRenderWindow(m_pRenderwindow);
		renderWindow->Render();
		renderWindowInteractor->Initialize();
		renderWindowInteractor->Start();
	}break;
	default:
		break;
	}

	m_pRenderwindow->Render();
}
