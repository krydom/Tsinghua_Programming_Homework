#include <iostream>
#include "CP_CalculagraphByClock.h"

using namespace std;

CP_CalculagraphByClock::CP_CalculagraphByClock()
{
	m_timeStart = clock();
	m_timeEnd = m_timeStart;
}

void CP_CalculagraphByClock::timeStart()
{
	m_timeStart = clock();
}

void CP_CalculagraphByClock::timeEnd()
{
	m_timeEnd = clock();
}

void CP_CalculagraphByClock::timeReport()
{
	clock_t usedTimeClock = m_timeEnd - m_timeStart;
	double usedTimeSecond = (double)usedTimeClock / (double)CLOCKS_PER_SEC;
	if (usedTimeSecond >= 1)
	{
		cout << "所用的时间是" << usedTimeSecond << "秒。" << endl;
	}
	else
	{
		cout << "所用的时间是" << usedTimeClock / (CLOCKS_PER_SEC / 1000) << "毫秒。" << endl;
	}
}