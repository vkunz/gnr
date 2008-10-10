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

// ctor
GNRFace::GNRFace()
{

}

// dtor
GNRFace::~GNRFace()
{
	// do nothing
}

void GNRFace::addVertex(int iPoint)
{
	this->m_ListOfInteger.push_back(iPoint);
}

void GNRPoint3d::addGNRPoint3d(const GNRPoint3d* point)
{

}

wxString GNRFace::ToString()
{
	wxString tmp;
	std::list<int>::iterator it;
	
	for (it = this->m_ListOfInteger.begin(); it != m_ListOfInteger.end(); it++)
	{
		tmp << *it;
		tmp << wxT("\t");
	}
	
	return tmp;
}
