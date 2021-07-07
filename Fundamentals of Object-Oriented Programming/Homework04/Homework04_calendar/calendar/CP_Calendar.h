#ifndef CP_CALENDAR_H
#define CP_CALENDAR_H

class CP_Calendar
{
private:
	const int monthLength[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const int yearsDays400 = 146097; // 365 * 400 + 97

	int m_Year, m_Month, m_Day;
	int totalDays;     // ���������õ�x������ʾ����Ԫ1��1��1��Ϊ��1�죬��Ԫǰ1��12��31��Ϊ��0��
	bool calendarSet;  // �Ƿ��Ѿ�����ʱ��

	bool isLeapYear(int year);

public:
	CP_Calendar() { m_Year = m_Month = m_Day = calendarSet = 0; }
	CP_Calendar(int year, int month, int day) { m_Year = year, m_Month = month, m_Day = day, calendarSet = 1; }
	~CP_Calendar() {}
	
	void dateToDays(); // ������ת��������
	void daysToDate(); // ������ת��������

	void setCalendar(int year, int month, int day); // ����ʱ��
	void setTotalDays(int Days);                    // ���������� 

	void modifyDays(int Days);                      // �޸ĳ�n����ʱ��

	int showTotalDays();						    // ����������
	int showYear();								    // ��ȡ��
	int showMonth();								// ��ȡ��
	int showDay();								    // ��ȡ��

	void outputCalendar();                          // ���ʱ��
};

#endif
