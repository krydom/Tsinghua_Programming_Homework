#include <iostream>
#include <windows.h>
#include "CP_CalculagraphByClock.h"
#include "CP_IntegerGcdLcm.h"
#include "CP_PositiveInteger.h"

using namespace std;

int main(int argc, char* args[])
{
	//integerGcdCheck1();      // gcd��֤����1
	//integerGcdCheck2(10000);    // gcd��֤����2������Ϊ�������,-1��ʾ�������

	CP_PositiveInteger a, b;
	cout << "��������һ��������a��ֵ" << endl;
	a.mb_getInput();
	cout << "Ȼ������һ��������b��ֵ" << endl;
	b.mb_getInput();
	cout << endl;

	CP_CalculagraphByClock cal;
	int tmp = 0;

	cal.timeStart();
	tmp = integerGcd(a.m_data, b.m_data);
	//Sleep(1919); // ��ʱ��֤��
	cal.timeEnd();
	cout << "a��b�����Լ���ǣ�" << tmp << endl;
	cal.timeReport();
	cout << endl;

	cal.timeStart();
	tmp = integerLcm(a.m_data, b.m_data);
	//Sleep(810); // ��ʱ��֤��
	cal.timeEnd();
	cout << "a��b����С�������ǣ�" << tmp << endl;
	cal.timeReport();

	system("pause");
	return 0;
}