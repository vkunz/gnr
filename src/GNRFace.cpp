/* vim: set expandtab sw=4 ts=4 sts=4: */
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

void GNRFace::addVNT(GNRVNT& vnt)
{
	m_vnt.push_back(vnt);
}

void GNRFace::setNormal()
{
	list<GNRVNT>::iterator it = m_vnt.begin();
	GNRVNT vp1 = *it;
	++it;
	
	if (vp1.getN() == NULL)
	{
		GNRVNT vp2 = *it; ++it;
        GNRVertex p1 = *vp1.getV(), p2 = *vp2.getV();

        GNRVertex face_normal = (p1 * p2);
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

