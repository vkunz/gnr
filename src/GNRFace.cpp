/**
 * GNRFace
 * @note        [TODO]
 * @name        GNRFace.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRFace.h"

#include <GL/gl.h>
#include <iostream>

using std::cout;
using std::endl;

/**
 * constructor
 * @access      public
 */
GNRFace::GNRFace()
{
}

/**
 * copy constructor
 * @access      public
 */
GNRFace::GNRFace(const GNRFace& other)
{
	for (list<GNRVNT>::const_iterator it = other.m_vnt.begin(); it != other.m_vnt.end(); ++it)
	{
		m_vnt.push_back(*it);
	}
}

/**
 * TODO:DESCRIPTION
 * @param
 * @return
 * @access
 */
int GNRFace::size() const
{
	return m_vnt.size();
}

/**
 * TODO:DESCRIPTION
 * @param
 * @return
 * @access
 */
void GNRFace::addVNT(GNRVNT& vnt)
{
	m_vnt.push_back(vnt);
}

/**
 * TODO:DESCRIPTION
 * @param
 * @return
 * @access
 */
void GNRFace::setNormal()
{
	list<GNRVNT>::iterator it = m_vnt.begin();
	GNRVNT vp1(*it);
	++it;
	
	if (vp1.getN() == NULL)
	{
		GNRVNT vp2(*it);
		++it;
		
		GNRVNT vp3(*it);
		
		GNRVertex p1 = *vp1.getV(), p2 = *vp2.getV(), p3 = *vp3.getV();
		
		GNRVertex face_normal = ((p2-p1) * (p3-p1));
		face_normal.normalize();
		
		for (it = m_vnt.begin(); it != m_vnt.end(); ++it)
		{
			GNRVertex* tmp = new GNRVertex(face_normal);
			it->setN(tmp);
		}
	}
}

/**
 * TODO:DESCRIPTION
 * @param
 * @return
 * @access
 */
void GNRFace::draw() const
{
	glBegin(GL_POLYGON);
	{
		for (list<GNRVNT>::const_iterator it = m_vnt.begin(); it != m_vnt.end(); ++it)
		{
			it->draw();
		}
	}
	glEnd();
}
