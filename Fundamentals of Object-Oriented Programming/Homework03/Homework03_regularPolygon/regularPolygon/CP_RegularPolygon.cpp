#include "CP_RegularPolygon.h"
#include <iostream>
#include <cmath>
#define PI 3.1415926535897932384626

using namespace std;

double CP_RegularPolygon::square()
{
	double high = sideLength / 2.0 / tan(PI / sideNumber);
	return sideLength * high / 2.0 * sideNumber;
}

double CP_RegularPolygon::perimeter()
{
	return sideLength * sideNumber;
}

void CP_RegularPolygon::initReport()
{
	switch (sideNumber)
	{
	case 3 : 
		cout << "请输入正三角形的边长" << endl;
		break;
	case 4 : 
		cout << "请输入正方形的边长" << endl;
		break;
	case 5 : 
		cout << "请输入正五边形的边长" << endl;
		break;
	case 6 : 
		cout << "请输入正六边形的边长" << endl;
		break;
	}
}