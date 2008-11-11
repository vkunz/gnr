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
 * set is category id
 * @param[in]       cat_id      id of cat
 */
void TreeLibraryItemData::setCatId(unsigned int cat_id)
{
	m_category_id = cat_id;
}

/**
 * get category id
 * @return       unsigned int     if cat or not
 */
unsigned int TreeLibraryItemData::getCatId()
{
	return m_category_id;
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

/**
 * set hash of entry
 * @param[in]       hash     wxString name of item
 */
void TreeLibraryItemData::setHash(wxString hash)
{
	m_hash = hash;
}

/**
 * get hash of entry
 * @return       wxString      get name of item
 */
wxString TreeLibraryItemData::getHash()
{
	return m_hash;
}
