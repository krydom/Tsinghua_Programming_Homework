#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "CP_StudentSystem.h"
#include "CP_Integer.h"

using namespace std;

void CP_StudentSystem::mb_printMainMenu()
{
	cout << "\n���˵�:\n";
	cout << "\t1: �������λѧ��(ѧ�ųɼ�)����0������\n";
	cout << "\t2: ɾ����1λָ��ѧ�ŵ�ѧ����\n";
	cout << "\t3: ɾ������ָ���ɼ���ѧ����\n";
	cout << "\t4: ��ʾ��1λָ��ѧ�ŵ�ѧ���ĳɼ���\n";
	cout << "\t5: ��ʾ����ָ���ɼ���ѧ����ѧ�š�\n";
	cout << "\t6: ��ʾ����ѧ����Ϣ��\n";
	cout << "\t-1: �˳���\n";
	cout << "������1��2��3��4��5��6 �� -1:";
}

void CP_StudentSystem::mb_printAllStudent()
{
	if (m_head == nullptr) 
	{
		cout << "Ŀǰ��û��ѧ����" << endl;
		return;
	}
	if (m_head->m_previous == nullptr)
	{
		cout << "Ŀǰ��û��ѧ����" << endl;
		return;
	}

	CP_StudentDoubleLink* p = m_head;
	int n = 1;
	do
	{
		cout << "[" << n << "]:ѧ��(" << p->m_data.m_ID << ")�� �ɼ�(" << p->m_data.m_score << ")" << endl;
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
		if ((opt.m_data < 1 || opt.m_data > 6) && opt.m_data != -1) cout << " ����:�����ʽ����!\n";
		switch (opt.m_data)
		{
		case 1: //�������λѧ��(ѧ�ųɼ�)����0������
			do
			{
				s.m_ID = 0;
				s.m_score = -1;
				cout << " ���ѧ����ѧ����ɼ�����0����:" << endl;

				cout << "��������λѧ����ѧ��:" << endl;
				id.mb_getInput();
				while (id.m_data < 0)
				{
					cout << "ѧ�Ų���С��0" << endl;
					id.mb_getInput();
				}
				s.m_ID = id.m_data;
				if (s.m_ID > 0)
				{
					cout << "��������λѧ���ĳɼ�:" << endl;
					score.mb_getInput();
					while (score.m_data < 0)
					{
						cout << "�ɼ�����С��0" << endl;
						score.mb_getInput();
					}
					s.m_score = score.m_data;

					bool fl = m_head->m_previous == nullptr;
					p = m_head->mb_findNodeById(s.m_ID);
					if (p != NULL) p->m_data.m_score = s.m_score;
					else
					{
						p = fac.getStudent(); // �򹤳��������½ڵ�
						if (p == nullptr) cout << "�ڴ�����ʧ��!" << endl;
						else
						{
							p->m_data = s;
							m_head->mb_insert(p);
						}
						if (fl) fac.insert(p); // ���նཨ�Ľڵ�
					}
				}
			} while (s.m_ID > 0);
			break;

		case 2: //ɾ����1λָ��ѧ�ŵ�ѧ����
			cout << "ɾ��ѧ������������λѧ����ѧ��:";
			id.mb_getInput();
			while (id.m_data <= 0)
			{
				cout << "ѧ�ű�����������" << endl;
				id.mb_getInput();
			}
			s.m_ID = id.m_data;
			p = m_head->mb_findNodeById(s.m_ID);
			if (p != NULL)
			{
				p = m_head->mb_deleteNode(p);
				if (p != nullptr) fac.insert(p); // ɾ����������������
			}
			else cout << "û���ҵ���ѧ�ŵ�ѧ����" << endl;
			break;

		case 3: //ɾ������ָ���ɼ���ѧ����
			cout << "ɾ��ѧ������������Щѧ���ĳɼ�:";
			score.mb_getInput();
			while (score.m_data < 0)
			{
				cout << "�ɼ�����С��0" << endl;
				id.mb_getInput();
			}
			p = m_head->mb_findNodeByScore(score.m_data);
			while (p != NULL)
			{
				p = m_head->mb_deleteNode(p);
				if (p != nullptr) fac.insert(p); // ɾ����������������
				p = m_head->mb_findNodeByScore(score.m_data);
			}
			cout << "�óɼ���ѧ��ȫ��ɾ����ϡ�" << endl;
			break;

		case 4: //��ʾ��1λָ��ѧ�ŵ�ѧ���ĳɼ���
			cout << "��������λѧ����ѧ��:";
			id.mb_getInput();
			while (id.m_data <= 0)
			{
				cout << "ѧ�ű�����������" << endl;
				id.mb_getInput();
			}
			p = m_head->mb_findNodeById(id.m_data);
			if (p != NULL) cout << "��λѧ���ĳɼ���:" << p->m_data.m_score << endl;
			else cout << "û���ҵ���ѧ�ŵ�ѧ����" << endl;
			break;

		case 5: //��ʾ����ָ���ɼ���ѧ����ѧ�š�
			cout << "�������ѯ��ѧ���ĳɼ�:";
			score.mb_getInput();
			while (score.m_data < 0)
			{
				cout << "�ɼ�����С��0" << endl;
				id.mb_getInput();
			}
			m_head->mb_outputNodeByScore(score.m_data);
			break;

		case 6: //��ʾ����ѧ����Ϣ��
			mb_printAllStudent();
			break;
		}
		cin.clear();
		cin.ignore();
	} while (opt.m_data != -1);

	delete m_head;    // �ͷ������ڴ�
	m_head = nullptr;
	fac.clear();
}
