#ifndef FACTORYMETHODSTUDENT_H
#define FACTORYMETHODSTUDENT_H

#include "CP_StudentDoubleLink.h"

class CP_FactoryMethodStudentInterface
{
public:
	virtual ~CP_FactoryMethodStudentInterface() {}
	virtual CP_StudentDoubleLink* mb_createInstance() = 0;
};

template <typename T_ProductType>
class CP_FactoryMethodStudent : public CP_FactoryMethodStudentInterface
{
public:
	virtual T_ProductType* mb_createInstance()
	{
		T_ProductType* s = new T_ProductType;
		return s;
	} // ��Ա����mb_createInstance �������};
};

#endif // !FACTORYMETHODSTUDENT_H
