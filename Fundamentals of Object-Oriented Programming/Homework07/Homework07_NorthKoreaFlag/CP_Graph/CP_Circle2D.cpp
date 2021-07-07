#include "pch.h"
#include "CP_Circle2D.h"

CP_Circle2D::CP_Circle2D()
{
	m_center.m_x = m_center.m_y = m_radius = 0.0;
}

CP_Circle2D::CP_Circle2D(double x, double y, double r)
{
	m_center.m_x = x;
	m_center.m_y = y;
	m_radius = r;
}

CP_Circle2D::~CP_Circle2D()
{
}

void gb_brushCircle(CDC* pDC, CP_Circle2D& r, COLORREF color)
{
	HGDIOBJ oldObj = pDC->SelectObject(GetStockObject(DC_BRUSH));
	COLORREF oldBrushColor = pDC->SetDCBrushColor(color);
	CPen* oldPen;
	oldPen = (CPen*)pDC->SelectStockObject(NULL_PEN); // È¥³ý±ß¿ò
	pDC->Ellipse(r.m_center.m_x - r.m_radius, r.m_center.m_y - r.m_radius, r.m_center.m_x + r.m_radius, r.m_center.m_y + r.m_radius);
	pDC->SetDCBrushColor(oldBrushColor);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldObj);
}
