#ifndef __GNRASSEMBLY_SPHERE_H__
#define __GNRASSEMBLY_SPHERE_H__

/**
 * GNRAssemblySphere
 * @name                GNRAssemblySphere.h
 * @date                2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssembly.h"

class GNRAssemblySphere : public GNRAssembly
{
public:
	GNRAssemblySphere(const string& name);
	virtual ~GNRAssemblySphere();
	
	float getRadius() const;
	
	void setRadius(float radius);
	
	void genDL();
	
private:
	float m_radius;
	GLUquadric* m_quadric;
};

#endif

