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

/**
 * constructor for TCoord
 * @param[in]       x           float x
 * @param[in]       y           float y
 */
TCoord::TCoord(float x, float y):
		m_x(x), m_y(y)
{
}

/**
 * set x
 * @param[in]       x           float x
 */
void TCoord::setX(float x)
{
	m_x = x;
}

/**
 * set y
 * @param[in]       y           float y
 */
void TCoord::setY(float y)
{
	m_x = y;
}

/**
 * set x and y
 * @param[in]       x           float x
 * @param[in]       y           float y
 */
void TCoord::setXY(float x, float y)
{
	m_x = x;
	m_y = y;
}

/**
 * get x
 * @return       float          x value
 */
float TCoord::getX() const
{
	return m_x;
}

/**
 * get y
 * @return       float          y value
 */
float TCoord::getY() const
{
	return m_y;
}
