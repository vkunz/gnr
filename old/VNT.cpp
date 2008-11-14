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

/**
 * constructor for vertex-normal-texture part
 * @param[in]       v       vertex pointer
 * @param[in]       n       normal pointer
 * @param[in]       t       texture pointer
 */
VNT::VNT(Vertex* v, Vertex* n, TCoord* t):
		m_v(v), m_n(n), m_t(t)
{
}

/**
 * copyconstructor for vertex-normal-texture part
 * @param[in]       other       copy other VNT
 */
VNT::VNT(const VNT& other)
{
	m_v = NULL;
	m_n = NULL;
	m_t = NULL;
	
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

/**
 * get vertex pointer
 * @return       Vertex*       vertex pointer
 */
const Vertex* VNT::getV() const
{
	return m_v;
}

/**
 * get normal pointer
 * @return       Vertex*       normal pointer
 */
const Vertex* VNT::getN() const
{
	return m_n;
}

/**
 * get texture pointer
 * @return       Vertex*       texture pointer
 */
const TCoord* VNT::getT() const
{
	return m_t;
}

/**
 * set normal pointer
 * @param[in]       n           Vertex* normal pointer
 */
void VNT::setN(Vertex* n)
{
	if (m_n != NULL)
	{
		delete m_n;
	}
	
	m_n = n;
}

/**
 * set vertex pointer
 * @param[in]       v           Vertex* vertex pointer
 */
void VNT::setV(Vertex* v)
{
	if (m_v != NULL)
	{
		delete m_v;
	}
	
	m_v = v;
}

/**
 * set texture pointer
 * @param[in]       t           TCoord* texture pointer
 */
void VNT::setT(TCoord* t)
{
	if (m_t != NULL)
	{
		delete m_t;
	}
	
	m_t = t;
}

/**
 * destructor of VNT
 */
VNT::~VNT()
{
	if (m_v != NULL)
	{
		delete m_v;
	}
	
	if (m_n != NULL)
	{
		delete m_n;
	}
	
	if (m_t != NULL)
	{
		delete m_t;
	}
}

/**
 * draw all contents to GL-methods
 */
void VNT::draw() const
{
	if (m_t != NULL)
	{
		glTexCoord2f(m_t->getX(), m_t->getY());
	}
	
	if (m_n != NULL)
	{
		glNormal3f(m_n->getX(), m_n->getY(), m_n->getZ());
	}
	
	glVertex3f(m_v->getX(), m_v->getY(), m_v->getZ());
}
