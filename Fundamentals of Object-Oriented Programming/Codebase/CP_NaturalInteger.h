#ifndef CP_NATURALINTEGER_H
#define CP_NATURALINTEGER_H

class CP_NaturalInteger
{
public:
	int m_data;

public:
	CP_NaturalInteger():m_data(0) {}
	~CP_NaturalInteger() {}

	int mb_getInput(); // ����
	int mb_showData(); // ������ڵ�ֵ

	int integerPlus(int plusNumber);          //�ӷ�
	int integerMultiply(int multiplyNumber);  //�˷�

	int integerOddOrEven(); //�ж���ż�ԣ�ż������0��������1
};

#endif
