/**
 * VNT
 * @name        VNT.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <GL/gl.h>


#include "VNT.h"

VNT::VNT(Vertex* v, Vertex* n, TCoord* t):
		m_v(v), m_n(n), m_t(t)
{
}

VNT::VNT(const VNT& other)
{
	m_v = 0;
	m_n = 0;
	m_t = 0;
	if (other.m_v)
	{
		m_v = new Vertex(*other.m_v);
	}
	if (other.m_n)
	{
		m_n = new Vertex(*other.m_n);
	}
	if (other.m_t)
	{
		m_t = new TCoord(*other.m_t);
	}
}

const Vertex* VNT::getV() const
{
	return m_v;
}

const Vertex* VNT::getN() const
{
	return m_n;
}

const TCoord* VNT::getT() const
{
	return m_t;
}

void VNT::setN(Vertex* n)
{
	if (m_n)
	{
		delete m_n;
	}
	
	m_n = n;
}

VNT::~VNT()
{
	if (m_v)
	{
		delete m_v;
	}
	if (m_n)
	{
		delete m_n;
	}
	if (m_t)
	{
		delete m_t;
	}
}

void VNT::draw() const
{
	if (m_t)
	{
		glTexCoord2f(m_t->getX(), m_t->getY());
	}
	
	if (m_n)
	{
		glNormal3f(m_n->getX(), m_n->getY(), m_n->getZ());
	}
	
	glVertex3f(m_v->getX(), m_v->getY(), m_v->getZ());
}
