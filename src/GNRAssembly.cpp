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

#include <iostream>
using std::cout;
using std::endl;

GNRAssembly::GNRAssembly(const string& name = "unnamed"):
		m_x(0.0), m_y(0.0), m_z(0.0), m_overground(0.0), m_phi(0.0), m_theta(0.0), m_rho(0.0),
		m_scale(1.0), m_Locked(false), m_Wall(false), m_Visible(true),
		m_name(name), m_parent(NULL), m_DL_valid(false), m_DL_id(glGenLists(1)), m_at_depth(0)
{
}

GNRAssembly::~GNRAssembly()
{
	for (list<GNRAssembly*>::iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		delete *it;
	}
	glDeleteLists(m_DL_id, 1);
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

void GNRAssembly::getPosition(GNRVertex& result) const
{
	result.setX(m_x);
	result.setY(m_y);
	result.setZ(m_z);
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

void GNRAssembly::setPosition(const GNRVertex& pos)
{
	m_x = pos.getX();
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

float GNRAssembly::getGroupX() const
{
	const GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	return ptr->m_x;
}

float GNRAssembly::getGroupY() const
{
	const GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	return ptr->m_y;
}

float GNRAssembly::getGroupZ() const
{
	const GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	return ptr->m_z;
}

void GNRAssembly::setGroupX(float x)
{
	GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	ptr->m_x = x;
}

void GNRAssembly::setGroupY(float y)
{
	GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	ptr->m_y = y;
}

void GNRAssembly::setGroupZ(float z)
{
	GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	ptr->m_z = z;
}

float GNRAssembly::getGroupPhi() const
{
	const GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	return ptr->m_phi;
}

float GNRAssembly::getGroupRho() const
{
	const GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	return ptr->m_rho;
}

float GNRAssembly::getGroupTheta() const
{
	const GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	return ptr->m_theta;
}

void GNRAssembly::setGroupPhi(const float phi)
{
	GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	ptr->m_phi = phi;
}

void GNRAssembly::setGroupRho(const float rho)
{
	GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	ptr->m_rho = rho;
}

void GNRAssembly::setGroupTheta(const float theta)
{
	GNRAssembly* ptr = this;
	if (m_at_depth > 1 && m_parent->m_Locked)
	{
		ptr = m_parent;
	}
	
	ptr->m_theta = theta;
}

void GNRAssembly::setOverGround(const float overground)
{
	m_overground = overground;
}

float GNRAssembly::getScale() const
{
	return m_scale;
}

float GNRAssembly::getScaleX() const
{
	return m_scaleX;
}

float GNRAssembly::getScaleY() const
{
	return m_scaleY;
}

float GNRAssembly::getScaleZ() const
{
	return m_scaleZ;
}

void GNRAssembly::setScale(float s)
{
	m_scale = s;
}

void GNRAssembly::setScaleX(float x)
{
	m_scaleX = x;
}

void GNRAssembly::setScaleY(float y)
{
	m_scaleY = y;
}

void GNRAssembly::setScaleZ(float z)
{
	m_scaleZ = z;
}

float GNRAssembly::getOverGround()
{
	return m_overground;
}

const string& GNRAssembly::getName() const
{
	return m_name;
}

// adds a part of an object (wheel->car)
void GNRAssembly::addPart(GNRAssembly* p)
{
	p->setParent(this);
	p->m_at_depth = m_at_depth + 1;
	m_part.push_back(p);
}

void GNRAssembly::setName(const string& name)
{
	m_name = name;
}

const GNRAssembly* GNRAssembly::getParent() const
{
	return m_parent;
}

void GNRAssembly::setParent(GNRAssembly* p)
{
	m_parent = p;
}

bool GNRAssembly::getLocked() const
{
	return m_Locked;
}

void GNRAssembly::setLocked(bool Locked)
{
	m_Locked = Locked;
}

void GNRAssembly::draw_children()
{
	for (list<GNRAssembly*>::iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		(*it)->draw();
	}
}

void GNRAssembly::draw()
{
	if ((m_at_depth == 1) || (m_at_depth == 2 && !(m_parent->m_Locked)))
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
		
		if (!m_DL_valid)
		{
			genDL();
		}
		glCallList(m_DL_id);
	}
	glPopMatrix();
}

void GNRAssembly::genDL()
{
	glNewList(m_DL_id, 1);
	{
		draw_children();
	}
	glEndList();
}
