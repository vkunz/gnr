#ifndef _GNRPOINT_H_
#define _GNRPOINT_H_

class GNRPoint
{
public:
	// ctor
	GNRPoint();
	GNRPoint(float x, float y, float z);
	
	// return value
	float getX();
	float getY();
	float getZ();
	
	// dtor
	virtual ~GNRPoint();
	
protected:

private:
	// stores the x-value relative to zero
	float m_x;
	
	// stores the y-value relative to zero
	float m_y;
	
	// stores the z-value relative to zer
	float m_z;
};

#endif // _GNRPOINT_H_
