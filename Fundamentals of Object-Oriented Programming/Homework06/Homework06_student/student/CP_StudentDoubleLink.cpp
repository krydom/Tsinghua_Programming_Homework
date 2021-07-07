#include "CP_StudentDoubleLink.h"
#include <iostream>

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