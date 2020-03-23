#pragma once
#pragma warning (disable:4290)
#include <iostream>
#include "Line.h"
#include "Circle.h"
#include <vector>
#include <fstream>
#include <string>
#include <ios>
#include <algorithm>

_declspec(dllexport) void solve(vector<pair<double, double>> & realIntersections) throw(const char*);
_declspec(dllexport) void ioHandler(string input) throw(const char*);
_declspec(dllexport) void addLine(double x1, double y1, double x2, double y2, int type) throw(const char*);
_declspec(dllexport) void deleteLine(double x1, double y1, double x2, double y2, int type);
_declspec(dllexport) void addCircle(double c1, double c2, double r) throw(const char*);
_declspec(dllexport) void deleteCircle(double c1, double c2, double r);
_declspec(dllexport) void deleteAll();
_declspec(dllexport) vector<Line> getLines();
_declspec(dllexport) vector<Circle> getCircles();