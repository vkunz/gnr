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

#include <wx/list.h>

#include "GNRFace.h"
#include "GNRPoint3d.h"
#include "GNRVertex.h"
#include <GL/gl.h>

// ctor
GNRFace::GNRFace()
{

}

// dtor
GNRFace::~GNRFace()
{
	// do nothing
}

void GNRFace::addGNRPoint3d(const GNRPoint3d* point)
{

}

wxString GNRFace::ToString()
{
	return wxT("");
}

void GNRFace::draw() const
{
	glBegin(GL_POLYGON);
	for (std::list<GNRPoint3d>::const_iterator it = m_points.begin(); it != m_points.end(); ++it)
	{
		const GNRVertex *v = NULL;
		v = it->getNorm();
		glNormal3f(v->getX(), v->getY(), v->getZ());
		
		v = it->getCoord();
		glVertex3f(v->getX(), v->getY(), v->getZ());
	}
	glEnd();
}
