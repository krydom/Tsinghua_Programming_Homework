#include <iostream>
#include "CP_PositiveInteger.h"
#include "sumOfEvenNumberNotLargeThanN.h"

using namespace std;

int main(int argc, char* args[])
{
	CP_PositiveInteger data;
	data.mb_getInput();
	cout << "������n����ż��֮��Ϊ��" << endl;
	cout << "��һ�ַ������㣺" << sumOfEvenNumberNotLargerThanN_1(data) << endl;
	cout << "�ڶ��ַ������㣺" << sumOfEvenNumberNotLargerThanN_2(data) << endl;
	system("pause");
	return 0;
}