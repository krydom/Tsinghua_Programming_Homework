#ifndef CP_CALCULAGRAPHBYCLOCK_H
#define CP_CALCULAGRAPHBYCLOCK_H

#include <ctime>

class CP_CalculagraphByClock
{
private:
	clock_t m_timeStart, m_timeEnd;

public:
	CP_CalculagraphByClock();
	~CP_CalculagraphByClock() {}

	void timeStart();
	void timeEnd();
	void timeReport();
};

#endif