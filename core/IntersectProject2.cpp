#include "IntersectProject2.h"
//#include <stdio.h>

using namespace std;

vector<Line> lines;
vector<Circle> circles;

bool cmp(const pair<double, double> pair1, const pair<double, double> pair2)
{
	return (pair1.first - pair2.first> eps || (fabs(pair1.first - pair2.first) < eps && pair1.second - pair2.second > eps));
}

bool myequal(const pair<double, double> pair1, const pair<double, double> pair2)
{
	return (fabs(pair1.first - pair2.first) < eps && fabs(pair1.second - pair2.second) < eps);
}

void solve(vector<pair<double, double>> &realIntersections) throw(const char*)
{
	vector<pair<double, double>> intersections;
	for (unsigned i = 0; i < lines.size(); i++)
	{
		for (unsigned j = i + 1; j < lines.size(); j++)
		{
			try
			{
				lines[i].intersect(lines[j], intersections);
			}catch (const char* msg)
			{
				throw msg;
			}
		}
	}
	for (unsigned i = 0; i < circles.size(); i++)
	{
		for (unsigned j = i + 1; j < circles.size(); j++)
		{
			if (circles[i].c1 == circles[j].c1 && circles[i].c2 == circles[j].c2 && circles[i].r == circles[j].r)
			{
				throw "Error: There are two same circles";
			}
			circles[i].intersectCircle(circles[j], intersections);
		}
		for (unsigned j = 0; j < lines.size(); j++)
		{
			circles[i].intersectLine(lines[j], intersections);
		}
	}
	sort(intersections.begin(), intersections.end(), cmp);
	if (intersections.size() == 0) 
	{ 
		//outputFile << 0; 
		return;
	}
	realIntersections.push_back(intersections[0]);
	for (unsigned i = 1; i < intersections.size(); i++)
	{
		if (!myequal(intersections[i - 1], intersections[i]))
		{
			realIntersections.push_back(intersections[i]);
		}
	}
	//cout << realIntersections.size() << endl;
	//for (auto iter = realIntersections.begin(); iter != realIntersections.end(); iter++)
	//{
		//cout << iter->first << ' ' << iter->second << endl;
	//	printf("%.3lf,%.3lf\n",iter->first,iter->second);
	//}
}

void ioHandler(string input)throw(const char*)
{
	fstream inputfile(input);
	int n;
	inputfile >> n;
	for (int i = 0; i < n; i++)
	{
		char type;
		inputfile >> type;
		if (type == 'L' || type == 'R' || type == 'S')
		{
			int tempType = -1;
			if (type == 'L') tempType = LINE;
			else if (type == 'R') tempType = RAY;
			else if (type == 'S') tempType = SEGMENT;
			double x1, x2, y1, y2;
			inputfile >> x1 >> y1 >> x2 >> y2;
			if (fabs(x1) > 100000 || fabs(y1) > 100000 || fabs(x2) > 100000 || fabs(y2) > 100000)
			{
				throw "Warning: your coordinate value is out of bound";
			}
			if (x1 == x2 && y1 == y2)
			{
				throw "Error: two points of a line should be different";
			}
			lines.push_back(Line(x1, y1, x2, y2, tempType));
		}
		else if (type == 'C')
		{
			double c1, c2, r;
			inputfile >> c1 >> c2 >> r;
			if (fabs(c1) > 100000 || fabs(c2) > 100000)
			{
				throw "Warning: your coordinate value is out of bound";
			}
			if (fabs(r) <= 0)
			{
				throw "Error: circle's radius should be a positive integer";
			}
			circles.push_back(Circle(c1, c2, r));
		}
		else
		{
			throw ("Error: unexcepted type mark");
		}
	}
}

void addLine(double x1, double y1, double x2, double y2, int type)throw(const char*)
{
	if (fabs(x1) > 100000 || fabs(y1) > 100000 || fabs(x2) > 100000 || fabs(y2) > 100000)
	{
		throw "Warning: your coordinate value is out of bound";
	}
	if (x1 == x2 && y1 == y2)
	{
		throw "Error: two points of a line should be different";
	}
	lines.push_back(Line(x1, y1, x2, y2, type));
}

void deleteLine(double x1, double y1, double x2, double y2, int type)
{
	for (auto iter = lines.begin(); iter!= lines.end();iter++)
	{
		if (iter->x1 == x1 && iter->y1 == y1 && iter->x2 == x2 && iter->y2 == y2 && iter->type == type)
		{
			lines.erase(iter);
			break;
		}
	}
}

void addCircle(double c1, double c2, double r)throw(const char*)
{
	if (fabs(c1) > 100000 || fabs(c2) > 100000)
	{
		throw "Warning: your coordinate value is out of bound";
	}
	if (fabs(r) <= 0)
	{
		throw "Error: circle's radius should be a positive integer";
	}
	circles.push_back(Circle(c1, c2, r));
}

void deleteCircle(double c1, double c2, double r)
{
	for (auto iter = circles.begin(); iter != circles.end(); iter++)
	{
		if (iter->c1 == c1 && iter->c2 == c2 && iter->r == r)
		{
			circles.erase(iter);
			break;
		}
	}
}

void deleteAll()
{
	lines.clear();
	circles.clear();
}

vector<Line> getLines() {
	return lines;
}

vector<Circle> getCircles() {
	return circles;
}

int main(int argc, char* argv[])
{
	string input;
	string output;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			input = argv[i + 1];
		}
		else if (strcmp(argv[i], "-o") == 0)
		{
			output = argv[i + 1];
		}
	}
	vector<pair<double, double>> myIntersections;
	try
	{
		ioHandler(input);
		solve(myIntersections);
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	}
	fstream outputFile(output, ios::out);
	outputFile << myIntersections.size();
	return 0;
}