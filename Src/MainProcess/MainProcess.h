#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_MainProcess.h"

#include "VtkDemoWidget.h"

class MainProcess : public QMainWindow
{
	Q_OBJECT

public:
	MainProcess(QWidget *parent = Q_NULLPTR);
private:
	Ui::MainProcessClass ui;
	VtkDemoWidget* m_pVtkDemoWidget{nullptr};
};
