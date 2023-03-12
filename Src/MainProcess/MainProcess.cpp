#include "MainProcess.h"

MainProcess::MainProcess(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	resize(1300, 700);

	//Demo
	m_pVtkDemoWidget = new VtkDemoWidget(this);
	ui.gridLayout_2->addWidget(m_pVtkDemoWidget);
}

