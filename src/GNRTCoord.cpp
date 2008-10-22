#include "GNRTCoord.h"

#include <string.h>

GNRTCoord::GNRTCoord(float x, float y):
	m_x(x), m_y(y)
{
}

void GNRTCoord::setX(float x)
{
	m_x = x;
}

void GNRTCoord::setY(float y)
{
	m_x = y;
}

float GNRTCoord::getX() const
{
	return m_x;
}

float GNRTCoord::getY() const
{
	return m_y;
}
