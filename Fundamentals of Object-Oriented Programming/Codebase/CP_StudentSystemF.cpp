#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "CP_StudentSystem.h"
#include "CP_Integer.h"

using namespace std;

void CP_StudentSystem::mb_printMainMenu()
{
	cout << "\n主菜单:\n";
	cout << "\t1: 添加若干位学生(学号成绩)，以0结束。\n";
	cout << "\t2: 删除第1位指定学号的学生。\n";
	cout << "\t3: 删除所有指定成绩的学生。\n";
	cout << "\t4: 显示第1位指定学号的学生的成绩。\n";
	cout << "\t5: 显示所有指定成绩的学生的学号。\n";
	cout << "\t6: 显示所有学生信息。\n";
	cout << "\t-1: 退出。\n";
	cout << "请输入1、2、3、4、5、6 或 -1:";
}

void CP_StudentSystem::mb_printAllStudent()
{
	if (m_head == nullptr) 
	{
		cout << "目前还没有学生。" << endl;
		return;
	}
	if (m_head->m_previous == nullptr)
	{
		cout << "目前还没有学生。" << endl;
		return;
	}

	CP_StudentDoubleLink* p = m_head;
	int n = 1;
	do
	{
		cout << "[" << n << "]:学号(" << p->m_data.m_ID << ")， 成绩(" << p->m_data.m_score << ")" << endl;
		p = p->m_next;
		n++;
	}
	while (p != m_head);
}

void CP_StudentSystem::mb_run()
{
	m_head = new CP_StudentDoubleLink;
	if (m_head == nullptr) return;

	CP_Student s;
	CP_StudentDoubleLink* p;
	CP_Integer opt;
	CP_Integer id, score;

	do
	{
		mb_printMainMenu();
		opt.mb_getInput();
		if ((opt.m_data < 1 || opt.m_data > 6) && opt.m_data != -1) cout << " 错误:输入格式有误!\n";
		switch (opt.m_data)
		{
		case 1: //添加若干位学生(学号成绩)，以0结束。
			do
			{
				s.m_ID = 0;
				s.m_score = -1;
				cout << " 添加学生的学号与成绩，以0结束:" << endl;

				cout << "请输入这位学生的学号:" << endl;
				id.mb_getInput();
				while (id.m_data < 0)
				{
					cout << "学号不能小于0" << endl;
					id.mb_getInput();
				}
				s.m_ID = id.m_data;
				if (s.m_ID > 0)
				{
					cout << "请输入这位学生的成绩:" << endl;
					score.mb_getInput();
					while (score.m_data < 0)
					{
						cout << "成绩不能小于0" << endl;
						score.mb_getInput();
					}
					s.m_score = score.m_data;

					bool fl = m_head->m_previous == nullptr;
					p = m_head->mb_findNodeById(s.m_ID);
					if (p != NULL) p->m_data.m_score = s.m_score;
					else
					{
						p = fac.getStudent(); // 向工厂类申请新节点
						if (p == nullptr) cout << "内存申请失败!" << endl;
						else
						{
							p->m_data = s;
							m_head->mb_insert(p);
						}
						if (fl) fac.insert(p); // 回收多建的节点
					}
				}
			} while (s.m_ID > 0);
			break;

		case 2: //删除第1位指定学号的学生。
			cout << "删除学生，请输入这位学生的学号:";
			id.mb_getInput();
			while (id.m_data <= 0)
			{
				cout << "学号必须是正整数" << endl;
				id.mb_getInput();
			}
			s.m_ID = id.m_data;
			p = m_head->mb_findNodeById(s.m_ID);
			if (p != NULL)
			{
				p = m_head->mb_deleteNode(p);
				if (p != nullptr) fac.insert(p); // 删除后回收至工厂类表单
			}
			else cout << "没有找到该学号的学生。" << endl;
			break;

		case 3: //删除所有指定成绩的学生。
			cout << "删除学生，请输入这些学生的成绩:";
			score.mb_getInput();
			while (score.m_data < 0)
			{
				cout << "成绩不能小于0" << endl;
				id.mb_getInput();
			}
			p = m_head->mb_findNodeByScore(score.m_data);
			while (p != NULL)
			{
				p = m_head->mb_deleteNode(p);
				if (p != nullptr) fac.insert(p); // 删除后回收至工厂类表单
				p = m_head->mb_findNodeByScore(score.m_data);
			}
			cout << "该成绩的学生全部删除完毕。" << endl;
			break;

		case 4: //显示第1位指定学号的学生的成绩。
			cout << "请输入这位学生的学号:";
			id.mb_getInput();
			while (id.m_data <= 0)
			{
				cout << "学号必须是正整数" << endl;
				id.mb_getInput();
			}
			p = m_head->mb_findNodeById(id.m_data);
			if (p != NULL) cout << "这位学生的成绩是:" << p->m_data.m_score << endl;
			else cout << "没有找到该学号的学生。" << endl;
			break;

		case 5: //显示所有指定成绩的学生的学号。
			cout << "请输入查询的学生的成绩:";
			score.mb_getInput();
			while (score.m_data < 0)
			{
				cout << "成绩不能小于0" << endl;
				id.mb_getInput();
			}
			m_head->mb_outputNodeByScore(score.m_data);
			break;

		case 6: //显示所有学生信息。
			mb_printAllStudent();
			break;
		}
		cin.clear();
		cin.ignore();
	} while (opt.m_data != -1);

	delete m_head;    // 释放所有内存
	m_head = nullptr;
	fac.clear();
}
