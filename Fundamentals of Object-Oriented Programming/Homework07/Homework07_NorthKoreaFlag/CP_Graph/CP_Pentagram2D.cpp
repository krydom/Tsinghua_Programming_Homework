#include "pch.h"
#include "CP_Pentagram2D.h"
#include <cmath>

CP_Pentagram2D::CP_Pentagram2D()
{
	m_center.m_x = m_center.m_y = m_radius = m_angle = 0.0;
}

CP_Pentagram2D::CP_Pentagram2D(double x, double y, double r, double a = 0)
{
	m_center.m_x = x, m_center.m_y = y;
	m_radius = r, m_angle = a;
}

CP_Pentagram2D::~CP_Pentagram2D()
{
}

void gb_brushPentagram(CDC* pDC, CP_Pentagram2D& p, COLORREF color)
{
	const double pi = acos(-1);
	double smallRadius = p.m_radius * sin(pi / 10.0) / sin(pi / 10.0 * 3);

	HGDIOBJ oldObj = pDC->SelectObject(GetStockObject(DC_PEN));
	COLORREF oldColor = pDC->SetDCPenColor(color);
	pDC->BeginPath();
	double Angle = p.m_angle;
	pDC->MoveTo(p.m_center.m_x - sin(Angle) * p.m_radius, p.m_center.m_y - cos(Angle) * p.m_radius);
	for (int i = 1; i <= 5; ++i) // »­Îå½ÇÐÇµÄÂÖÀª
	{
		Angle += pi / 5.0;
		pDC->LineTo(p.m_center.m_x - sin(Angle) * smallRadius, p.m_center.m_y - cos(Angle) * smallRadius);
		Angle += pi / 5.0;
		pDC->LineTo(p.m_center.m_x - sin(Angle) * p.m_radius, p.m_center.m_y - cos(Angle) * p.m_radius);
	}
	pDC->EndPath();
	pDC->SetDCPenColor(oldColor);
	pDC->SelectObject(oldObj);

	CRgn rgn;  // Ìî³ä
	rgn.CreateFromPath(pDC);
	pDC->InvertRgn(&rgn);
	CBrush brush;
	brush.CreateSolidBrush(color);
	pDC->FillRgn(&rgn, &brush);
}