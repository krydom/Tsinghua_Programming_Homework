#include "CP_CalendarTest.h"
#include "CP_Calendar.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int random()
{
	return (rand() << 15) | rand();
}

void calendar_test()
{
	int monthLength[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	srand(time(0));
	CP_Calendar CD;
	while (1)
	{
		// 天数转换为日期，再转换回来
		int tmp = random() % 200000000 - 100000000; 
		CD.setTotalDays(tmp);
		CD.daysToDate();
		CD.dateToDays();
		if (tmp != CD.showTotalDays())
		{
			cout << tmp << ' ' << CD.showTotalDays() << endl;
			return;
		}
		else
		{
			cout << "Accepted!" << endl;
		}

		// 日期转换为天数，再转换回来
		int year = random() % 200000 - 100000; 
		while (year == 0) year = rand() % 200000 - 100000;
		int month = rand() % 12 + 1;
		int day = monthLength[month];
		int Tyear = year > 0 ? year : year + 1;
		if ((Tyear % 4 == 0 && (Tyear % 100 || Tyear % 400 == 0)) && month == 2) ++day;
		day = rand() % day + 1;

		CD.setCalendar(year, month, day);
		CD.dateToDays();
		CD.daysToDate();
		if (CD.showYear() != year || CD.showMonth() != month || CD.showDay() != day)
		{
			cout << year << ' ' << month << ' ' << day << endl;
			return;
		}
		else
		{
			cout << "Accepted!" << endl;
		}
	}
}