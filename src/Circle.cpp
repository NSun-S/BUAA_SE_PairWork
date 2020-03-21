#include "Circle.h"

Circle::Circle(double c1, double c2, double r)
{
	this->c1 = c1;
	this->c2 = c2;
	this->r = r;
}

pair<double, double> Circle::getFoot(Line line1)
{
	line1.type = LINE;
	vector<pair<double, double>> intersection;
	if (line1.x1 == line1.x2)
	{
		Line line2 = Line(c1, c2, c1 + 1, c2, LINE);
		line1.intersect(line2, intersection);
		if (intersection.size() == 0) { 
			cout << "18" << endl; 
			cout << line1.type << " " << line2.type << endl;
			cout << line1.x1 << " " << line1.y1 << " " << line1.x2 << " " << line1.y2 << endl;
			cout << line2.x1 << " " << line2.y1 << " " << line2.x2 << " " << line2.y2 << endl;
		}
		return intersection[0];
	}
	else if (line1.y1 == line1.y2)
	{
		Line line2 = Line(c1, c2, c1, c2 + 1, LINE);
		line1.intersect(line2, intersection);
		if (intersection.size() == 0) cout << "25" << endl;
		return intersection[0];
	}
	else
	{
		double cof = -(line1.x2 - line1.x1) / (line1.y2 - line1.y1);
		Line line2 = Line(c1, c2, c1 + 1, c2 + cof, LINE);
		line1.intersect(line2, intersection);
		if (intersection.size() == 0) cout << "33" << endl;
		return intersection[0];
	}
}

double Circle::getDistance(Line line1)
{
	pair<double, double> foot = getFoot(line1);
	return sqrt(pow((foot.first - c1), 2) + pow((foot.second - c2), 2));
}

int Circle::intersectLine(Line line1, vector<pair<double, double>>& intersections)
{
	double distance = getDistance(line1);
	//cout << distance << endl;
	if (distance - r > eps)
	{
		return 0;
	}
	pair<double, double> foot = getFoot(line1);
	if (fabs(distance - r) < eps)
	{
		if (line1.pointOnLine(foot))
		{
			intersections.push_back(foot);
			return 1;
		}
		return 0;
	}
	double length = sqrt(r * r - distance * distance);
	pair<double, double> intersection1, intersection2;
	if (line1.x1 == line1.x2)
	{
		intersection1 = make_pair(foot.first, foot.second + length);
		intersection2 = make_pair(foot.first, foot.second - length);
		//intersections.push_back(make_pair(foot.first, foot.second + length));
		//intersections.push_back(make_pair(foot.first, foot.second - length));
	}
	else
	{
		double cof = (line1.y1 - line1.y2) / (line1.x1 - line1.x2);
		double x = 1 / sqrt(cof * cof + 1);
		double y = cof / sqrt(cof * cof + 1);
		intersection1 = make_pair(foot.first + x * length, foot.second + y * length);
		intersection2 = make_pair(foot.first - x * length, foot.second - y * length);
		//intersections.push_back(make_pair(foot.first + x * length, foot.second + y * length));
		//intersections.push_back(make_pair(foot.first - x * length, foot.second - y * length));
	}
	if (line1.pointOnLine(intersection1))
	{
		intersections.push_back(intersection1);
	}
	if (line1.pointOnLine(intersection2))
	{
		intersections.push_back(intersection2);
	}
	return 2;
}

int Circle::intersectCircle(Circle circle2, vector<pair<double, double>>& intersections)
{
	//double distance = sqrt(circle2.r * circle2.r - r * r);
	double distance = sqrt(pow(circle2.c1 - c1, 2) + pow(circle2.c2 - c2,2));
	if (distance - eps > (r + circle2.r) || distance + eps < fabs(r - circle2.r)) return 0;
	double right = circle2.r * circle2.r - r * r + c1 * c1 - circle2.c1 * circle2.c1
		+ c2 * c2 - circle2.c2 * circle2.c2;
	if (circle2.c1 == c1)
	{
		double y = -right / (2 * circle2.c2 - 2 * c2);
		Line line1 = Line(1, y, -1, y, LINE);
		return intersectLine(line1, intersections);
	}
	else if (circle2.c2 == c2)
	{
		double x = -right / (2 * circle2.c1 - 2 * c1);
		Line line1 = Line(x, 1, x, -1, LINE);
		return intersectLine(line1, intersections);
	}
	else
	{
		Line line1 = Line(1, (-right - 2 * circle2.c1 + 2 * c1) / (2 * circle2.c2 - 2 * c2), 
			0, -right / (2 * circle2.c2 - 2 * c2), LINE);
		//Line line1 = Line(1, (-right - 2*circle2.c1 + 2*c1) / (2 * circle2.c2 - 2 * c2), -right / (2 * circle2.c1 - 2 * c1), 0, LINE);
		//cout << right / (2 * circle2.c2 - 2 * c2) << ' '<<right / (2 * circle2.c1 - 2 * c1) << endl;
		return intersectLine(line1, intersections);
	}
}



