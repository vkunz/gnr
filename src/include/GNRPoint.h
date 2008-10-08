#ifndef _GNRPOINT_H_
#define _GNRPOINT_H_

#include <wx/string.h>

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
	
	// setter
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	
	// dtor
	virtual ~GNRPoint();
	
	// return attributes
	wxString ToString();
	
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
