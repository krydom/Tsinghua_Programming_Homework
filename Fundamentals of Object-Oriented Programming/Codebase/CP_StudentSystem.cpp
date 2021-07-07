#include <iostream>
#include "CP_StudentSystem.h"
#include "CP_Integer.h"

using namespace std;

void CP_StudentSystem::mb_printMainMenu()
{
	cout << "\n���˵�:\n";
	cout << "\t1: ��ָ���ļ��������\n";
	cout << "\t2: ���һλѧ��(ѧ�ųɼ�)��\n";
	cout << "\t3: ɾ����1λָ��ѧ�ŵ�ѧ����\n";
	cout << "\t4: ɾ������ѧ������Ϣ��\n";
	cout << "\t5: ����һλָ��ѧ��ѧ���ĳɼ���\n";
	cout << "\t6: ����ѧ�ţ������ѧ�Ŷ�Ӧ�ĳɼ���\n";
	cout << "\t7: ��ʾ���е�ѧ�ż����Ӧ�ĳɼ���\n";
	cout << "\t8: ����ɼ�����ָ���ļ���\n";
	cout << "\t-1: �˳���\n";
	cout << "������1��2��3��4��5��6��7��8 �� -1:";
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
		if ((opt.m_data < 1 || opt.m_data > 8) && opt.m_data != -1) cout << " ����:�����ʽ����!\n";
		switch (opt.m_data)
		{
		case 1: //��ָ���ļ��������
			m_head->mb_readFile();
			break;

		case 2: //���һλѧ��(ѧ�ųɼ�)��
			s.m_ID = 0;
			s.m_score = -1;
			cout << " ���ѧ����ѧ����ɼ�:" << endl;

			cout << "��������λѧ����ѧ��:" << endl;
			id.mb_getInput();
			while (id.m_data <= 0)
			{
				cout << "ѧ�Ų���С�ڵ���0" << endl;
				id.mb_getInput();
			}
			s.m_ID = id.m_data;
			p = m_head->mb_findNodeById(s.m_ID);
			if (p != NULL)
			{
				cout << "��ѧ���Ѿ����ڡ�" << endl;
				break;
			}
			cout << "��������λѧ���ĳɼ�:" << endl;
			score.mb_getInput();
			while (score.m_data < 0)
			{
				cout << "�ɼ�����С��0" << endl;
				score.mb_getInput();
			}
			s.m_score = score.m_data;

			p = m_head->mb_createNode(id.m_data);
			if (p != nullptr)
			{
				p->m_data = s;
			}
			else cout << "�ڴ�����ʧ��!" << endl;
			break;

		case 3: //ɾ����1λָ��ѧ�ŵ�ѧ����
			cout << "ɾ��ѧ������������λѧ����ѧ��:";
			id.mb_getInput();
			while (id.m_data <= 0)
			{
				cout << "ѧ�ű�����������" << endl;
				id.mb_getInput();
			}
			s.m_ID = id.m_data;
			p = m_head->mb_findNodeById(s.m_ID);
			if (p != NULL) m_head->mb_deleteNode(p);
			else cout << "û���ҵ���ѧ�ŵ�ѧ����" << endl;
			break;

		case 4: //ɾ������ѧ������Ϣ��
			delete m_head;
			m_head = new CP_StudentDoubleLink;
			cout << "����ѧ����Ϣɾ����ϡ�" << endl;
			break;

		case 5: //����һλָ��ѧ��ѧ���ĳɼ���
			s.m_ID = 0;
			s.m_score = -1;
			cout << " ����ѧ����ѧ����ɼ�:" << endl;
			cout << "��������λѧ����ѧ��:" << endl;
			id.mb_getInput();
			while (id.m_data <= 0)
			{
				cout << "ѧ�Ų���С�ڵ���0" << endl;
				id.mb_getInput();
			}
			s.m_ID = id.m_data;
			p = m_head->mb_findNodeById(s.m_ID);
			if (p == NULL)
			{
				cout << "û���ҵ���ѧ�ŵ�ѧ����" << endl;
				break;
			}
			cout << "��������λѧ���ĳɼ�:" << endl;
			score.mb_getInput();
			while (score.m_data < 0)
			{
				cout << "�ɼ�����С��0" << endl;
				score.mb_getInput();
			}
			s.m_score = score.m_data;

			p = m_head->mb_createNode(id.m_data);
			if (p != nullptr)
			{
				p->m_data = s;
			}
			else cout << "�ڴ�����ʧ��!" << endl;
			break;

		case 6: //����ѧ�ţ������ѧ�Ŷ�Ӧ�ĳɼ���
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

		case 7: //��ʾ���е�ѧ�ż����Ӧ�ĳɼ���
			mb_printAllStudent();
			break;

		case 8: //�������ָ���ļ���
			m_head->mb_writeFile();
			break;
		}
		
		cin.clear();
		cin.ignore();
	} while (opt.m_data != -1);

	delete m_head;
	m_head = nullptr;
}