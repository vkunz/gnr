#include "TreeLibraryItemData.h"

TreeLibraryItemData::TreeLibraryItemData()
{
	//ctor
}

TreeLibraryItemData::~TreeLibraryItemData()
{
	//dtor
}

void TreeLibraryItemData::setCat(bool cat)
{
	m_category = cat;
}

bool TreeLibraryItemData::getCat()
{
	return m_category;
}

void TreeLibraryItemData::setName(wxString name)
{
	m_name = name;
}

wxString TreeLibraryItemData::getName()
{
	return m_name;
}
