#include "LibraryCategory.h"

// ctor
LibraryCategory::LibraryCategory()
{
}

LibraryCategory::LibraryCategory(wxString name, unsigned int categoryId, unsigned int parentId)
{
	// asign name
	m_name = name;
	
	// asign gropuId
	m_categoryId = categoryId;
	
	// asign parentId
	m_parentId = parentId;
}

// dtor
LibraryCategory::~LibraryCategory()
{
	// do nothing
}

wxString LibraryCategory::getName()
{
	return m_name;
}

unsigned int LibraryCategory::getCategoryId()
{
	return m_categoryId;
}

unsigned int LibraryCategory::getParentId()
{
	return m_parentId;
}

void LibraryCategory::setName(wxString name)
{
	m_name = name;
}

wxString LibraryCategory::toString()
{
	wxString tmp;
	
	tmp << wxT("Name: ") << m_name << wxT("\tCategoryId: ") << m_categoryId << wxT("\tParentId: ") << m_parentId;
	
	return tmp;
}
