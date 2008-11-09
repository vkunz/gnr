/**
 * Vertex
 * @name        Vertex.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRVERTEX_H_
#define _GNRVERTEX_H_

#include <wx/string.h>

#include "Vertex.h"

class Vertex
{
public:
	// ctor
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(const Vertex& v);
	
	// dtor
	virtual ~Vertex();
	
	// return value
	const float getX() const;
	const float getY() const;
	const float getZ() const;
	
	// setter
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);
	void setXYZ(const float x, const float y, const float z);
	
	float deltaX(Vertex* point);
	float deltaY(Vertex* point);
	float deltaZ(Vertex* point);
	
	Vertex  operator  + (const Vertex& p2) const;
	Vertex  operator  - (const Vertex& p2) const;
	Vertex  operator  * (const float r) const;
	Vertex  operator  * (const Vertex& p2) const;
	Vertex  operator  ^(const Vertex& p2) const;
	
	Vertex& operator  = (const Vertex& p2);
	Vertex& operator += (const Vertex& p2);
	Vertex& operator -= (const Vertex& p2);
	
	float length();
	bool normalize();
	void rotate(float phi, float theta, float rho);
	void rotate(const Vertex& angles);
	
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
