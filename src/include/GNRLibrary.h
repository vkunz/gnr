#ifndef _GNRLIBRARY_H_
#define _GNRLIBRARY_H_

#include <vector>
#include <wx/filename.h>
#include <wx/mstream.h>
#include <wx/string.h>
#include <wx/xml/xml.h>

#include "GNRLibraryCategory.h"
#include "GNRLibraryEntry.h"

class GNRLibrary
{
public:
	// ctor
	GNRLibrary();
	
	// dtor
	virtual ~GNRLibrary();
	
	// attributes
	// static variable to store id
	static unsigned int m_categoryId;
	
	// functions
	// retunrs m_ptrCategories
	std::vector<GNRLibraryCategory>* getCategories();
	
	// returns m_ptrEntries
	std::vector<GNRLibraryEntry>* getEntries();
	
	// add ne oax to library
	void addEntry(wxString reference, wxInputStream& inStream, bool newCat);
	
	// delete entry
	void deleteEntry(wxString reference);
	
	// get entry
	wxMemoryOutputStream* getEntryData(wxString reference);
	
	// rename category
	void renameCategory(wxString name, wxString newName);
	
	// rename entry
	void renameEntry(wxString name, wxString newName);
	
protected:

private:
	// attributes
	// file name of library
	wxFileName m_fileName;
	
	// pointer to categories-vector
	std::vector<GNRLibraryCategory>* m_ptrCategories;
	
	// pointer to entries-vector
	std::vector<GNRLibraryEntry>* m_ptrEntries;
	
	// parentid
	unsigned int m_parentId;
	
	// functions
	// return parentId of entry with name
	unsigned int getParentId(wxString name);
	
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
	void addXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, bool newCat);
	
	// delete XML entry
	void deleteXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, wxString& reference);
	
	// rename XML category
	void renameXmlCategory(wxXmlDocument& xml, wxZipOutputStream& out, wxString& reference, wxString& newName);
	
	// rename XML entry
	void renameXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, wxString& reference, wxString& newName);
};

#endif // _GNRLIBRARY_H_
