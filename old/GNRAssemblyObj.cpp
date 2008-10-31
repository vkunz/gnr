/**
 * GNRAssemblyObj
 * @name        GNRAssemblyObj.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssemblyObj.h"

GNRAssemblyObj::GNRAssemblyObj(const string& name = "unnamed"):
		GNRAssembly(name)
{
}

GNRAssemblyObj::~GNRAssemblyObj()
{
}

void GNRAssemblyObj::addFace(const GNRFace& face)
{
	m_face.push_back(face);
}

void GNRAssemblyObj::setNormals()
{
	for (list<GNRFace>::iterator it = m_face.begin(); it != m_face.end(); ++it)
	{
		it->setNormal();
	}
}

void GNRAssemblyObj::genDL()
{
	glNewList(m_DL_id, GL_COMPILE);
	{
		for (list<GNRFace>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
		{
			it->draw();
		}
		
		draw_children();
	}
	glEndList();
	
//	m_DL_valid = true;
}

