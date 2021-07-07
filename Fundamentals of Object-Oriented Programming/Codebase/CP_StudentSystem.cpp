#include <iostream>
#include "CP_StudentSystem.h"
#include "CP_Integer.h"

using namespace std;

void CP_StudentSystem::mb_printMainMenu()
{
	cout << "\n主菜单:\n";
	cout << "\t1: 从指定文件输入表单。\n";
	cout << "\t2: 添加一位学生(学号成绩)。\n";
	cout << "\t3: 删除第1位指定学号的学生。\n";
	cout << "\t4: 删除所有学生的信息。\n";
	cout << "\t5: 更改一位指定学号学生的成绩。\n";
	cout << "\t6: 输入学号，输出该学号对应的成绩。\n";
	cout << "\t7: 显示所有的学号及其对应的成绩。\n";
	cout << "\t8: 输出成绩表单到指定文件。\n";
	cout << "\t-1: 退出。\n";
	cout << "请输入1、2、3、4、5、6、7、8 或 -1:";
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
		if ((opt.m_data < 1 || opt.m_data > 8) && opt.m_data != -1) cout << " 错误:输入格式有误!\n";
		switch (opt.m_data)
		{
		case 1: //从指定文件输入表单。
			m_head->mb_readFile();
			break;

		case 2: //添加一位学生(学号成绩)。
			s.m_ID = 0;
			s.m_score = -1;
			cout << " 添加学生的学号与成绩:" << endl;

			cout << "请输入这位学生的学号:" << endl;
			id.mb_getInput();
			while (id.m_data <= 0)
			{
				cout << "学号不能小于等于0" << endl;
				id.mb_getInput();
			}
			s.m_ID = id.m_data;
			p = m_head->mb_findNodeById(s.m_ID);
			if (p != NULL)
			{
				cout << "该学生已经存在。" << endl;
				break;
			}
			cout << "请输入这位学生的成绩:" << endl;
			score.mb_getInput();
			while (score.m_data < 0)
			{
				cout << "成绩不能小于0" << endl;
				score.mb_getInput();
			}
			s.m_score = score.m_data;

			p = m_head->mb_createNode(id.m_data);
			if (p != nullptr)
			{
				p->m_data = s;
			}
			else cout << "内存申请失败!" << endl;
			break;

		case 3: //删除第1位指定学号的学生。
			cout << "删除学生，请输入这位学生的学号:";
			id.mb_getInput();
			while (id.m_data <= 0)
			{
				cout << "学号必须是正整数" << endl;
				id.mb_getInput();
			}
			s.m_ID = id.m_data;
			p = m_head->mb_findNodeById(s.m_ID);
			if (p != NULL) m_head->mb_deleteNode(p);
			else cout << "没有找到该学号的学生。" << endl;
			break;

		case 4: //删除所有学生的信息。
			delete m_head;
			m_head = new CP_StudentDoubleLink;
			cout << "所有学生信息删除完毕。" << endl;
			break;

		case 5: //更改一位指定学号学生的成绩。
			s.m_ID = 0;
			s.m_score = -1;
			cout << " 输入学生的学号与成绩:" << endl;
			cout << "请输入这位学生的学号:" << endl;
			id.mb_getInput();
			while (id.m_data <= 0)
			{
				cout << "学号不能小于等于0" << endl;
				id.mb_getInput();
			}
			s.m_ID = id.m_data;
			p = m_head->mb_findNodeById(s.m_ID);
			if (p == NULL)
			{
				cout << "没有找到该学号的学生。" << endl;
				break;
			}
			cout << "请输入这位学生的成绩:" << endl;
			score.mb_getInput();
			while (score.m_data < 0)
			{
				cout << "成绩不能小于0" << endl;
				score.mb_getInput();
			}
			s.m_score = score.m_data;

			p = m_head->mb_createNode(id.m_data);
			if (p != nullptr)
			{
				p->m_data = s;
			}
			else cout << "内存申请失败!" << endl;
			break;

		case 6: //输入学号，输出该学号对应的成绩。
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

		case 7: //显示所有的学号及其对应的成绩。
			mb_printAllStudent();
			break;

		case 8: //输出表单到指定文件。
			m_head->mb_writeFile();
			break;
		}
		
		cin.clear();
		cin.ignore();
	} while (opt.m_data != -1);

	delete m_head;
	m_head = nullptr;
}