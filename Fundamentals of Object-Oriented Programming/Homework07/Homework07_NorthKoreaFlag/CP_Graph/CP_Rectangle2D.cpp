#include "pch.h"
#include "CP_Rectangle2D.h"

CP_Rectangle2D::CP_Rectangle2D()
{
	m_leftUpperPoint.m_x = m_leftUpperPoint.m_y = m_height = m_width = 0.0;
}

CP_Rectangle2D::CP_Rectangle2D(double x, double y, double w, double h)
{
	m_leftUpperPoint.m_x = x, m_leftUpperPoint.m_y = y;
	m_width = w, m_height = h;
}

CP_Rectangle2D::~CP_Rectangle2D()
{
}

void CP_Rectangle2D::gb_moveRectangle(int x, int y)
{
	m_leftUpperPoint.m_x += x, m_leftUpperPoint.m_y += y;
}

void gb_brushRectangle(CDC* pDC, CP_Rectangle2D& r, COLORREF color) // 实心矩形
{
	HGDIOBJ oldObj = pDC->SelectObject(GetStockObject(DC_BRUSH));
	COLORREF oldBrushColor = pDC->SetDCBrushColor(color);
	CPen *oldPen;
	oldPen = (CPen*)pDC->SelectStockObject(NULL_PEN); // 去除边框
	pDC->Rectangle(r.m_leftUpperPoint.m_x, r.m_leftUpperPoint.m_y, r.m_leftUpperPoint.m_x + r.m_width, r.m_leftUpperPoint.m_y + r.m_height);
	pDC->SetDCBrushColor(oldBrushColor);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldObj);
}

void gb_drawRectangle(CDC* pDC, CP_Rectangle2D& r, COLORREF color) // 空心矩形
{
	HGDIOBJ oldObj = pDC->SelectObject(GetStockObject(DC_PEN));
	COLORREF oldPenColor = pDC->SetDCPenColor(color);
	pDC->MoveTo(r.m_leftUpperPoint.m_x, r.m_leftUpperPoint.m_y);
	pDC->LineTo(r.m_leftUpperPoint.m_x + r.m_width - 1, r.m_leftUpperPoint.m_y);
	pDC->LineTo(r.m_leftUpperPoint.m_x + r.m_width - 1, r.m_leftUpperPoint.m_y + r.m_height - 1);
	pDC->LineTo(r.m_leftUpperPoint.m_x, r.m_leftUpperPoint.m_y + r.m_height - 1);
	pDC->LineTo(r.m_leftUpperPoint.m_x, r.m_leftUpperPoint.m_y);
	pDC->SetDCPenColor(oldPenColor);
	pDC->SelectObject(oldObj);
}