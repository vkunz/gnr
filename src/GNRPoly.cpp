#include <wx/list.h>

#include "GNRPoly.h"

// ctor
GNRPoly::GNRPoly()
{

}

// dtor
GNRPoly::~GNRPoly()
{
	// do nothing
}

void GNRPoly::addVertex(int iPoint)
{
	this->m_ListOfInteger.push_back(iPoint);
}

wxString GNRPoly::ToString()
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
