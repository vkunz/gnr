/**
 * LibraryCategory
 * @name        LibraryCategory.h
 * @date        2008-11-12
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "LibraryCategory.h"

/**
 * default constructor of category data
 */
LibraryCategory::LibraryCategory()
{
}

/**
 * constructor of category data
 * @param[in]       name
 * @param[in]       cat_id
 * @param[in]       parent_id
 */
LibraryCategory::LibraryCategory(wxString name, unsigned int cat_id, unsigned int parent_id)
{
	// asign name
	m_name = name;

	// asign gropuId
	m_categoryId = cat_id;

	// asign parentId
	m_parentId = parent_id;
}

/**
 * destructor of category data
 */
LibraryCategory::~LibraryCategory()
{
}

/**
 * getName
 * @return      wxString        name of cat
 */
wxString LibraryCategory::getName()
{
	return m_name;
}

/**
 * setName
 * @param[in]      name        name of cat
 */
void LibraryCategory::setName(wxString name)
{
	m_name = name;
}

/**
 * getCategoryId
 * @return      unsigned int        id of cat
 */
unsigned int LibraryCategory::getCatId()
{
	return m_categoryId;
}

/**
 * setCategoryId
 * @param[in]      cat_id           id of cat
 */
void LibraryCategory::setCatId(unsigned int cat_id)
{
	m_categoryId = cat_id;
}

/**
 * getParentId
 * @return      unsigned int        id of parent cat
 */
unsigned int LibraryCategory::getParentId()
{
	return m_parentId;
}

/**
 * setParentId
 * @param[in]      parent_id        id of parent cat
 */
void LibraryCategory::setParentId(unsigned int parent_id)
{
	m_parentId = parent_id;
}

/**
 * toString
 * @return      wxString        string of complete data
 */
wxString LibraryCategory::toString()
{
	wxString tmp;

	tmp << wxT("Name: ") << m_name << wxT("\tCategoryId: ") << m_categoryId << wxT("\tParentId: ") << m_parentId;

	return tmp;
}
