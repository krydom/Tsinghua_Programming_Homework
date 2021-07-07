#ifndef CP_RECTANGLE2D_H
#define CP_RECTANGLE2D_H

#include "CP_Point2D.h"

class CP_Rectangle2D
{
public:
	CP_Point2D m_leftUpperPoint;
	double m_width, m_height;

public:
	CP_Rectangle2D();
	CP_Rectangle2D::CP_Rectangle2D(double x, double y, double w, double h);
	~CP_Rectangle2D();

	void gb_moveRectangle(int x, int y);
};

extern void gb_brushRectangle(CDC* pDC, CP_Rectangle2D& r, COLORREF color);
extern void gb_drawRectangle(CDC* pDC, CP_Rectangle2D& r, COLORREF color);

#endif
