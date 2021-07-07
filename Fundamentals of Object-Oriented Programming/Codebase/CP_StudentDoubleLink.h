#ifndef CP_STUDENTDOUBLELINK_H
#define CP_STUDENTDOUBLELINK_H

#include "CP_student.h"

class CP_StudentDoubleLink
{
public:
	CP_Student m_data;
	CP_StudentDoubleLink* m_previous;
	CP_StudentDoubleLink* m_next;

public:
	CP_StudentDoubleLink() : m_previous(nullptr), m_next(nullptr) {}
	~CP_StudentDoubleLink();

	CP_StudentDoubleLink* mb_createNode(int id);
	CP_StudentDoubleLink* mb_findNodeById(int id);
	CP_StudentDoubleLink* mb_findNodeByScore(int score);
	void mb_deleteNode(CP_StudentDoubleLink* p);
	void mb_outputNodeByScore(int score);
	void mb_readFile();
	void mb_writeFile();
};

#endif
