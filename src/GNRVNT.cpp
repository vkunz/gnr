#include "GNRVNT.h"

#include <GL/gl.h>

GNRVNT::GNRVNT(GNRVertex* v, GNRVertex* n, GNRTCoord* t):
		m_v(v), m_n(n), m_t(t)
{
}

GNRVNT::GNRVNT(const GNRVNT& other)
{
	m_v = 0;
	m_n = 0;
	m_t = 0;
	if (other.m_v)
	{
		m_v = new GNRVertex(*other.m_v);
	}
	if (other.m_n)
	{
		m_n = new GNRVertex(*other.m_n);
	}
	if (other.m_t)
	{
		m_t = new GNRTCoord(*other.m_t);
	}
}

const GNRVertex* GNRVNT::getV() const
{
	return m_v;
}

const GNRVertex* GNRVNT::getN() const
{
	return m_n;
}

const GNRTCoord* GNRVNT::getT() const
{
	return m_t;
}

void GNRVNT::setN(GNRVertex* n)
{
	if (m_n)
	{
		delete m_n;
	}
	
	m_n = n;
}

GNRVNT::~GNRVNT()
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

void GNRVNT::draw() const
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
