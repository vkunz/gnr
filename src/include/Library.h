#ifndef _GNRLIBRARY_H_
#define _GNRLIBRARY_H_

#include <vector>
#include <wx/filename.h>
#include <wx/mstream.h>
#include <wx/string.h>
#include <wx/xml/xml.h>

#include "LibraryCategory.h"
#include "LibraryEntry.h"

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
	// return parentId of entry with name
	unsigned int getParentId(unsigned int cat_id);
	
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
};

#endif // _GNRLIBRARY_H_
