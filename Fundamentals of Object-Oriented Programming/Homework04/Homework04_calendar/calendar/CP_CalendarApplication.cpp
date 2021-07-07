#include "CP_Calendar.h"
#include "CP_CalendarApplication.h"
#include "CP_Integer.h"
#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

bool isLeapYear(int year) // �ж��Ƿ�������
{
	int yearAbs = year > 0 ? year : -year - 1;

	if (yearAbs % 4) return 0;   // ��4����һ����������
	if (yearAbs % 100) return 1; // ��4�ı���������100�ı���һ��������
	return !(yearAbs % 400);      // ��400�ı��������꣬���ǵĻ��Ͳ�������
}

CP_Calendar input()
{
	cout << "�Ƿ�ʹ�õ�ǰϵͳʱ�䣿1��ʾyes, 0��ʾno" << endl;
	CP_Integer fl;
	fl.mb_getInput();
	while (fl.m_data != 0 && fl.m_data != 1)
	{
		cout << "������0����1" << endl;
		fl.mb_getInput();
	}
	if (fl.m_data == 1)
	{
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		CP_Calendar CD(st.wYear, st.wMonth, st.wDay);
		cout << "��ǰ��";
		CD.outputCalendar();
		cout << endl;
		return CD;
	}
	cout << endl;

	int monthLength[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	CP_Integer year, month, day;

	cout << "���������(��Ԫǰ����������Ԫ���ø�����ʾ)" << endl;
	year.mb_getInput();
	while (year.m_data == 0)
	{
		cout << "��ݲ���Ϊ0������������" << endl;
		cout << "���������(��Ԫǰ����������Ԫ���ø�����ʾ)" << endl;
		year.mb_getInput();
	}
	cout << endl;

	cout << "�������·�(��1-12��������ʾ)" << endl;
	month.mb_getInput();
	while (month.m_data < 1 || month.m_data > 12)
	{
		cout << "��������·ݲ���1-12�ķ�Χ�ڣ�����������" << endl;
		cout << "�������·�(��1-12��������ʾ)" << endl;
		month.mb_getInput();
	}
	cout << endl;

	int monthDays = monthLength[month.m_data] + (month.m_data == 2 && isLeapYear(year.m_data));
	cout << "����������(��1-" << monthDays << "��������ʾ)" << endl;
	day.mb_getInput();
	while (day.m_data < 1 || day.m_data > monthDays)
	{
		cout << "����������ڲ���1-" << monthDays << "�ķ�Χ�ڣ�����������" << endl;
		cout << "����������(��1-" << monthDays << "��������ʾ)" << endl;
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
	cout << "������һ������n��ʾ���n��ǰ�ø�����ʾ" << endl;
	n.mb_getInput();
	CD.modifyDays(n.m_data);
	cout << endl << "n����";  // �����"�����ǡ���"
	CD.outputCalendar();
}