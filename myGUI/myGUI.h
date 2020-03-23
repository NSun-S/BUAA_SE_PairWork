#pragma once

#include <QtWidgets/QMainWindow>
#include <QButtonGroup>
#include <QRadioButton>
#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include <QLibrary>
#include <fstream>
#include "ui_myGUI.h"
#include "qcustomplot.h"
#include "IntersectProject2.h"

using namespace std;

class myGUI : public QMainWindow
{
	Q_OBJECT

public:
	myGUI(QWidget* parent = Q_NULLPTR);
	void initialize();
private:
	Ui::myGUIClass ui;

public slots:
	void Qsolve();
	void QaddLine();
	void QdeleteLine();
	void QaddCircle();
	void QdeleteCircle();
	void QdeleteAll();
	void QioHandler();
};