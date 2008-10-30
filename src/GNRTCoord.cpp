/**
 * GNRTCoord
 * @name        GNRTCoord.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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

void GNRTCoord::setXY(float x, float y)
{
	m_x = x;
	m_y = y;
}

float GNRTCoord::getX() const
{
	return m_x;
}

float GNRTCoord::getY() const
{
	return m_y;
}
