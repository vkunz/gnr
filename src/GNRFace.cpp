/**
 * GNRFace
 * @name        GNRFace.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRFace.h"
#include "GNRMaterial.h"
#include "GNRMaterialLibrary.h"

#include <GL/gl.h>

#include <iostream>

using std::cout;
using std::endl;

extern GNRMaterialLibrary mtllib;

GNRFace::GNRFace(const string& matname):
		m_matname(matname)
{
}

GNRFace::GNRFace(const GNRFace& other):
		m_matname(other.m_matname)
{
	for (list<GNRVNT>::const_iterator it = other.m_vnt.begin(); it != other.m_vnt.end(); ++it)
	{
		m_vnt.push_back(*it);
	}
}

int GNRFace::size() const
{
	return m_vnt.size();
}

void GNRFace::addVNT(GNRVNT& vnt)
{
	m_vnt.push_back(vnt);
}

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

void GNRFace::draw() const
{
	mtllib.selectMaterial(m_matname);
	
	glBegin(GL_POLYGON);
	{
		for (list<GNRVNT>::const_iterator it = m_vnt.begin(); it != m_vnt.end(); ++it)
		{
			it->draw();
		}
	}
	glEnd();
}

