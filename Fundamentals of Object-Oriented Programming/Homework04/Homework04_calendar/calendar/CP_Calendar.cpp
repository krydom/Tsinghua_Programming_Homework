#include "CP_Calendar.h"
#include <algorithm>
#include <iostream>

using namespace std;

bool CP_Calendar::isLeapYear(int year) // �ж��Ƿ�������
{
	int yearAbs = year > 0 ? year : -year - 1;

	if (yearAbs % 4) return 0;   // ��4����һ����������
	if (yearAbs % 100) return 1; // ��4�ı���������100�ı���һ��������
	return !(yearAbs % 400);      // ��400�ı��������꣬���ǵĻ��Ͳ�������
}

void CP_Calendar::dateToDays() // ������ת��������
{
	int yearAbs = abs(m_Year);        // ����֮ǰ�����ж�����
	totalDays = (yearAbs - 1) / 400 * yearsDays400;
	int nowYear = (yearAbs - 1) / 400 * 400;
	for (int i = nowYear + 1; i < yearAbs; ++i)
		totalDays += isLeapYear((m_Year > 0) ? i : -i) ? 366 : 365;

	for (int i = (m_Year > 0 ? 1 : m_Month + 1); i <= (m_Year > 0 ? m_Month - 1 : 12); ++i) // ����֮ǰ�����ж�����
	{
		totalDays += monthLength[i];
		if (i == 2 && isLeapYear(m_Year)) totalDays++;
	}

	totalDays += m_Year > 0 ? m_Day : monthLength[m_Month] - m_Day + (m_Month == 2 && isLeapYear(m_Year)); // ����������ж�����

	if (m_Year < 0) totalDays = -totalDays;
}

void CP_Calendar::daysToDate()
{
	int Days = abs(totalDays);
	if (totalDays <= 0) Days++;

	m_Year = (Days - 1) / yearsDays400 * 400 + 1;
	Days -= (Days - 1) / yearsDays400 * yearsDays400;
	if (totalDays <= 0) m_Year = -m_Year;
	while (Days > (isLeapYear(m_Year) ? 366 : 365)) // ȷ������һ��
	{
		Days -= (isLeapYear(m_Year) ? 366 : 365);
		(totalDays > 0) ? m_Year++ : m_Year--;
	}
	
	m_Month = (totalDays > 0) ? 1 : 12;                                        // ȷ������һ��
	while (Days > monthLength[m_Month] + (m_Month == 2 && isLeapYear(m_Year)))
	{
		Days -= monthLength[m_Month] + (m_Month == 2 && isLeapYear(m_Year));
		(totalDays > 0) ? m_Month++ : m_Month--;
	}

	m_Day = (totalDays > 0) ? Days : monthLength[m_Month] + (m_Month == 2 && isLeapYear(m_Year)) - Days + 1; //ȷ������һ��
}

void CP_Calendar::setCalendar(int year, int month, int day) // ����ʱ��
{
	m_Year = year, m_Month = month, m_Day = day, calendarSet = 1;
}

void CP_Calendar::setTotalDays(int Days) // ����������
{
	totalDays = Days;
}

int CP_Calendar::showTotalDays()
{
	return totalDays;
}

int CP_Calendar::showYear()
{
	return m_Year;
}

int CP_Calendar::showMonth()
{
	return m_Month;
}

int CP_Calendar::showDay()
{
	return m_Day;
}

void CP_Calendar::outputCalendar() // ���ʱ��
{
	if (!calendarSet)
	{
		cout << "���ڻ�û�г�ʼ������" << endl;
		return;
	}
	cout << "�����ǣ���Ԫ";
	if (m_Year < 0) cout << "ǰ";
	cout << abs(m_Year) << "��" << m_Month << "��" << m_Day << "��" << endl;
}

void CP_Calendar::modifyDays(int Days)
{
	dateToDays();
	//cout << totalDays << endl; //������
	totalDays += Days;
	daysToDate();
}