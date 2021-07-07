#include "CP_Calendar.h"
#include <algorithm>
#include <iostream>

using namespace std;

bool CP_Calendar::isLeapYear(int year) // 判断是否是闰年
{
	int yearAbs = year > 0 ? year : -year - 1;

	if (yearAbs % 4) return 0;   // 非4倍数一定不是闰年
	if (yearAbs % 100) return 1; // 是4的倍数，不是100的倍数一定是闰年
	return !(yearAbs % 400);      // 是400的倍数是闰年，不是的话就不是闰年
}

void CP_Calendar::dateToDays() // 将日期转化成天数
{
	int yearAbs = abs(m_Year);        // 计算之前的年有多少天
	totalDays = (yearAbs - 1) / 400 * yearsDays400;
	int nowYear = (yearAbs - 1) / 400 * 400;
	for (int i = nowYear + 1; i < yearAbs; ++i)
		totalDays += isLeapYear((m_Year > 0) ? i : -i) ? 366 : 365;

	for (int i = (m_Year > 0 ? 1 : m_Month + 1); i <= (m_Year > 0 ? m_Month - 1 : 12); ++i) // 计算之前的月有多少天
	{
		totalDays += monthLength[i];
		if (i == 2 && isLeapYear(m_Year)) totalDays++;
	}

	totalDays += m_Year > 0 ? m_Day : monthLength[m_Month] - m_Day + (m_Month == 2 && isLeapYear(m_Year)); // 计算这个月有多少天

	if (m_Year < 0) totalDays = -totalDays;
}

void CP_Calendar::daysToDate()
{
	int Days = abs(totalDays);
	if (totalDays <= 0) Days++;

	m_Year = (Days - 1) / yearsDays400 * 400 + 1;
	Days -= (Days - 1) / yearsDays400 * yearsDays400;
	if (totalDays <= 0) m_Year = -m_Year;
	while (Days > (isLeapYear(m_Year) ? 366 : 365)) // 确定在哪一年
	{
		Days -= (isLeapYear(m_Year) ? 366 : 365);
		(totalDays > 0) ? m_Year++ : m_Year--;
	}
	
	m_Month = (totalDays > 0) ? 1 : 12;                                        // 确定在哪一月
	while (Days > monthLength[m_Month] + (m_Month == 2 && isLeapYear(m_Year)))
	{
		Days -= monthLength[m_Month] + (m_Month == 2 && isLeapYear(m_Year));
		(totalDays > 0) ? m_Month++ : m_Month--;
	}

	m_Day = (totalDays > 0) ? Days : monthLength[m_Month] + (m_Month == 2 && isLeapYear(m_Year)) - Days + 1; //确定是哪一天
}

void CP_Calendar::setCalendar(int year, int month, int day) // 设置时间
{
	m_Year = year, m_Month = month, m_Day = day, calendarSet = 1;
}

void CP_Calendar::setTotalDays(int Days) // 设置总天数
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

void CP_Calendar::outputCalendar() // 输出时间
{
	if (!calendarSet)
	{
		cout << "现在还没有初始化日历" << endl;
		return;
	}
	cout << "日期是：公元";
	if (m_Year < 0) cout << "前";
	cout << abs(m_Year) << "年" << m_Month << "月" << m_Day << "日" << endl;
}

void CP_Calendar::modifyDays(int Days)
{
	dateToDays();
	//cout << totalDays << endl; //测试用
	totalDays += Days;
	daysToDate();
}