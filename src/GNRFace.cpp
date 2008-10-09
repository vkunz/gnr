#include <wx/list.h>

#include "GNRFace.h"

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
