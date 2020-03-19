#include "Line.h"

Line::Line(double x1, double y1, double x2, double y2, int type)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->type = type;
}

bool Line::intersect(Line line2, vector<pair<double, double>>& intersections)
{
	double x3 = line2.x1;
	double x4 = line2.x2;
	double y3 = line2.y1;
	double y4 = line2.y2;
	double Determinant = (y1 - y2) * (x3 - x4) - (y3 - y4) * (x1 - x2);
	if (fabs(Determinant) < eps)
	{
		return false;
	}
	double intersect_x = (-(x1 - x2) * (y3 * x4 - x3 * y4) + (x3 - x4) * (y1 * x2 - x1 * y2)) / Determinant;
	double intersect_y = (-(y1 - y2) * (y3 * x4 - x3 * y4) + (y3 - y4) * (y1 * x2 - x1 * y2)) / Determinant;
	pair<double, double> intersect = make_pair(intersect_x, intersect_y);
	if (pointOnLine(intersect) && line2.pointOnLine(intersect))
	{
		intersections.push_back(make_pair(intersect_x, intersect_y));
	}
	return true;
}

double Line::pointDistance(pair<double, double> point1, pair<double, double> point2)
{
	return sqrt(pow(point1.first - point2.first, 2) + pow(point1.second - point2.second, 2));
}

bool Line::pointOnLine(pair<double, double> intersection)
{
	pair<double, double> endPoint1 = make_pair(x1, y1);
	pair<double, double> endPoint2 = make_pair(x2, y2);
	double distance1 = pointDistance(endPoint1, intersection);
	double distance2 = pointDistance(endPoint2, intersection);
	double length = pointDistance(endPoint1, endPoint2);
	if (type == SEGMENT)
	{
		return (distance1 <= length && distance2 <= length);
	}
	else if (type == RAY)
	{
		return ((distance2 - distance1) - length) < -eps;
	}
	return true;
}

