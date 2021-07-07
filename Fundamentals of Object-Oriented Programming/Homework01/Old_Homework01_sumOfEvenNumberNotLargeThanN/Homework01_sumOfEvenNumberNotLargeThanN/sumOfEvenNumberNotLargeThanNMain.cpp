#include <iostream>
#include "CP_PositiveInteger.h"
#include "sumOfEvenNumberNotLargeThanN.h"

using namespace std;

int main(int argc, char* args[])
{
	CP_PositiveInteger data;
	data.mb_getInput();
	cout << "不超过n的正偶数之和为：" << endl;
	cout << "第一种方法计算：" << sumOfEvenNumberNotLargerThanN_1(data) << endl;
	cout << "第二种方法计算：" << sumOfEvenNumberNotLargerThanN_2(data) << endl;
	system("pause");
	return 0;
}