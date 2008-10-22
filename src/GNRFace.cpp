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

#include <GL/gl.h>

#include <iostream>

using std::cout; using std::endl;

extern GNRMatLib* mtllib;

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

void GNRFace::draw() const
{
    GNRMatLib::const_iterator it = mtllib->find(m_matname);
    if (it != mtllib->end())
    {
//        cout << m_matname << endl;
        it->second.draw();
    }

	glBegin(GL_POLYGON);
    {
    	for (list<GNRVNT>::const_iterator it = m_vnt.begin(); it != m_vnt.end(); ++it)
        {
            it->draw();
        }
	}
	glEnd();
}

