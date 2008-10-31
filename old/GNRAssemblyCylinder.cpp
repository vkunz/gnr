/**
 * GNRAssemblyCylinder
 * @name        GNRAssemblyCylinder.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssemblyCylinder.h"
#include <GL/glu.h>

GNRAssemblyCylinder::GNRAssemblyCylinder(const string& name = "unnamed"):
		GNRAssembly(name), m_qtop(gluNewQuadric()),
		m_qbottom(gluNewQuadric()), m_qside(gluNewQuadric()),
		m_top(0.5), m_bottom(1.0), m_height(1.0)
{
	gluQuadricOrientation(m_qtop, GLU_OUTSIDE);
	gluQuadricOrientation(m_qbottom, GLU_INSIDE);
}

GNRAssemblyCylinder::~GNRAssemblyCylinder()
{
	gluDeleteQuadric(m_qtop);
	gluDeleteQuadric(m_qbottom);
	gluDeleteQuadric(m_qside);
}

float GNRAssemblyCylinder::getHeight() const
{
	return m_height;
}

float GNRAssemblyCylinder::getTop() const
{
	return m_top;
}

float GNRAssemblyCylinder::getBottom() const
{
	return m_bottom;
}

void GNRAssemblyCylinder::setHeight(float height)
{
	m_height = height;
}

void GNRAssemblyCylinder::setTop(float top)
{
	m_top = top;
}

void GNRAssemblyCylinder::setBottom(float bottom)
{
	m_bottom = bottom;
}

void GNRAssemblyCylinder::genDL()
{
	glNewList(m_DL_id, 1);
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glRotatef(-90, 1, 0, 0);
			glTranslatef(0, 0, -m_height/2.0);
			
			gluCylinder(m_qside, m_bottom, m_top, m_height, 32, 32);
			
			gluDisk(m_qbottom, 0.0, m_bottom, 32, 32);
			
			glTranslatef(0, 0, m_height);
			gluDisk(m_qtop, 0.0, m_top, 32, 32);
		}
		glPopMatrix();
		draw_children();
	}
	glEndList();
}
