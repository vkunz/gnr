/**
 * GNRTreeLibraryController
 * @name                GNRTreeLibraryController.h
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRTREELIBRARYCONTROLLER_H_
#define _GNRTREELIBRARYCONTROLLER_H_

#include <map>
#include <vector>
#include <wx/treectrl.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>

#include "GNRLibraryCategory.h"
#include "GNRLibraryEntry.h"

/**
 * @class GNRTreeLibraryController
 *
 * This class manages the treelibrary on the left side of the Application.
 */
class GNRTreeLibraryController
{
public:
	enum
	{
		TreeCtrlIcon_Folder = 0,
		TreeCtrlIcon_Assembly
	};
	
	// ctor
	GNRTreeLibraryController(wxTreeCtrl* treectrl);
	
	// dtor
	virtual ~GNRTreeLibraryController();
	
	// functions
	std::vector<wxString>* getAllCategories();
	
protected:

private:
	// attributes
	// parentId
	unsigned int m_parentId;
	
	// pointer to wxFFileInputStream
	wxFFileInputStream* m_inFile;
	
	// pointer to wxZipInputStream
	wxZipInputStream* m_inZip;
	
	// pointer to wxZipEntry
	wxZipEntry* m_zipEntry;
	
	// TreeControl to manage
	wxTreeCtrl* m_treeCtrl;
	
	// vector to store all groups
	std::vector<GNRLibraryCategory> m_category;
	std::vector<GNRLibraryCategory>::iterator m_categoryit;
	
	// vector to store all entrys
	std::vector<GNRLibraryEntry> m_entries;
	std::vector<GNRLibraryEntry>::iterator m_entriesit;
	
	// functions
	// return parentId of entry with name
	unsigned int getParentId(wxString name);
	
	// if library does not exist, create an empty one
	void createEmptyLibrary();
	
	// opens library and build groups and entries
	void openLibrary();
	
	// builds the tree control and shows it
	void buildTreeCtrl();
	
	// adds a new category
	void addCategory(wxString& name, unsigned int& categoryId, unsigned int& parentId);
	
	// adds a new category
	void addCategory(wxString& name);
	
	// adds a new entry from import
	void addEntry(wxString& name, wxString& reference, wxString& categoryname, wxInputStream& instream);
	
	// adds a new entry from xml
	void addEntry(wxString& name, wxString& reference, unsigned int& categoryId);
	
	// load xml file
	void LoadXml();
	
	// create imagelist
	void createImageList(int size = 16);
};

#endif // _GNRTREELIBRARYCONTROLLER_H_
