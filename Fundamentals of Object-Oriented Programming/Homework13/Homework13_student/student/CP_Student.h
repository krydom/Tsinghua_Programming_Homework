#ifndef CP_STUDENT_H
#define CP_STUDENT_H

class CP_Student
{
public:
	int m_ID, m_score;

public:
	CP_Student(int id = 0, int score = 100) : m_ID(id), m_score(score) {}
	~CP_Student() {}
};

#endif