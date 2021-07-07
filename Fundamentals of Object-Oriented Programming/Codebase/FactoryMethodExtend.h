#ifndef FACTORYMETHODEXTEND_H
#define FACTORYMETHODEXTEND_H

#include "CP_StudentDoubleLink.h"

class FactoryMethodExtend
{
public:
	CP_StudentDoubleLink* m_head;

	CP_StudentDoubleLink* getStudent();
	void insert(CP_StudentDoubleLink* p);
	void clear();
};

#endif // !FACTORYMETHODEXTEND_H

