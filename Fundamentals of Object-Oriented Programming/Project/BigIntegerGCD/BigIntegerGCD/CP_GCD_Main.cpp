#include "CP_GCD_Test.h"
#include <iostream>

using namespace std;

int main(int argc, char* args[])
{
	while (true)
	{
		int opt;

		cout << endl;
		cout << "1 进行正确性的手动验证" << endl;
		cout << "2 进行正确性的自动验证" << endl;
		cout << "3 进行两种算法的时间测试" << endl;
		cout << "0 退出" << endl;
		cout << "请输入操作符:";
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