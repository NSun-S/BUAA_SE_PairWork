#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Line.h"
#include "../src/Circle.h"
#include <vector>
#include <algorithm>
#include "../src/IntersectProject2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool CMP(const pair<double, double> pair1, const pair<double, double> pair2)
{
	return (pair1.first > pair2.first || (pair1.first == pair2.first && pair1.second > pair2.second));
}

bool Myequal(const pair<double, double> pair1, const pair<double, double> pair2)
{
	return (fabs(pair1.first - pair2.first) < 1e-10 && fabs(pair1.second - pair2.second) < 1e-10);
}

int compute(vector<Line> lines, vector<Circle> circles)
{
	vector<pair<double, double>> intersections;
	for (unsigned i = 0; i < lines.size(); i++)
	{
		for (unsigned j = i + 1; j < lines.size(); j++)
		{
			cout << lines[i].intersect(lines[j], intersections) << endl;
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
	sort(intersections.begin(), intersections.end(), CMP);
	//intersections.erase(unique(intersections.begin(), intersections.end()), intersections.end());
	int count = 1;
	for (unsigned i = 1; i < intersections.size(); i++)
	{
		if (!Myequal(intersections[i-1], intersections[i]))
		{
			count += 1;
		}
	}
	if (intersections.size() == 0) return 0;
	return count;
}

namespace test
{
	TEST_CLASS(TestLines)
	{
		TEST_METHOD(TestLines1)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 1, LINE));
			Assert::AreEqual(0, compute(lines, circles));
		}
		TEST_METHOD(TestLines2)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 1, LINE));
			lines.push_back(Line(0, 0, 1, -1, LINE));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(TestLines3)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 0, LINE));
			lines.push_back(Line(0, 0, 0, 1, LINE));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(TestLines4)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 1, LINE));
			lines.push_back(Line(0, 0, 1, 0, LINE));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(TestLines5)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 0, LINE));
			lines.push_back(Line(0, 1, 1, 1, LINE));
			lines.push_back(Line(0, 2, 1, 2, LINE));
			Assert::AreEqual(0, compute(lines, circles));
		}
		TEST_METHOD(TestLines6)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 0, LINE));
			lines.push_back(Line(0, 1, 1, 1, LINE));
			lines.push_back(Line(0, 0, 1, 2, LINE));
			Assert::AreEqual(2, compute(lines, circles));
		}
		TEST_METHOD(TestLines7)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 1, LINE));
			lines.push_back(Line(0, 0, 1, -1, LINE));
			lines.push_back(Line(0, 0, 1, 2, LINE));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(TestLines8)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 1, LINE));
			lines.push_back(Line(1, 0, 0, 1, LINE));
			lines.push_back(Line(1, 2, 2, 0, LINE));
			Assert::AreEqual(3, compute(lines, circles));
		}
		TEST_METHOD(TestLines9)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 0, LINE));
			lines.push_back(Line(0, 1, 1, 1, LINE));
			lines.push_back(Line(0, 2, 1, 2, LINE));
			lines.push_back(Line(0, -1, 1, 0, LINE));
			Assert::AreEqual(3, compute(lines, circles));
		}
		TEST_METHOD(TestLines10)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 1, LINE));
			lines.push_back(Line(1, 0, 0, 1, LINE));
			lines.push_back(Line(1, 2, 2, 0, LINE));
			lines.push_back(Line(0, -1, 2, 0, LINE));
			Assert::AreEqual(6, compute(lines, circles));
		}
		TEST_METHOD(TestLines11) {
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 1, LINE));
			Assert::AreEqual(0, compute(lines, circles));
		}
		TEST_METHOD(TestLines12) {
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 1, LINE));
			lines.push_back(Line(1, 0, 0, 1, LINE));
			lines.push_back(Line(1, 2, 2, 0, LINE));
			Assert::AreEqual(3, compute(lines, circles));
		}
		TEST_METHOD(TestLines13) {
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 1, LINE));
			lines.push_back(Line(0, 0, 0, 1, LINE));
			lines.push_back(Line(0, 0, -1, 0, LINE));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(TestLines14) {
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 1, 1, 0, LINE));
			lines.push_back(Line(1, 1, 1, 2, LINE));
			lines.push_back(Line(0, -1, 2, 1, LINE));
			lines.push_back(Line(0, 0, -1, 0, LINE));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(TestLines15) {
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 1, 1, 0, LINE));
			lines.push_back(Line(1, 1, 1, 2, LINE));
			lines.push_back(Line(0, -1, 2, 1, LINE));
			lines.push_back(Line(0, 0, -1, 0, LINE));
			lines.push_back(Line(0, 1, 1, 1, LINE));
			Assert::AreEqual(4, compute(lines, circles));
		}
	};

	TEST_CLASS(TestCircles)
	{
		TEST_METHOD(TestCircles1)
		{
			vector<Line> lines;
			vector<Circle> circles;
			circles.push_back(Circle(1, 0, 2));
			circles.push_back(Circle(2, 2, 1));
			circles.push_back(Circle(3, -2, 6));
			lines.push_back(Line(-1, 4, 4, -1, LINE));
			Assert::AreEqual(6, compute(lines, circles));
		}
		TEST_METHOD(TestCircles2)
		{
			vector<Line> lines;
			vector<Circle> circles; 
			circles.push_back(Circle(0, 0, 1));
			circles.push_back(Circle(2, 0, 1));
			lines.push_back(Line(1, 1, 1, 2, LINE));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(TestCircles3)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 1, 1, 0, LINE));
			lines.push_back(Line(1, 1, 1, 2, LINE));
			lines.push_back(Line(0, -1, 2, 1, LINE));
			lines.push_back(Line(0, 0, -1, 0, LINE));
			circles.push_back(Circle(0, 0, 1));
			circles.push_back(Circle(2, 0, 1));
			Assert::AreEqual(7, compute(lines, circles));
		}
		TEST_METHOD(TestCircles4)
		{
			vector<Line> lines;
			vector<Circle> circles;
			circles.push_back(Circle(0, 0, 1));
			circles.push_back(Circle(1, 0, 2));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(TestCircles5)
		{
			vector<Line> lines;
			vector<Circle> circles;
			circles.push_back(Circle(0, 0, 2));
			circles.push_back(Circle(2, 0, 2));
			lines.push_back(Line(1, 1, 1, 2, LINE));
			Assert::AreEqual(2, compute(lines, circles));
		}
	};
	TEST_CLASS(testAll)
	{
		TEST_METHOD(method1)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(-1, 3, 2, -1, SEGMENT));
			lines.push_back(Line(-3, 0, 4, 2, SEGMENT));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(method2)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(-1, 3, 2, -1, SEGMENT));
			lines.push_back(Line(-3, 0, -1, 1, SEGMENT));
			Assert::AreEqual(0, compute(lines, circles));
		}
		TEST_METHOD(method3)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(-1, 3, 2, -1, SEGMENT));
			lines.push_back(Line(-3, 0, -1, 1, RAY));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(method4)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(-1, 3, 2, -1, SEGMENT));
			lines.push_back(Line(-3, 0, 4, 2, RAY));
			lines.push_back(Line(-2, 2, 3, 0, LINE));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(method5)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(2, 4, 3, 2, SEGMENT));
			lines.push_back(Line(2, 5, -1, 2, RAY));
			lines.push_back(Line(-1, 4, 5, 2, LINE));
			circles.push_back(Circle(3, 3, 3));
			Assert::AreEqual(5, compute(lines, circles));
		}
		TEST_METHOD(method6)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(-37531, 49133, 36827, 63048, SEGMENT));
			lines.push_back(Line(-94720, -15556, 49289, 56287, SEGMENT));
			lines.push_back(Line(-60, 64526, -42292, -2447, LINE));
			lines.push_back(Line(87992, -20625, 83777, 88155, LINE));
			lines.push_back(Line(-77717, 69979, 7960, -84229, LINE));
			Assert::AreEqual(6, compute(lines, circles));
		}
		TEST_METHOD(method7)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 0, SEGMENT));
			circles.push_back(Circle(0, 0, 1));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(method8)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(-1, 0, 1, 0, SEGMENT));
			lines.push_back(Line(-1, 0, -2, 0, SEGMENT));
			circles.push_back(Circle(0, 0, 1));
			Assert::AreEqual(2, compute(lines, circles));
		}
		TEST_METHOD(method9)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(-1, 0, 0, 0, RAY));
			lines.push_back(Line(-1, 0, 0, 1, RAY));
			circles.push_back(Circle(0, 0, 1));
			Assert::AreEqual(3, compute(lines, circles));
		}
		TEST_METHOD(method10)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(2, 1, 2, 9, SEGMENT));
			lines.push_back(Line(-1, 0, 0, 1, RAY));
			lines.push_back(Line(2, 0, 0, 2, LINE));
			circles.push_back(Circle(0, 0, 2));
			Assert::AreEqual(5, compute(lines, circles));
		}
		TEST_METHOD(method11) {
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(-1, 1, 0, 1, SEGMENT));
			lines.push_back(Line(2, 0, 2, 2, SEGMENT));
			lines.push_back(Line(3, 2, 3, 3, RAY));
			lines.push_back(Line(0, -2, 3, 1, LINE));
			circles.push_back(Circle(2, 0, 2));
			circles.push_back(Circle(5, 0, 1));
			Assert::AreEqual(5, compute(lines, circles));
		}
		TEST_METHOD(method12)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 0, 1, SEGMENT));
			lines.push_back(Line(0, 0, 0, -1, RAY));
			Assert::AreEqual(1, compute(lines, circles));
		}
		TEST_METHOD(method13)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 0, 1, SEGMENT));
			lines.push_back(Line(0, 0, 0, 1, RAY));
			Assert::AreEqual(0, compute(lines, circles));
		}
		TEST_METHOD(method14)
		{
			vector<Line> lines;
			vector<Circle> circles;
			lines.push_back(Line(0, 0, 1, 1, SEGMENT));
			lines.push_back(Line(1, 1, 2, 2, SEGMENT));
			lines.push_back(Line(0, 0, -1, -1, RAY));
			lines.push_back(Line(3, 3, 2, 2, SEGMENT));
			Assert::AreEqual(3, compute(lines, circles));
		}
	};
	TEST_CLASS(testinterface)
	{
		TEST_METHOD(method1) 
		{
			vector<pair<double, double>> myIntersections;
			solve("../input.txt", myIntersections);
			int answer = myIntersections.size();
			Assert::AreEqual(6327238, answer);
		}
	};
}
