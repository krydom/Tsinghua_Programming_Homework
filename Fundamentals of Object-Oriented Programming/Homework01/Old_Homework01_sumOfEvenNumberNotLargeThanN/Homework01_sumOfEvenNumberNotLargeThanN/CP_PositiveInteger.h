#ifndef CP_POSTIVEINTEGER_H
#define CP_POSTIVEINTEGER_H

class CP_PositiveInteger
{
public:
	int m_data;

public:
	CP_PositiveInteger():m_data(0) {}
	~CP_PositiveInteger() {}

	int mb_getInput(); // ����
	int mb_showData(); // ������ڵ�ֵ

	int integerPlus(int plusNumber);          //�ӷ�
	int integerMultiply(int multiplyNumber);  //�˷�

	int integerOddOrEven(); //�ж���ż�ԣ�ż������0��������1
};

#endif
