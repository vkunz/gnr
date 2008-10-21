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

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

// ctor
GNRFace::GNRFace()
{

}

// dtor
GNRFace::~GNRFace()
{
	// do nothing
}

void GNRFace::addGNRPoint3d(const GNRPoint3d* p_point)
{
	m_points.push_back(*p_point);
}

wxString GNRFace::ToString()
{
	wxString msg;
	
	std::list<GNRPoint3d>::iterator it;
	
	for (it = m_points.begin(); it != m_points.end(); it++)
	{
		msg << it->ToString();
	}
	
	return msg;
}

void GNRFace::draw() const
{
	GLfloat mat1_ambient[]		=	{0.11f,0.06f,0.11f,1.00f};
	GLfloat mat1_diffuse[]		=	{0.43f,0.47f,0.54f,1.00f};
	GLfloat mat1_specular[]		=	{0.33f,0.33f,0.52f,1.00f};
	GLfloat mat1_emission[]		=	{0.00f,0.00f,0.00f,0.00f};
	GLfloat mat1_shininess	    =	10;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat1_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat1_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat1_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat1_shininess);
	
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
