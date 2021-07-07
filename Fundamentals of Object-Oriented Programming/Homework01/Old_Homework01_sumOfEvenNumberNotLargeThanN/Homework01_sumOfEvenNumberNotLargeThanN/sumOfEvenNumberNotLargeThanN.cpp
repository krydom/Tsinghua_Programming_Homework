#include "CP_PositiveInteger.h"
#include "sumOfEvenNumberNotLargeThanN.h"

int sumOfEvenNumberNotLargerThanN_1(CP_PositiveInteger data)
{
	int sum = 0;
	for (int i = 2; i <= data.m_data; i += 2)
	{
		sum += i;
	}
	return sum;
}

int sumOfEvenNumberNotLargerThanN_2(CP_PositiveInteger data)
{
	if (data.integerOddOrEven() == 0) // Å¼Êý
	{
		return (data.m_data + 2) * (data.m_data / 2) / 2;
	}
	else
	{
		return (data.m_data + 1) * (data.m_data / 2) / 2;
	}
}