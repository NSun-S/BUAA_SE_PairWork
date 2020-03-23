#include "myGUI.h"

myGUI::myGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.widget->xAxis->setLabel("x");
	ui.widget->yAxis->setLabel("y");
	ui.widget->xAxis->setRange(-40, 40);
	ui.widget->yAxis->setRange(-25, 25);
	ui.widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	ui.widget->replot();
	initialize();
}

void myGUI::initialize()
{
	this->setWindowTitle("Intersection solution");
}

void myGUI::QaddLine()
{
	string newType = ui.newType->toPlainText().toStdString();
	double x1 = ui.newX1->toPlainText().toDouble();
	double y1 = ui.newY1->toPlainText().toDouble();
	double x2 = ui.newX2->toPlainText().toDouble();
	double y2 = ui.newY2->toPlainText().toDouble();
	int type = -1;
	if (newType == "L") {
		type = LINE;
	}
	else if (newType == "R") {
		type = RAY;
	}
	else if (newType == "S") {
		type = SEGMENT;
	}
	addLine(x1, y1, x2, y2, type);
	Qsolve();
}

void myGUI::QdeleteLine()
{
	string newType = ui.newType->toPlainText().toStdString();
	double x1 = ui.newX1->toPlainText().toDouble();
	double y1 = ui.newY1->toPlainText().toDouble();
	double x2 = ui.newX2->toPlainText().toDouble();
	double y2 = ui.newY2->toPlainText().toDouble();
	int type = -1;
	if (newType == "L") type = LINE;
	else if (newType == "R") type = RAY;
	else if (newType == "S") type = SEGMENT;
	deleteLine(x1, y1, x2, y2, type);
	ui.widget->clearItems();
	ui.widget->clearGraphs();
	Qsolve();
}

void myGUI::QaddCircle()
{
	double c1 = ui.newC1->toPlainText().toDouble();
	double c2 = ui.newC2->toPlainText().toDouble();
	double r = ui.newR->toPlainText().toDouble();
	addCircle(c1, c2, r);
	Qsolve();
}

void myGUI::QdeleteCircle()
{
	double c1 = ui.newC1->toPlainText().toDouble();
	double c2 = ui.newC2->toPlainText().toDouble();
	double r = ui.newR->toPlainText().toDouble();
	deleteCircle(c1, c2, r);
	ui.widget->clearItems();
	ui.widget->clearGraphs();
	Qsolve();
}

void myGUI::QdeleteAll()
{
	deleteAll();
	ui.widget->clearItems();
	ui.widget->clearGraphs();
	ui.widget->replot();
}

void myGUI::QioHandler()
{
	string inputFile = ui.fileInput->toPlainText().toStdString();
	ioHandler(inputFile);
	Qsolve();
}

void myGUI::Qsolve()
{
	vector<pair<double, double>> realIntersections;
	solve(realIntersections);
	fstream outputFile("output.txt", ios::out);
	outputFile << realIntersections.size();
	QString num = QString::number(realIntersections.size());
	ui.intersectionNum->setText(num);
	ui.widget->xAxis->setLabel("X");
	ui.widget->yAxis->setLabel("Y");
	ui.widget->addGraph(ui.widget->yAxis, ui.widget->xAxis);
	ui.widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	ui.widget->axisRect()->setupFullAxesBox();
	ui.widget->rescaleAxes();
	ui.widget->xAxis->setScaleRatio(ui.widget->yAxis, 1.0);
	ui.widget->xAxis2->setScaleRatio(ui.widget->yAxis2, 1.0);
	QPen drawPen;
	drawPen.setColor(Qt::red);
	drawPen.setWidth(4);
	QVector<double> X, Y;
	for (unsigned i = 0; i < realIntersections.size(); i++)
	{
		X << realIntersections[i].first;
		Y << realIntersections[i].second;
	}
	QCPGraph* curGraph = ui.widget->addGraph();
	curGraph->setPen(drawPen);
	curGraph->setLineStyle(QCPGraph::lsNone);
	curGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
	curGraph->setData(X, Y);
	ui.widget->xAxis->setVisible(true);
	ui.widget->yAxis->setVisible(true);

	vector<Line> lines = getLines();
	for (unsigned i = 0; i < lines.size(); i++)
	{
		if (lines[i].type == LINE) {
			QCPItemStraightLine* line = new QCPItemStraightLine(ui.widget);
			line->point1->setType(QCPItemPosition::PositionType::ptPlotCoords);
			line->point2->setType(QCPItemPosition::PositionType::ptPlotCoords);
			line->point1->setCoords(lines[i].x1, lines[i].y1);
			line->point2->setCoords(lines[i].x2, lines[i].y2);
		}
		else if (lines[i].type == RAY) {
			QCPItemLine* ray = new QCPItemLine(ui.widget);
			ray->setHead(QCPLineEnding::esFlatArrow);
			ray->setTail(QCPLineEnding::esBar);
			ray->start->setType(QCPItemPosition::PositionType::ptPlotCoords);
			ray->end->setType(QCPItemPosition::PositionType::ptPlotCoords);
			ray->start->setCoords(lines[i].x1, lines[i].y1);
			ray->end->setCoords(lines[i].x2, lines[i].y2);
		}
		else if (lines[i].type == SEGMENT) {
			QCPItemLine* segment = new QCPItemLine(ui.widget);
			segment->setHead(QCPLineEnding::esHalfBar);
			segment->setTail(QCPLineEnding::esHalfBar);
			segment->start->setType(QCPItemPosition::PositionType::ptPlotCoords);
			segment->end->setType(QCPItemPosition::PositionType::ptPlotCoords);
			segment->start->setCoords(lines[i].x1, lines[i].y1);
			segment->end->setCoords(lines[i].x2, lines[i].y2);
		}
	}

	vector<Circle> circles = getCircles();
	for (unsigned i = 0; i < circles.size(); i++) {
		QCPItemEllipse* circle = new  QCPItemEllipse(ui.widget);
		circle->topLeft->setType(QCPItemPosition::PositionType::ptPlotCoords);
		circle->bottomRight->setType(QCPItemPosition::PositionType::ptPlotCoords);
		circle->topLeft->setCoords(circles[i].c1 - circles[i].r, circles[i].c2 - circles[i].r);
		circle->bottomRight->setCoords(circles[i].c1 + circles[i].r, circles[i].c2 + circles[i].r);
	}
	ui.widget->replot();
}