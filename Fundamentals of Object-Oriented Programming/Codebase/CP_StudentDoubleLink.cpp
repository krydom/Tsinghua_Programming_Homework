#include "CP_StudentDoubleLink.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

CP_StudentDoubleLink::~CP_StudentDoubleLink()
{
	if (m_previous == nullptr) return;
	m_previous->m_next = nullptr;
	delete m_next;
}

CP_StudentDoubleLink* CP_StudentDoubleLink::mb_createNode(int id)
{
	if (m_previous == nullptr) // 0��Ԫ�ص����
	{
		m_previous = this;
		m_next = this;
		return this;
	}
	if (m_data.m_ID == id) return this; // ѧ����ͬΪ�޸ĳɼ�
	if (m_data.m_ID > id) // ���Ӧ�ò��ڱ�ͷλ��
	{
		CP_Student tmp = m_data; // ���ر�ͷ��λ�ã���ԭ���ı�ͷ���²���
		m_data.m_ID = 0;
		CP_StudentDoubleLink* p;
		p = mb_createNode(tmp.m_ID);
		if (p != nullptr)
		{
			p->m_data = tmp;
		}
		else cout << "�ڴ�����ʧ��!" << endl;
		return this;
	}
	if (m_next->m_data.m_ID <= m_data.m_ID || (m_data.m_ID <= id && id < m_next->m_data.m_ID)) // �ҵ�����λ��
	{
		CP_StudentDoubleLink* pNew = nullptr;
		pNew = new CP_StudentDoubleLink;
		if (pNew == nullptr) return nullptr;
		CP_StudentDoubleLink* p = m_next;
		m_next = pNew;
		m_next->m_previous = this;
		p->m_previous = pNew;
		m_next->m_next = p;
		return pNew;
	}
	else return m_next->mb_createNode(id);
}

CP_StudentDoubleLink* CP_StudentDoubleLink::mb_findNodeById(int id)
{
	if (m_previous == nullptr) return nullptr;
	CP_StudentDoubleLink* p = this;
	do
	{
		if (p->m_data.m_ID == id) return p;
		p = p->m_previous;
	} while (p != this);
	return nullptr;
}

CP_StudentDoubleLink* CP_StudentDoubleLink::mb_findNodeByScore(int score)
{
	if (m_previous == nullptr) return nullptr;
	CP_StudentDoubleLink* p = this;
	do
	{
		if (p->m_data.m_score == score) return p;
		p = p->m_next;
	} while (p != this);
	return nullptr;
}

void CP_StudentDoubleLink::mb_outputNodeByScore(int score)
{
	cout << "�ɼ�Ϊ�˵�ѧ����ѧ����:" << endl;
	int n = 1;
	if (m_previous == nullptr) return;
	CP_StudentDoubleLink* p = this;
	do
	{
		if (p->m_data.m_score == score)
		{
			cout << "[" << n << "]: " << p->m_data.m_ID << endl;
			++n;
		}
		p = p->m_next;
	} while (p != this);
}

void CP_StudentDoubleLink::mb_deleteNode(CP_StudentDoubleLink* p)
{
	if (m_previous == nullptr) return;
	if (p == this)
	{
		if (p->m_previous == this)
		{
			p->m_previous = nullptr;
			return;
		}
		m_data = p->m_next->m_data; // next���Ƶ�this,ɾ��next
		p = p->m_next;
	}

	CP_StudentDoubleLink* q;
	for (q = m_next; (q != p) && (q != this);) // �ҵ�Ҫɾ���ĵ�
	{
		if (q != nullptr) q = q->m_next;
		else break;
	}
	if (q == this) return; // û���ҵ�
	if (q != p) return;

	q = p->m_previous;
	q->m_next = p->m_next;
	q = p->m_next;
	q->m_previous = p->m_previous;
	p->m_previous = p;
	delete p;
}

void CP_StudentDoubleLink::mb_readFile()
{
	CP_Student s;
	CP_StudentDoubleLink* p;
	bool openSuc = 0;
	char filename[100];
	vector<int> m_data;
	openSuc = 0;
	char c = cin.get();
	while (c != '\n') c = cin.get(); // ȥ��ǰ������Ļس�
	do
	{
		cout << "������һ���ļ���:" << endl;
		cin.clear();
		cin.getline(filename, 100);
		ifstream fileObject(filename);
		if (fileObject.fail())
		{
			cout << "�ļ�" << filename << "��ʧ�ܡ�\n";
		}
		else openSuc = 1;
	} while (openSuc == 0);

	m_data.clear();
	ifstream fileObject(filename);
	do
	{
		int tmp = -1;
		fileObject >> tmp;
		if (fileObject.good())
			if (tmp < 0 || (tmp == 0 && m_data.size() % 3 == 1)) continue;
			else m_data.push_back(tmp);
		else
		{
			fileObject.clear();
			char c = fileObject.get();
		}
	} while (!fileObject.eof());

	for (int i = 0; i + 2 < m_data.size(); i += 3)
	{
		s.m_ID = m_data[i + 1];
		s.m_score = m_data[i + 2];
		p = mb_createNode(s.m_ID);
		if (p != nullptr)
		{
			p->m_data = s;
		}
		else cout << "�ڴ�����ʧ��!" << endl;
	}
	cout << "��" << filename << "������ɹ������س�������\n";
}

void CP_StudentDoubleLink::mb_writeFile()
{
	bool openSuc = 0;
	char filename[100];
	char c = cin.get();
	while (c != '\n') c = cin.get(); // ȥ��ǰ������Ļس�
	do
	{
		cout << "������һ���ļ���:" << endl;
		cin.getline(filename, 100);
		ofstream fileObject(filename);
		if (fileObject.fail())
		{
			cout << "�ļ�" << filename << "��ʧ�ܡ�\n";
		}
		else openSuc = 1;
	} while (openSuc == 0);
	ofstream fileObject(filename);
	CP_StudentDoubleLink* p = this;
	if (p == nullptr || p->m_previous == nullptr)
	{
		cout << "�������" << filename << "�ɹ������س�������\n";
		return;
	}
	int n = 1;
	do
	{
		fileObject << "[" << n << "]:ѧ��(" << p->m_data.m_ID << ")�� �ɼ�(" << p->m_data.m_score << ")" << endl;
		p = p->m_next;
		n++;
	} while (p != this);
	cout << "�������" <<  filename << "�ɹ������س�������\n";
}