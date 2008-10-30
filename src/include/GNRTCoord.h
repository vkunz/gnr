/**
 * GNRTCoord
 * @name        GNRTCoord.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef __GNRTCOORD_H__
#define __GNRTCOORD_H__

class GNRTCoord
{
public:
	GNRTCoord(float x, float y);
	
	void setX(float x);
	void setY(float y);
	void setXY(float x, float y);
	
	float getX() const;
	float getY() const;
	
private:
	float m_x, m_y;
};

#endif
