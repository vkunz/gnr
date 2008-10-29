/**
 * GNRAssemblyCuboid
 * @name        GNRAssemblyCuboid.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssemblyCuboid.h"
#include <GL/glu.h>

GNRAssemblyCuboid::GNRAssemblyCuboid(const string& name = "unnamed"):
		GNRAssembly(name), m_width(1), m_height(1), m_depth(1)
{
}

GNRAssemblyCuboid::~GNRAssemblyCuboid()
{
}

float GNRAssemblyCuboid::getWidth() const
{
	return m_width;
}

float GNRAssemblyCuboid::getHeight() const
{
	return m_height;
}

float GNRAssemblyCuboid::getDepth() const
{
	return m_depth;
}

void GNRAssemblyCuboid::setWidth(float width)
{
	m_width = width;
}

void GNRAssemblyCuboid::setHeight(float height)
{
	m_height = height;
}

void GNRAssemblyCuboid::setDepth(float depth)
{
	m_depth = depth;
}

void GNRAssemblyCuboid::genDL()
{
	float x = m_width / 2.0,  y = m_height / 2.0, z = m_depth / 2.0;
	
	glNewList(m_DL_id, 1);
	{
		glBegin(GL_QUADS);
		{
			// forward face
			glNormal3f(0, 0, 1);
			glVertex3f(-x, -y,  z);
			glVertex3f(x, -y,  z);
			glVertex3f(x,  y,  z);
			glVertex3f(-x,  y,  z);
			
			// right face
			glNormal3f(1, 0, 0);
			glVertex3f(x, -y,  z);
			glVertex3f(x, -y, -z);
			glVertex3f(x,  y, -z);
			glVertex3f(x,  y,  z);
			
			// back face
			glNormal3f(0, 0, -1);
			glVertex3f(x, -y, -z);
			glVertex3f(-x, -y, -z);
			glVertex3f(-x,  y, -z);
			glVertex3f(x,  y, -z);
			
			// left face
			glNormal3f(-1, 0, 0);
			glVertex3f(-x, -y, -z);
			glVertex3f(-x, -y,  z);
			glVertex3f(-x,  y,  z);
			glVertex3f(-x,  y, -z);
			
			// upper face
			glNormal3f(0, 1, 0);
			glVertex3f(-x,  y,  z);
			glVertex3f(x,  y,  z);
			glVertex3f(x,  y, -z);
			glVertex3f(-x,  y, -z);
			
			// bottom face
			glNormal3f(0, -1, 0);
			glVertex3f(-x, -y,  z);
			glVertex3f(x, -y,  z);
			glVertex3f(x, -y, -z);
			glVertex3f(-x, -y, -z);
		}
		glEnd();
		
		draw_children();
	}
	glEndList();
}
