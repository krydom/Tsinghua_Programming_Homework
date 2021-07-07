#ifndef CP_POSTIVEINTEGER_H
#define CP_POSTIVEINTEGER_H

class CP_PositiveInteger
{
public:
	int m_data;

public:
	CP_PositiveInteger():m_data(0) {}
	~CP_PositiveInteger() {}

	int mb_getInput(); // 输入
	int mb_showData(); // 输出现在的值

	int integerPlus(int plusNumber);          //加法
	int integerMultiply(int multiplyNumber);  //乘法

	int integerOddOrEven(); //判断奇偶性，偶数返回0奇数返回1
};

#endif
