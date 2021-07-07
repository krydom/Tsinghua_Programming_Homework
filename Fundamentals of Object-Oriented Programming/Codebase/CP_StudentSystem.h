#ifndef CP_ STUDENTSYSTEM_H
#define CP_ STUDENTSYSTEM_H

#include "CP_StudentDoubleLink.h"

class CP_StudentSystem
{
public:
	CP_StudentDoubleLink * m_head;

public:
	CP_StudentSystem() : m_head(nullptr) { }
	~CP_StudentSystem() { delete m_head; }
	void mb_printAllStudent();
	void mb_printMainMenu();
	void mb_run();
}; 

#endif
