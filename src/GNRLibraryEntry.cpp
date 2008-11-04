#include "GNRLibraryEntry.h"

// ctor
GNRLibraryEntry::GNRLibraryEntry()
{
}

GNRLibraryEntry::GNRLibraryEntry(wxString name, wxString reference, unsigned int categoryId)
{
	// asign name
	m_name = name;
	
	// asign reference
	m_reference = reference;
	
	// asign groupId
	m_categoryId = categoryId;
}

// dtor
GNRLibraryEntry::~GNRLibraryEntry()
{
	// do nothing
}

wxString GNRLibraryEntry::toString()
{
	wxString tmp;
	
	tmp << wxT("Name: ") << m_name << wxT("\tReference: ") << m_reference << wxT("\tCategoryId: ") << m_categoryId;
	
	return tmp;
}

wxString GNRLibraryEntry::getName()
{
	return m_name;
}

unsigned int GNRLibraryEntry::getCategoryId()
{
	return m_categoryId;
}
