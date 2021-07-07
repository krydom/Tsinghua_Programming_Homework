#ifndef CP_POSITIVEREAL_H
#define CP_POSITIVEREAL_H

class CP_PositiveReal
{
public:
	double m_data;

public:
	CP_PositiveReal() :m_data(0) {}
	~CP_PositiveReal() {}

	int mb_getInput(); // 输入
	int mb_showData(); // 输出现在的值
};

#endif
