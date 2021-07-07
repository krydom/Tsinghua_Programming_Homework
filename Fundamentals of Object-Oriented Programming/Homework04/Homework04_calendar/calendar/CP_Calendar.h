#ifndef CP_CALENDAR_H
#define CP_CALENDAR_H

class CP_Calendar
{
private:
	const int monthLength[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const int yearsDays400 = 146097; // 365 * 400 + 97

	int m_Year, m_Month, m_Day;
	int totalDays;     // 将年月日用第x天来表示，公元1年1月1日为第1天，公元前1年12月31日为第0天
	bool calendarSet;  // 是否已经设置时间

	bool isLeapYear(int year);

public:
	CP_Calendar() { m_Year = m_Month = m_Day = calendarSet = 0; }
	CP_Calendar(int year, int month, int day) { m_Year = year, m_Month = month, m_Day = day, calendarSet = 1; }
	~CP_Calendar() {}
	
	void dateToDays(); // 将日期转化成天数
	void daysToDate(); // 将天数转化成日期

	void setCalendar(int year, int month, int day); // 设置时间
	void setTotalDays(int Days);                    // 设置总天数 

	void modifyDays(int Days);                      // 修改成n天后的时间

	int showTotalDays();						    // 返回总天数
	int showYear();								    // 获取年
	int showMonth();								// 获取月
	int showDay();								    // 获取日

	void outputCalendar();                          // 输出时间
};

#endif
