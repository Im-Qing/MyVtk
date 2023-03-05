#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainProcess.h"

class MainProcess : public QMainWindow
{
	Q_OBJECT

public:
	MainProcess(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainProcessClass ui;
};
