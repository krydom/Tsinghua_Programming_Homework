#ifndef CP_INTEGER_H
#define CP_INTEGER_H

class CP_Integer
{
public:
	int m_data;

public:
	CP_Integer():m_data(0) {}
	~CP_Integer() {}

	int mb_getInput(); // ����
	int mb_showData(); // ������ڵ�ֵ

	int integerPlus(int plusNumber);          //�ӷ�
	int integerMultiply(int multiplyNumber);  //�˷�

	int integerOddOrEven(); //�ж���ż�ԣ�ż������0��������1
};

#endif
