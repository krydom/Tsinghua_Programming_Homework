#include "regularPolygonTest.h"
#include "CP_RegularPolygon.h"
#include "CP_Circle.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

void regularPolygonTest1() // ≥ı≤Ω≤‚ ‘
{
	for (int i = 3; i <= 6; ++i)
	{
		CP_RegularPolygon rp(i, 1);
		cout << rp.perimeter() << ' ' << rp.square() << endl;
	}
	CP_Circle cc(1);
	cout << cc.perimeter() << ' ' << cc.square() << endl;
}

bool equiv(double a, double b)
{
	return fabs(a - b) / a < 1e-9;
}

void regularPolygonTest2() // ∂‘≈ƒ≤‚ ‘
{
	srand(time(0));
	while (1)
	{
		int type = rand() % 5 + 1;
		double length = (double)rand() + 1;
		if (type <= 4)
		{
			CP_RegularPolygon rp1(type, 1), rpa(type, length);
			if (!equiv(rp1.perimeter() * length, rpa.perimeter()) || !equiv(rp1.square() * length * length, rpa.square()))
			{
				cout << type << ' ' << length << endl;
				return;
			}
		}
		else
		{
			CP_Circle cc1(1), cca(length);
			if (!equiv(cc1.perimeter() * length, cca.perimeter()) || !equiv(cc1.square() * length * length, cca.square()))
			{
				cout << type << ' ' << length << endl;
				return;
			}
		}
		cout << "Accepted!" << endl;
	}
}