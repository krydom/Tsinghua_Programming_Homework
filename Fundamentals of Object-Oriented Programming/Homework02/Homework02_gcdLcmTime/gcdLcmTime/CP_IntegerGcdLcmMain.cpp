#include <iostream>
#include <windows.h>
#include "CP_CalculagraphByClock.h"
#include "CP_IntegerGcdLcm.h"
#include "CP_PositiveInteger.h"

using namespace std;

int main(int argc, char* args[])
{
	//integerGcdCheck1();      // gcd验证方案1
	//integerGcdCheck2(10000);    // gcd验证方案2，参数为随机次数,-1表示不断随机

	CP_PositiveInteger a, b;
	cout << "请先输入一个正整数a的值" << endl;
	a.mb_getInput();
	cout << "然后输入一个正整数b的值" << endl;
	b.mb_getInput();
	cout << endl;

	CP_CalculagraphByClock cal;
	int tmp = 0;

	cal.timeStart();
	tmp = integerGcd(a.m_data, b.m_data);
	//Sleep(1919); // 计时验证用
	cal.timeEnd();
	cout << "a和b的最大公约数是：" << tmp << endl;
	cal.timeReport();
	cout << endl;

	cal.timeStart();
	tmp = integerLcm(a.m_data, b.m_data);
	//Sleep(810); // 计时验证用
	cal.timeEnd();
	cout << "a和b的最小公倍数是：" << tmp << endl;
	cal.timeReport();

	system("pause");
	return 0;
}