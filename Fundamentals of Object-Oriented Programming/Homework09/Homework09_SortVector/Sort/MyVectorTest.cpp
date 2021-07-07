#include "MyVectorTest.h"
#include "MyVector.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

void correctTest()
{
	MyVector<int> v;

	for (int i = 0; i < 10; ++i) v.push_back(i); // 0 1 2 3 4 5 6 7 8 9
	for (int i = 0; i < (int) v.size(); ++i) cout << v[i] << ' ';
	cout << endl;

	for (int i = 0; i < 5; ++i) v.pop_back();
	for (int i = 0; i < (int) v.size(); ++i) cout << v[i] << ' '; // 0 1 2 3 4
	cout << endl;

	MyVector<int> V(v);
	for (int i = 0; i < (int) V.size(); ++i) cout << V[i] << ' '; // 0 1 2 3 4
	cout << endl;

	V.erase(V.begin());
	for (int i = 0; i < (int) V.size(); ++i) cout << V[i] << ' '; // 1 2 3 4
	cout << endl;

	V.insert(V.end() - 2, 5);
	for (int i = 0; i < (int) V.size(); ++i) cout << V[i] << ' '; // 1 2 5 3 4
	cout << endl;

	V.front() = 5, V.back() = 3, V[1] = 4, V.at(3) = 4;
	for (int i = 0; i < (int) V.size(); ++i) cout << V[i] << ' '; // 5 4 5 4 3
	cout << endl;

	cout << V.empty();
	V.clear();
	cout << ' ' << V.empty() << endl;

	MyVector<int> w(v.begin() + 1, v.end() - 1); 
	for (int i = 0; i < (int)w.size(); ++i) cout << w[i] << ' '; // 1 2 3
	cout << endl;

	w.resize(5, 4);
	for (int i = 0; i < (int)w.size(); ++i) cout << w[i] << ' '; // 1 2 3 4 4
	cout << endl;

	w.resize(4);
	for (int i = 0; i < (int)w.size(); ++i) cout << w[i] << ' '; // 1 2 3 4
	cout << endl;

	V.swap(w);
	for (int i = 0; i < (int)V.size(); ++i) cout << V[i] << ' '; // 1 2 3 4
	cout << endl;

	v = V;
	for (int i = 0; i < (int)v.size(); ++i) cout << v[i] << ' '; // 1 2 3 4
	cout << endl;

	MyVector<int> W;
	for (int i = 0; i < (int)W.size(); ++i) cout << W[i] << ' '; // 
	cout << endl;

	MyVector<int> WW(6, 6);
	for (int i = 0; i < (int)WW.size(); ++i) cout << WW[i] << ' '; // 6 6 6 6 6 6
	cout << endl;
}

void MyVectorTest()
{
	MyVector<int> v1;
	vector<int> v2;
	srand(time(0));
	int c1, c2;

	correctTest();
	
	int pushBackTime1 = 0, pushBackTime2 = 0, clearTime1 = 0, clearTime2 = 0, popBackTime1 = 0, popBackTime2 = 0;
	for (int i = 0; i < 10; ++i)
	{
		c1 = clock();
		for (int i = 0; i < 1000000; ++i) v1.push_back(rand());
		c2 = clock();
		pushBackTime1 += c2 - c1;

		c1 = clock();
		for (int i = 0; i < 1000000; ++i) v2.push_back(rand());
		c2 = clock();
		pushBackTime2 += c2 - c1;

		c1 = clock();
		for (int i = 0; i < 1000000; ++i) v1.pop_back();
		c2 = clock();
		popBackTime1 += c2 - c1;

		c1 = clock();
		for (int i = 0; i < 1000000; ++i) v2.pop_back();
		c2 = clock();
		popBackTime2 += c2 - c1;

		c1 = clock();
		v1.clear();
		c2 = clock();
		clearTime1 += c2 - c1;

		c1 = clock();
		v2.clear();
		c2 = clock();
		clearTime2 += c2 - c1;
	}

	int insertTime1 = 0, insertTime2 = 0, eraseTime1 = 0, eraseTime2 = 0;
	for (int i = 0; i < 100; ++i)
	{
		c1 = clock();
		for (int i = 0; i < 10000; ++i) v1.insert(v1.begin() + rand() % (i + 1), rand());
		c2 = clock();
		insertTime1 += c2 - c1;

		c1 = clock();
		for (int i = 0; i < 10000; ++i) v2.insert(v2.begin() + rand() % (i + 1), rand());
		c2 = clock();
		insertTime2 += c2 - c1;

		c1 = clock();
		for (int i = 0; i < 10000; ++i) v1.erase(v1.begin() + rand() % (10000 - i));
		c2 = clock();
		eraseTime1 += c2 - c1;

		c1 = clock();
		for (int i = 0; i < 10000; ++i) v2.erase(v2.begin() + rand() % (10000 - i));
		c2 = clock();
		eraseTime2 += c2 - c1;
	}

	int initTime1 = 0, initTime2 = 0;
	for (int i = 0; i < 100; ++i)
	{
		c1 = clock();
		MyVector<int> V1(1000000, rand());
		c2 = clock();
		initTime1 += c2 - c1;

		c1 = clock();
		vector<int> V2(1000000, rand());
		c2 = clock();
		initTime2 += c2 - c1;
	}
	
	cout << "MyVector的push_back使用时间:" << (double)pushBackTime1 / 1000.0 << "s" << endl;
	cout << "vector的push_back使用时间:  " << (double)pushBackTime2 / 1000.0 << "s" << endl;
	cout << "MyVector的pop_back使用时间:" << (double)popBackTime1 / 1000.0 << "s" << endl;
	cout << "vector的pop_back使用时间:  " << (double)popBackTime2 / 1000.0 << "s" << endl;
	cout << "MyVector的clear使用时间:" << (double)clearTime1 / 1000.0 << "s" << endl;
	cout << "vector的clear使用时间:  " << (double)clearTime2 / 1000.0 << "s" << endl;
	cout << "MyVector的insert使用时间:" << (double)insertTime1 / 1000.0 << "s" << endl;
	cout << "vector的insert使用时间:  " << (double)insertTime2 / 1000.0 << "s" << endl;
	cout << "MyVector的erase使用时间:" << (double)eraseTime1 / 1000.0 << "s" << endl;
	cout << "vector的erase使用时间:  " << (double)eraseTime2 / 1000.0 << "s" << endl;
	cout << "MyVector的构造使用时间:" << (double)initTime1 / 1000.0 << "s" << endl;
	cout << "vector的构造使用时间:  " << (double)initTime2 / 1000.0 << "s" << endl;
}
