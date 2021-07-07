#include "FactoryMethodExtend.h"
#include "FactoryMethodStudent.h"

void FactoryMethodExtend::clear()
{
	delete m_head;
	m_head = nullptr;
}

CP_StudentDoubleLink* FactoryMethodExtend::getStudent()
{
	if (m_head != nullptr && m_head->m_previous != nullptr) // 非空，取走头元素
	{
		if (m_head->m_previous == m_head)
		{
			CP_StudentDoubleLink* p = m_head;
			m_head = nullptr;
			return p;
		}

		m_head->m_previous->m_next = m_head->m_next;
		m_head->m_next->m_previous = m_head->m_previous;
		CP_StudentDoubleLink* p = m_head;
		m_head = m_head->m_previous;
		return p;
	}

	CP_StudentDoubleLink* s; // 空，申请新节点
	CP_FactoryMethodStudent<CP_StudentDoubleLink> t;
	s = t.mb_createInstance();
	return s;
}

void FactoryMethodExtend::insert(CP_StudentDoubleLink* p) // 将废弃的元素回收，插入在头元素的后面
{
	if (m_head == nullptr)
	{
		m_head = p;
		p->m_previous = p->m_next = p;
		return;
	}
	if (m_head->m_previous == nullptr)
	{
		m_head = p;
		p->m_previous = p->m_next = p;
		return;
	}

	p->m_previous = m_head;
	p->m_next = m_head->m_next;
	m_head->m_next->m_previous = p;
	m_head->m_next = p;
}