#include "CP_GCD_Test.h"
#include <iostream>

using namespace std;

int main(int argc, char* args[])
{
	while (true)
	{
		int opt;

		cout << endl;
		cout << "1 ������ȷ�Ե��ֶ���֤" << endl;
		cout << "2 ������ȷ�Ե��Զ���֤" << endl;
		cout << "3 ���������㷨��ʱ�����" << endl;
		cout << "0 �˳�" << endl;
		cout << "�����������:";
		cin >> opt;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl;

		if (opt == 1) gcdManualTest();
		if (opt == 2) gcdAutoTest();
		if (opt == 3) gcdTimeTest();
		if (opt == 0) break;
	}
	return 0;
}