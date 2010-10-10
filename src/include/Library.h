/**
 * Library
 * @name        Library.h
 * @date        2008-11-12
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <vector>
#include <wx/filename.h>
#include <wx/mstream.h>
#include <wx/string.h>
#include <wx/zipstrm.h>
#include <wx/xml/xml.h>

class LibraryCategory;
class LibraryEntry;

class Library
{
public:
	// ctor
	Library();

	// dtor
	virtual ~Library();

	// attributes
	// static variable to store id
	static unsigned int m_categoryId;

	// functions
	// retunrs m_ptrCategories
	std::vector<LibraryCategory>* getCategories();

	// returns m_ptrEntries
	std::vector<LibraryEntry>* getEntries();

	// add new category to library
	void addCategory(wxString& name, unsigned int parentId = 0);

	// add new oax to library
	void addEntry(wxString reference, wxInputStream& inStream);

	// delete entry
	void deleteEntry(wxString reference);

	// get entry
	wxMemoryOutputStream* getEntryData(wxString reference);

	// rename category
	void renameCategory(unsigned int cat_id, wxString new_name);

	// rename entry
	void renameEntry(wxString reference, wxString newName);

	// add new category
	void addNewCategory(const wxString& name, const unsigned int parentId);

	// move entry from one category to an other
	void moveEntry(const wxString reference, const unsigned int new_parent_id);

	// move category to an other parent
	void moveCategory(const unsigned int catId, const unsigned int newParentId);

protected:

private:
	// attributes
	// file name of library
	wxFileName m_fileName;

	// pointer to categories-vector
	std::vector<LibraryCategory>* m_ptrCategories;

	// pointer to entries-vector
	std::vector<LibraryEntry>* m_ptrEntries;

	// parentid
	unsigned int m_parentId;

	// functions
	// open library and procceed xml
	void openLibrary();

	// creates a new empty library
	void createEmptyLibrary();

	// load library.xml
	void LoadXml(wxInputStream& inStream);

	// add new category from xml
	void addCategory(wxString& name, unsigned int& categoryId, unsigned int& parentId);

	// add new entry from xml
	void addEntry(wxString& name, wxString& reference, unsigned int& categoryId);

	// add new category to xml
	void addXmlCategory(wxXmlDocument& xml, wxZipOutputStream& out, wxString& newName);

	// add new entry to xml
	void addXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out);

	// delete xml entry
	void deleteXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, wxString& reference);

	// rename xml category
	void renameXmlCategory(wxXmlDocument& xml, wxZipOutputStream& out, unsigned int cat_id, wxString& newName);

	// rename xml entry
	void renameXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, wxString& reference, wxString& newName);

	// add new category to xml
	void addNewXmlCategory(wxXmlDocument& xml, wxZipOutputStream& out, const unsigned int parentId, const wxString& newName);

	// move entry in xml
	void moveXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, const wxString& reference, const unsigned int new_parent_id);

	// move entry in xml
	void moveXmlCategory(wxXmlDocument& xml, wxZipOutputStream& out, const unsigned int catId, const unsigned int new_parent_id);
};

#endif // _LIBRARY_H_
