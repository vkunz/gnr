#include "LibraryEntry.h"

// ctor
LibraryEntry::LibraryEntry()
{
}

LibraryEntry::LibraryEntry(wxString name, wxString reference, unsigned int categoryId)
{
	// asign name
	m_name = name;
	
	// asign reference
	m_reference = reference;
	
	// asign groupId
	m_categoryId = categoryId;
}

// dtor
LibraryEntry::~LibraryEntry()
{
	// do nothing
}

wxString LibraryEntry::toString()
{
	wxString tmp;
	
	tmp << wxT("Name: ") << m_name << wxT("\tReference: ") << m_reference << wxT("\tCategoryId: ") << m_categoryId;
	
	return tmp;
}

wxString LibraryEntry::getName()
{
	return m_name;
}

unsigned int LibraryEntry::getCategoryId()
{
	return m_categoryId;
}

wxString LibraryEntry::getReference()
{
	return m_reference;
}

void LibraryEntry::setName(wxString name)
{
	m_name = name;
}
