#include "pch.h"
#include "CP_Point2D.h"
#include <cmath>

CP_Point2D::CP_Point2D(): m_x(0), m_y(0)
{
}

CP_Point2D::CP_Point2D(double x, double y) : m_x(x), m_y(x)
{
}

CP_Point2D::~CP_Point2D()
{
}