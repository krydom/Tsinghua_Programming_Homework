#include "CP_PositiveInteger.h"
#include "IntegerSort.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <ctime>
#include <cstdlib>

using namespace std;

int a[1000010];


void test()
{
	
	srand(time(0));
	while (1)
	{
		set<int> S;
		for (int i = 0; i < 100000; ++i)
		{
			int x = rand();
			a[i] = x, S.insert(x);
		}
		sort(a, a + 100000);
		int n = unique(a, a + 100000) - a;
		
		bool fl = 0;
		set<int>::iterator it;
		int i = 0;
		for (it = S.begin(); it != S.end(); it++, ++i)
		{
			if ((*it) != a[i]) { puts("WA!"); return; }
		}
		if (i != n) { puts("WA!"); return; }
		puts("Accepted!");
	}
}

void Sort()
{
	//test(); ���Ĳ���

	CP_PositiveInteger n; 
	n.mb_getInput(); 
	cout << "��������Ҫ�������:" << endl;
	for (int i = 0; i < n.m_data; ++i) cin >> a[i];

	cout << "��ȥ������:" << endl;
	sort(a, a + n.m_data); // ��ȥ������
	for (int i = 0; i < n.m_data; ++i) cout << a[i] << ' ';
	cout << endl;

	cout << "ȥ������:" << endl;
	set<int> S;  // ȥ������
	for (int i = 0; i < n.m_data; ++i) S.insert(a[i]);
	set<int>::iterator it;
	for (it = S.begin(); it != S.end(); it++) cout << *it << ' ';
	cout << endl;
}