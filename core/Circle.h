#pragma once
#include <utility>
#include "Line.h"
#include <math.h>

using namespace std;

class Circle
{
public:
	Circle(double c1, double c2, double r);
	pair<double, double>getFoot(Line line1);
	double getDistance(Line line1);
	int intersectLine(Line line1, vector<pair<double, double>>& intersections);
	int intersectCircle(Circle circle2, vector<pair<double, double>>& intersections);
	double c1, c2, r;
};
	//int intersectLine(Line line1, set<pair<double, double>>& intersections);
	//int intersectCircle(Circle circle2, set<pair<double, double>>& intersections);