#ifndef _GNRVERTEX_H_
#define _GNRVERTEX_H_

#include <wx/string.h>

class GNRVertex
{
public:
	// ctor
	GNRVertex();
	GNRVertex(float x, float y, float z);
	
	// return value
	float getX();
	float getY();
	float getZ();
	
	// setter
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	
	float deltaX(GNRVertex* point);
	float deltaY(GNRVertex* point);
	float deltaZ(GNRVertex* point);
	
	GNRVertex  operator  + (const GNRVertex& p2) const;
	GNRVertex  operator  - (const GNRVertex& p2) const;
	GNRVertex& operator  = (const GNRVertex& p2);
	GNRVertex& operator += (const GNRVertex& p2);
	GNRVertex& operator -= (const GNRVertex& p2);
	
	// dtor
	virtual ~GNRVertex();
	
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

#endif // _GNRVERTEX_H_
