#ifndef CP_POSITIVEREAL_H
#define CP_POSITIVEREAL_H

class CP_PositiveReal
{
public:
	double m_data;

public:
	CP_PositiveReal() :m_data(0) {}
	~CP_PositiveReal() {}

	int mb_getInput(); // ����
	int mb_showData(); // ������ڵ�ֵ
};

#endif
