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
		if (type == RAY && line2.type == RAY)
		{
			if (x1 == x3 && y1 == y3 && ((x2 - x1) * (x4 - x1) < 0 || (y2 - y1) * (y4 - y1) < 0))
			{
				intersections.push_back(make_pair(x1, y1));
			}
			else
			{
				return false;
			}
		}
		else if (type == RAY && line2.type == SEGMENT)
		{
			if (x1 == x3 && y1 == y3 && ((x2 - x1) * (x4 - x1) < 0 || (y2 - y1) * (y4 - y1) < 0))
			{
				intersections.push_back(make_pair(x1, y1));
			}
			else if (x1 == x4 && y1 == y4 && ((x2 - x1) * (x3 - x1) < 0 || (y2 - y1) * (y3 - y1) < 0))
			{
				intersections.push_back(make_pair(x1, y1));
			}
			else
			{
				return false;
			}
		}
		else if (type == SEGMENT && line2.type == RAY)
		{
			if (x1 == x3 && y1 == y3 && ((x2 - x1) * (x4 - x1) < 0 || (y2 - y1) * (y4 - y1) < 0))
			{
				intersections.push_back(make_pair(x1, y1));
			}
			else if (x2 == x3 && y2 == y3 && ((x1 - x2) * (x4 - x2) < 0 || (y1 - y2) * (y4 - y2) < 0))
			{
				intersections.push_back(make_pair(x2, y1));
			}
			else
			{
				return false;
			}
		}
		else if (type == SEGMENT && line2.type == SEGMENT)
		{
			if (x1 == x3 && y1 == y3 && ((x2 - x1) * (x4 - x1) < 0 || (y2 - y1) * (y4 - y1) < 0))
			{
				intersections.push_back(make_pair(x1, y1));
			}
			else if (x1 == x4 && y1 == y4 && ((x2 - x1) * (x3 - x1) < 0 || (y2 - y1) * (y3 - y1) < 0))
			{
				intersections.push_back(make_pair(x1, y1));
			}
			else if (x2 == x3 && y2 == y3 && ((x1 - x2) * (x4 - x2) < 0 || (y1 - y2) * (y4 - y2) < 0))
			{
				intersections.push_back(make_pair(x2, y2));
			}
			else if (x2 == x4 && y2 == y4 && ((x1 - x2) * (x3 - x2) < 0 || (y1 - y2) * (y3 - y2) < 0))
			{
				intersections.push_back(make_pair(x2, y2));
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
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
	//pair<double, double> endPoint1 = make_pair(x1, y1);
	//pair<double, double> endPoint2 = make_pair(x2, y2);
	//double distance1 = pointDistance(endPoint1, intersection);
	//double distance2 = pointDistance(endPoint2, intersection);
//	double length = pointDistance(endPoint1, endPoint2);
	if (type == SEGMENT)
	{
		if (x1 == x2)
		{
			return ((x1 - eps <= intersection.first && intersection.first <= x1 + eps) &&
				((y1 - eps <= intersection.second && intersection.second <= y2 + eps) ||
				(y2 - eps <= intersection.second && intersection.second <= y1 + eps)));
		}
		return ((x1 - eps <= intersection.first && intersection.first <= x2 + eps) ||
			(x2 - eps <= intersection.first && intersection.first <= x1 + eps));
		//return (distance1 <= length + eps && distance2 <= length + eps);
	}
	else if (type == RAY)
	{
		if (x1 == x2)
		{
			return ((x1 - eps <= intersection.first && intersection.first <= x1 + eps) &&
				((intersection.second - y1 - eps)*(y2-y1)>=0||
				(intersection.second - y1 + eps) * (y2 - y1) >= 0));
		}
		else if (x1 < x2) return x1 - eps <= intersection.first;
		else return intersection.first <= x1 + eps;
		//return (((distance2 - distance1) - length) < -eps)||(distance1 < eps);
	}
	return true;
}

