#ifndef CP_PENTAGRAM2D_H
#define CP_PENTAGRAM2D_H

#include "CP_Point2D.h"

class CP_Pentagram2D
{
public:
	CP_Point2D m_center;
	double m_radius, m_angle;

public:
	CP_Pentagram2D();
	CP_Pentagram2D(double x, double y, double r, double a);
	~CP_Pentagram2D();
};

extern void gb_brushPentagram(CDC* pDC, CP_Pentagram2D& p, COLORREF color);

#endif // 