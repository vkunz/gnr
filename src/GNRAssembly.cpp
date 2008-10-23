/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRAssembly
 * @name        GNRAssembly.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssembly.h"

#include <GL/gl.h>

GNRAssembly::GNRAssembly(const string& name = "unnamed"):
		m_x(0.0), m_y(0.0), m_z(0.0), m_phi(0.0), m_theta(0.0), m_rho(0.0),
		m_scale(1.0), m_locked(false), m_isWall(false), m_name(name), m_parent(NULL)
{
}

GNRAssembly::~GNRAssembly()
{
	for (list<GNRAssembly*>::iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		delete *it;
	}
}

float GNRAssembly::getX() const
{
	return m_x;
}

float GNRAssembly::getY() const
{
	return m_y;
}

float GNRAssembly::getZ() const
{
	return m_z;
}

void GNRAssembly::setX(float x)
{
	m_x = x;
}

void GNRAssembly::setY(float y)
{
	m_y = y;
}

void GNRAssembly::setZ(float z)
{
	m_z = z;
}

float GNRAssembly::getPhi() const
{
	return m_phi;
}

float GNRAssembly::getRho() const
{
	return m_rho;
}

float GNRAssembly::getTheta() const
{
	return m_theta;
}

void GNRAssembly::setPhi(const float phi)
{
	m_phi = phi;
}

void GNRAssembly::setRho(const float rho)
{
	m_rho = rho;
}

void GNRAssembly::setTheta(const float theta)
{
	m_theta = theta;
}

void GNRAssembly::setScale(float s)
{
	m_scale = s;
}

const string& GNRAssembly::getName() const
{
	return m_name;
}

void GNRAssembly::addFace(const GNRFace& face)
{
	m_face.push_back(face);
}

void GNRAssembly::addPart(GNRAssembly* p)
{
	m_part.push_back(p);
}

bool GNRAssembly::getIsRoot() const
{
	return m_isroot;
}

void GNRAssembly::setIsRoot(bool isroot)
{
	m_isroot = isroot;
}

const GNRAssembly* GNRAssembly::getParent() const
{
	return m_parent;
}

void GNRAssembly::setParent(GNRAssembly* p)
{
	m_parent = p;
}

void GNRAssembly::setNormals()
{
	// set normals on own faces
	for (list<GNRFace>::iterator it = m_face.begin(); it != m_face.end(); ++it)
	{
		it->setNormal();
	}
	
	// let children set their normals
	for (list<GNRAssembly*>::iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		(*it)->setNormals();
	}
}

void GNRAssembly::draw() const
{
	if (m_isroot)
	{
		glLoadName((int)this);
	}
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		//if importer scale factor 1.0, then scale before translate
		glScalef(m_scale, m_scale, m_scale);
		glTranslatef(m_x, m_y, m_z);
		
		//rotate in object center
		glRotatef(m_phi, 1, 0, 0);
		glRotatef(m_theta, 0, 1, 0);
		glRotatef(m_rho, 0, 0, 1);
		
		// draw myself
		for (list<GNRFace>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
		{
			it->draw();
		}
		
		// draw the children
		for (list<GNRAssembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
		{
			(*it)->draw();
		}
	}
	glPopMatrix();
}

