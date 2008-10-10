/* vim: set expandtab sw=4 ts=4 sts=4: */
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

class GNRVertex
{
public:
	// ctor
	GNRVertex(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
	GNRVertex(const GNRVertex& v) : m_x(v.m_x), m_y(v.m_y), m_z(v.m_z) { }
	GNRVertex(const GNRVertex* p_v) {
		m_x = p_v->m_x;
		m_y = p_v->m_y;
		m_z = p_v->m_z;
	}

	// dtor
	virtual ~GNRVertex();
	
	// return value
	const float getX() const { return m_x; }
	const float getY() const { return m_y; }
	const float getZ() const { return m_z; }
	
	// setter
	void setX(const float x) { m_x = x; }
	void setY(const float y) { m_y = y; }
	void setZ(const float z) { m_z = z; }
	
	float deltaX(GNRVertex* point) { return m_x - point.x; }
	float deltaY(GNRVertex* point) { return m_y - point.y; }
	float deltaZ(GNRVertex* point) { return m_z - point.z; }
	
	GNRVertex  operator  + (const GNRVertex& p2) const;
	GNRVertex  operator  - (const GNRVertex& p2) const;
	GNRVertex& operator  = (const GNRVertex& p2);
	GNRVertex& operator += (const GNRVertex& p2);
	GNRVertex& operator -= (const GNRVertex& p2);
	
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
