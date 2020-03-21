#pragma once
#include <iostream>
#include "Line.h"
#include "Circle.h"
#include <vector>
#include <fstream>
#include <string>
#include <ios>
#include <algorithm>

extern "C" _declspec(dllexport) void __cdecl solve(string input, string output, vector<pair<double, double>> &realIntersections);