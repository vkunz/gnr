#include "GNRTreeLibraryItemData.h"

GNRTreeLibraryItemData::GNRTreeLibraryItemData()
{
	//ctor
}

GNRTreeLibraryItemData::~GNRTreeLibraryItemData()
{
	//dtor
}

void GNRTreeLibraryItemData::setCat(bool cat)
{
	m_category = cat;
}

bool GNRTreeLibraryItemData::getCat()
{
	return m_category;
}

void GNRTreeLibraryItemData::setName(wxString name)
{
	m_name = name;
}

wxString GNRTreeLibraryItemData::getName()
{
	return m_name;
}
