#include "CP_Circle.h"
#include <iostream>
#define PI 3.1415926535897932384626

using namespace std;

double CP_Circle::square()
{
	return PI * radius * radius;
}

double CP_Circle::perimeter()
{
	return PI * radius * 2;
}

void CP_Circle::initReport()
{
	cout << "ÇëÊäÈëÔ²ÐÎµÄ°ë¾¶" << endl;
}