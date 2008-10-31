/**
 * GNRVertex
 * @name        GNRVertex.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRVERTEX_H_
#define _GNRVERTEX_H_

#include <wx/string.h>

#include "GNRVertex.h"

class GNRVertex
{
public:
	// ctor
	GNRVertex();
	GNRVertex(float x, float y, float z);
	GNRVertex(const GNRVertex& v);
	
	// dtor
	virtual ~GNRVertex();
	
	// return value
	const float getX() const;
	const float getY() const;
	const float getZ() const;
	
	// setter
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);
	void setXYZ(const float x, const float y, const float z);
	
	float deltaX(GNRVertex* point);
	float deltaY(GNRVertex* point);
	float deltaZ(GNRVertex* point);
	
	GNRVertex  operator  + (const GNRVertex& p2) const;
	GNRVertex  operator  - (const GNRVertex& p2) const;
	GNRVertex  operator  * (const float r) const;
	GNRVertex  operator  * (const GNRVertex& p2) const;
	GNRVertex  operator  ^(const GNRVertex& p2) const;
	
	GNRVertex& operator  = (const GNRVertex& p2);
	GNRVertex& operator += (const GNRVertex& p2);
	GNRVertex& operator -= (const GNRVertex& p2);
	
	float length();
	bool normalize();
	void rotate(float phi, float theta, float rho);
	void rotate(GNRVertex* angles);
	
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
