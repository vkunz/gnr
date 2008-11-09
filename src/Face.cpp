/**
 * Face
 * @note        [TODO]
 * @name        Face.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "Face.h"

#include <GL/gl.h>
#include <iostream>

using std::cout;
using std::endl;

/**
 * constructor
 */
Face::Face()
{
}

/**
 * copy constructor
 * @param[in]       face        face that has to be copied
 */
Face::Face(const Face& other)
{
	for (list<VNT>::const_iterator it = other.m_vnt.begin(); it != other.m_vnt.end(); ++it)
	{
		m_vnt.push_back(*it);
	}
}

/**
 * TODO:DESCRIPTION
 */
int Face::size() const
{
	return m_vnt.size();
}

/**
 * TODO:DESCRIPTION
 */
void Face::addVNT(VNT& vnt)
{
	m_vnt.push_back(vnt);
}

/**
 * TODO:DESCRIPTION
 */
void Face::setNormal()
{
	list<VNT>::iterator it = m_vnt.begin();
	VNT vp1(*it);
	++it;
	
	if (vp1.getN() == NULL)
	{
		VNT vp2(*it);
		++it;
		
		VNT vp3(*it);
		
		Vertex p1 = *vp1.getV(), p2 = *vp2.getV(), p3 = *vp3.getV();
		
		Vertex face_normal = ((p2-p1) * (p3-p1));
		face_normal.normalize();
		
		for (it = m_vnt.begin(); it != m_vnt.end(); ++it)
		{
			Vertex* tmp = new Vertex(face_normal);
			it->setN(tmp);
		}
	}
}

/**
 * TODO:DESCRIPTION
 */
void Face::draw() const
{
	glBegin(GL_POLYGON);
	{
		for (list<VNT>::const_iterator it = m_vnt.begin(); it != m_vnt.end(); ++it)
		{
			it->draw();
		}
	}
	glEnd();
}
