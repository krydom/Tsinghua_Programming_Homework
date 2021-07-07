#include <iostream>
#include "CP_NaturalInteger.h"
#include "CP_PositiveReal.h"
#include "CP_RegularPolygon.h"
#include "CP_Circle.h"
#include "regularPolygonTest.h"

using namespace std;

void outputToolTips()
{
	cout << "������һ��0-5����Ȼ����ʾ��������" << endl;
	cout << "1) ����һ��������" << endl;
	cout << "2) ����һ��������" << endl;
	cout << "3) ����һ���������" << endl;
	cout << "4) ����һ����������" << endl;
	cout << "5) ����һ��Բ��" << endl;
	cout << "0) ��������������" << endl;
	cout << endl;
}

int main(int argc, char* args[])
{
	//regularPolygonTest1(); // ��������
	//system("pause");
	//regularPolygonTest2(); // ���Ĳ���

	double totalSquare = 0, totalPerimetre = 0;
	int polygonNumber = 0;

	outputToolTips();

	CP_NaturalInteger opt;

	opt.mb_getInput();
	while (opt.m_data > 5)
	{
		cout << "���������Ȼ��������5" << endl;
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
			cout << "���������Ȼ��������5" << endl;
			opt.mb_getInput();
		}
	}

	cout << endl;
	cout << "�����ͼ���ܸ����ǣ�" << polygonNumber << endl;
	cout << "����ͼ�ε����ܳ��ǣ�" << totalPerimetre << endl;
	cout << "����ͼ�ε�������ǣ�" << totalSquare << endl;

	system("pause");
	return 0;
}