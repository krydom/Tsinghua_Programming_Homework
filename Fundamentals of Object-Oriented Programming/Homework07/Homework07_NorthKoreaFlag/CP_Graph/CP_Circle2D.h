#ifndef CP_CIRCLE2D_H
#define CP_CIRCLE2D_H

#include "CP_Point2D.h"

class CP_Circle2D
{
public:
	CP_Point2D m_center;
	double m_radius;

public:
	CP_Circle2D();
	CP_Circle2D(double x, double y, double r);
	~CP_Circle2D();
};

void gb_brushCircle(CDC* pDC, CP_Circle2D& r, COLORREF color);

#endif // ! CP_CIRCLE2D_H