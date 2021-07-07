#include <iostream>
#include "CP_NaturalInteger.h"
#include "CP_PositiveReal.h"
#include "CP_RegularPolygon.h"
#include "CP_Circle.h"
#include "regularPolygonTest.h"

using namespace std;

void outputToolTips()
{
	cout << "请输入一个0-5的自然数表示操作类型" << endl;
	cout << "1) 输入一个三角形" << endl;
	cout << "2) 输入一个正方形" << endl;
	cout << "3) 输入一个正五边形" << endl;
	cout << "4) 输入一个正六边形" << endl;
	cout << "5) 输入一个圆形" << endl;
	cout << "0) 结束程序，输出结果" << endl;
	cout << endl;
}

int main(int argc, char* args[])
{
	//regularPolygonTest1(); // 初步测试
	//system("pause");
	//regularPolygonTest2(); // 对拍测试

	double totalSquare = 0, totalPerimetre = 0;
	int polygonNumber = 0;

	outputToolTips();

	CP_NaturalInteger opt;

	opt.mb_getInput();
	while (opt.m_data > 5)
	{
		cout << "您输入的自然数超过了5" << endl;
		opt.mb_getInput();
	}
	while (opt.m_data != 0)
	{
		++polygonNumber;

		if (opt.m_data == 5)
		{
			CP_PositiveReal radius;
			CP_Circle cc;
			cc.initReport();
			radius.mb_getInput();
			cc.radius = radius.m_data;
			totalPerimetre += cc.perimeter();
			totalSquare += cc.square();
		}
		else
		{
			CP_PositiveReal length;
			CP_RegularPolygon rp(opt.m_data + 2);
			rp.initReport();
			length.mb_getInput();
			rp.sideLength = length.m_data;
			totalPerimetre += rp.perimeter();
			totalSquare += rp.square();
		}

		cout << endl;
		outputToolTips();
		opt.mb_getInput();
		while (opt.m_data > 5)
		{
			cout << "您输入的自然数超过了5" << endl;
			opt.mb_getInput();
		}
	}

	cout << endl;
	cout << "输入的图形总个数是：" << polygonNumber << endl;
	cout << "所有图形的总周长是：" << totalPerimetre << endl;
	cout << "所有图形的总面积是：" << totalSquare << endl;

	system("pause");
	return 0;
}