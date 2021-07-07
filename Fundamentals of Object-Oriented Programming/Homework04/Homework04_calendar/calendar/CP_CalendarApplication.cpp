#include "CP_Calendar.h"
#include "CP_CalendarApplication.h"
#include "CP_Integer.h"
#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

bool isLeapYear(int year) // 判断是否是闰年
{
	int yearAbs = year > 0 ? year : -year - 1;

	if (yearAbs % 4) return 0;   // 非4倍数一定不是闰年
	if (yearAbs % 100) return 1; // 是4的倍数，不是100的倍数一定是闰年
	return !(yearAbs % 400);      // 是400的倍数是闰年，不是的话就不是闰年
}

CP_Calendar input()
{
	cout << "是否使用当前系统时间？1表示yes, 0表示no" << endl;
	CP_Integer fl;
	fl.mb_getInput();
	while (fl.m_data != 0 && fl.m_data != 1)
	{
		cout << "请输入0或者1" << endl;
		fl.mb_getInput();
	}
	if (fl.m_data == 1)
	{
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CP_Calendar CD(st.wYear, st.wMonth, st.wDay);
		cout << "当前的";
		CD.outputCalendar();
		cout << endl;
		return CD;
	}
	cout << endl;

	int monthLength[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	CP_Integer year, month, day;

	cout << "请输入年份(公元前用正数，公元后用负数表示)" << endl;
	year.mb_getInput();
	while (year.m_data == 0)
	{
		cout << "年份不能为0，请重新输入" << endl;
		cout << "请输入年份(公元前用正数，公元后用负数表示)" << endl;
		year.mb_getInput();
	}
	cout << endl;

	cout << "请输入月份(用1-12的整数表示)" << endl;
	month.mb_getInput();
	while (month.m_data < 1 || month.m_data > 12)
	{
		cout << "您输入的月份不在1-12的范围内，请重新输入" << endl;
		cout << "请输入月份(用1-12的整数表示)" << endl;
		month.mb_getInput();
	}
	cout << endl;

	int monthDays = monthLength[month.m_data] + (month.m_data == 2 && isLeapYear(year.m_data));
	cout << "请输入日期(用1-" << monthDays << "的整数表示)" << endl;
	day.mb_getInput();
	while (day.m_data < 1 || day.m_data > monthDays)
	{
		cout << "您输入的日期不在1-" << monthDays << "的范围内，请重新输入" << endl;
		cout << "请输入日期(用1-" << monthDays << "的整数表示)" << endl;
		day.mb_getInput();
	}
	cout << endl;

	CP_Calendar CD(year.m_data, month.m_data, day.m_data);
	return CD;
}

void calendar_run()
{
	CP_Calendar CD = input();
	CP_Integer n;
	cout << "请输入一个整数n表示天后，n天前用负数表示" << endl;
	n.mb_getInput();
	CD.modifyDays(n.m_data);
	cout << endl << "n天后的";  // 输出是"日期是……"
	CD.outputCalendar();
}