/**
 * LibraryEntry
 * @name        LibraryEntry.h
 * @date        2008-11-12
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "LibraryEntry.h"

/**
 * default constructor of category data
 */
LibraryEntry::LibraryEntry()
{
}

/**
 * constructor of category data
 * @param[in]       name            name of entry
 * @param[in]       reference       reference of entry
 * @param[in]       cat_id          parent id of entry
 */
LibraryEntry::LibraryEntry(wxString name, wxString reference, unsigned int cat_id)
{
	// asign name
	m_name = name;

	// asign reference
	m_reference = reference;

	// asign groupId
	m_categoryId = cat_id;
}

/**
 * destructor of category data
 */
LibraryEntry::~LibraryEntry()
{
}

/**
 * toString
 * @return      wxString        string of complete data
 */
wxString LibraryEntry::toString()
{
	wxString tmp;

	tmp << wxT("Name: ") << m_name << wxT("\tReference: ") << m_reference << wxT("\tCategoryId: ") << m_categoryId;

	return tmp;
}

/**
 * getName
 * @return      wxString        name of entry
 */
wxString LibraryEntry::getName()
{
	return m_name;
}

/**
 * setName
 * @param[in]      name        name of entry
 */
void LibraryEntry::setName(wxString name)
{
	m_name = name;
}

/**
 * getCategoryId
 * @return      unsigned int        id of entry
 */
unsigned int LibraryEntry::getCategoryId()
{
	return m_categoryId;
}

/**
 * setCategoryId
 * @param[in]      cat_id           id of entry
 */
void LibraryEntry::setCategoryId(unsigned int cat_id)
{
	m_categoryId = cat_id;
}

/**
 * getReference
 * @return      wxString        reference hash of entry
 */
wxString LibraryEntry::getReference()
{
	return m_reference;
}

/**
 * getReference
 * @param[in]      reference        wxString reference hash of entry
 */
void LibraryEntry::setReference(wxString reference)
{
	m_reference = reference;
}
