#pragma once
#include <set>
#include <utility>
#include <math.h>
#include <iostream>
#include <vector>
#include "const.h" 

using namespace std;

class UILine
{
public:
	UILine(double x1, double y1, double x2, double y2, int type);
	double x1;
	double y1;
	double x2;
	double y2;
	int type;
};