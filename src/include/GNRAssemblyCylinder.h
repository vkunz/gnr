#ifndef __GNRASSEMBLY_CYLINDER_H__
#define __GNRASSEMBLY_CYLINDER_H__

/**
 * GNRAssemblyCylinder
 * @name                GNRAssemblyCylinder.h
 * @date                2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssembly.h"

class GNRAssemblyCylinder : public GNRAssembly
{
public:
	GNRAssemblyCylinder(const string& name);
	virtual ~GNRAssemblyCylinder();
	
	float getHeight() const;
	float getTop() const;
	float getBottom() const;
	
	void setHeight(float height);
	void setTop(float top);
	void setBottom(float bottom);
	
	void genDL();
	
private:
	float m_height, m_top, m_bottom;
	GLUquadric* m_qtop, *m_qbottom, *m_qside;
};

#endif

