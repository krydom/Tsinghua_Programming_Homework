#include <cstdlib>
#include <ctime>
#include <iostream>
#include "CP_PositiveInteger.h"
#include "sumOfEvenNumberNotLargeThanN.h"

using namespace std;

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
		return (data.m_data + 2) / 2 * (data.m_data / 2);
	}
	else
	{
		return (data.m_data + 1) / 2 * (data.m_data / 2);
	}
}

void sumOfEvenNumberNotLargerThanNTest()
{
	while (1)
	{
		CP_PositiveInteger data;
		data.m_data = ((rand() << 15) | rand()) % 92681 + 1;
		if (sumOfEvenNumberNotLargerThanN_1(data) != sumOfEvenNumberNotLargerThanN_2(data))
		{
			cout << data.m_data << endl;
			system("pause");
			return;
		}
		cout << "Accepted!" << endl;
	}
}