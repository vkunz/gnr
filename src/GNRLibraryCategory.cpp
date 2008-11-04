#include "GNRLibraryCategory.h"

// ctor
GNRLibraryCategory::GNRLibraryCategory()
{
}

GNRLibraryCategory::GNRLibraryCategory(wxString name, unsigned int categoryId, unsigned int parentId)
{
	// asign name
	m_name = name;
	
	// asign gropuId
	m_categoryId = categoryId;
	
	// asign parentId
	m_parentId = parentId;
}

// dtor
GNRLibraryCategory::~GNRLibraryCategory()
{
	// do nothing
}

wxString GNRLibraryCategory::getName()
{
	return m_name;
}

unsigned int GNRLibraryCategory::getCategoryId()
{
	return m_categoryId;
}

unsigned int GNRLibraryCategory::getParentId()
{
	return m_parentId;
}

wxString GNRLibraryCategory::toString()
{
	wxString tmp;
	
	tmp << wxT("Name: ") << m_name << wxT("\tCategoryId: ") << m_categoryId << wxT("\tParentId: ") << m_parentId;
	
	return tmp;
}
