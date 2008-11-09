#include "TreeLibraryItemData.h"

/**
 * constructor of TreeLibraryItemData
 */
TreeLibraryItemData::TreeLibraryItemData()
{
}

/**
 * destructor of TreeLibraryItemData
 */
TreeLibraryItemData::~TreeLibraryItemData()
{
}

/**
 * set is category or not
 * @param[in]       cat     boolean, if cat or not
 */
void TreeLibraryItemData::setCat(bool cat)
{
	m_category = cat;
}

/**
 * get category or not
 * @return       bool     if cat or not
 */
bool TreeLibraryItemData::getCat()
{
	return m_category;
}

/**
 * set name of cat
 * @param[in]       name     wxString name of item
 */
void TreeLibraryItemData::setName(wxString name)
{
	m_name = name;
}

/**
 * get name of cat
 * @return       wxString      get name of item
 */
wxString TreeLibraryItemData::getName()
{
	return m_name;
}
