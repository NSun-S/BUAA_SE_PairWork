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

extern "C" _declspec(dllexport) void __cdecl solve(vector<pair<double, double>> & realIntersections) throw(const char*);
extern "C" _declspec(dllexport) void __cdecl ioHandler(string input) throw(const char*);
extern "C" _declspec(dllexport) void __cdecl addLine(double x1, double y1, double x2, double y2, int type) throw(const char*);
extern "C" _declspec(dllexport) void __cdecl deleteLine(double x1, double y1, double x2, double y2, int type);
extern "C" _declspec(dllexport) void __cdecl addCircle(double c1, double c2, double r) throw(const char*);
extern "C" _declspec(dllexport) void __cdecl deleteCircle(double c1, double c2, double r);
extern "C" _declspec(dllexport) void __cdecl deleteAll();