#include "MainProcess.h"

MainProcess::MainProcess(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_pVtkWrap = new MyVtk::VtkWrap::VtkWrap();
	ui.gridLayout->addWidget(m_pVtkWrap->test());
}
