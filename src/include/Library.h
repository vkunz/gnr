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
	
	// add ne oax to library
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
	
	// add new entry to XML
	void addXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out);
	
	// delete XML entry
	void deleteXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, wxString& reference);
	
	// rename XML category
	void renameXmlCategory(wxXmlDocument& xml, wxZipOutputStream& out, unsigned int cat_id, wxString& newName);
	
	// rename XML entry
	void renameXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, wxString& reference, wxString& newName);
};

#endif // _GNRLIBRARY_H_
