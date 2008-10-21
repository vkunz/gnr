#ifndef __GNRTCOORD_H__
#define __GNRTCOORD_H__

class GNRTCoord
{
public:
	GNRTCoord(float x, float y);
	
	void setX(float x);
	void setY(float y);
	
	float getX() const;
	float getY() const;
	
private:
	float m_x, m_y;
};

#endif
