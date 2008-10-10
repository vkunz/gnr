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
	GNRVertex(double x, double y, double z) : m_x(x), m_y(y), m_z(z)
			GNRVertex(const GNRVertex& v) : m_x(v.m_x), m_y(v.m_y), m_z(v.m_z) { }
	GNRVertex(const GNRVertex* p_v) : this(*p_v);
	
	// dtor
	virtual ~GNRVertex();
	
	// return value
	double getX();
	double getY();
	double getZ();
	
	// setter
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	
	double deltaX(GNRVertex* point);
	double deltaY(GNRVertex* point);
	double deltaZ(GNRVertex* point);
	
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
	double m_x;
	
	// stores the y-value relative to zero
	double m_y;
	
	// stores the z-value relative to zer
	double m_z;
};

#endif // _GNRVERTEX_H_
