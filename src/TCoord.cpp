/**
 * TCoord
 * @name        TCoord.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "TCoord.h"

#include <string.h>

TCoord::TCoord(float x, float y):
		m_x(x), m_y(y)
{
}

void TCoord::setX(float x)
{
	m_x = x;
}

void TCoord::setY(float y)
{
	m_x = y;
}

void TCoord::setXY(float x, float y)
{
	m_x = x;
	m_y = y;
}

float TCoord::getX() const
{
	return m_x;
}

float TCoord::getY() const
{
	return m_y;
}
