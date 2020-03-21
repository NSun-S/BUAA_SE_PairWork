#include "IntersectProject2.h"
//#include <stdio.h>

using namespace std;

bool cmp(const pair<double, double> pair1, const pair<double, double> pair2)
{
	return (pair1.first - pair2.first> eps || (fabs(pair1.first - pair2.first) < eps && pair1.second - pair2.second > eps));
}

bool myequal(const pair<double, double> pair1, const pair<double, double> pair2)
{
	return (fabs(pair1.first - pair2.first) < eps && fabs(pair1.second - pair2.second) < eps);
}

void solve(string input, string output, vector<pair<double, double>> &realIntersections)
{
	fstream inputfile(input);
	int n;
	inputfile >> n;
	vector<Line> lines;
	vector<Circle>circles;
	vector<pair<double, double>> intersections;
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
			lines.push_back(Line(x1, y1, x2, y2, tempType));
		}
		else if (type == 'C')
		{
			double c1, c2, r;
			inputfile >> c1 >> c2 >> r;
			circles.push_back(Circle(c1, c2, r));
		}
	}
	for (unsigned i = 0; i < lines.size(); i++)
	{
		for (unsigned j = i + 1; j < lines.size(); j++)
		{
			lines[i].intersect(lines[j], intersections);
		}
	}
	for (unsigned i = 0; i < circles.size(); i++)
	{
		for (unsigned j = i + 1; j < circles.size(); j++)
		{
			circles[i].intersectCircle(circles[j], intersections);
		}
		for (unsigned j = 0; j < lines.size(); j++)
		{
			circles[i].intersectLine(lines[j], intersections);
		}
	}
	sort(intersections.begin(), intersections.end(), cmp);
	//vector<pair<double, double>> realIntersections;
	fstream outputFile(output, ios::out);
	if (intersections.size() == 0) 
	{ 
		outputFile << 0; 
		return;
		//return realIntersections;
	}
	realIntersections.push_back(intersections[0]);
	for (unsigned i = 1; i < intersections.size(); i++)
	{
		if (!myequal(intersections[i - 1], intersections[i]))
		{
			realIntersections.push_back(intersections[i]);
		}
	}
	outputFile << realIntersections.size();
	//return realIntersections;
	//string points = "points.txt";
	//fstream outpoint(points, ios::out);
	//cout << realIntersections.size() << endl;
	//for (auto iter = realIntersections.begin(); iter != realIntersections.end(); iter++)
	//{
		//cout << iter->first << ' ' << iter->second << endl;
	//	printf("%.10lf,%.10lf\n",iter->first,iter->second);
	//}
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
	solve(input, output, myIntersections);
	return 0;
}
