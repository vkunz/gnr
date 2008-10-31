/**
 * GNRAssemblySphere
 * @name        GNRAssemblySphere.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssemblySphere.h"
#include <GL/glu.h>

GNRAssemblySphere::GNRAssemblySphere(const string& name = "unnamed"):
		GNRAssembly(name), m_radius(1), m_quadric(gluNewQuadric())
{
}

GNRAssemblySphere::~GNRAssemblySphere()
{
	gluDeleteQuadric(m_quadric);
}

void GNRAssemblySphere::genDL()
{
	glNewList(m_DL_id, 1);
	{
		gluSphere(m_quadric, m_radius, 32, 32);
		draw_children();
	}
	glEndList();
}

