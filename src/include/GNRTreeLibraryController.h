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

#include "GNRLibrary.h"
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
	
	// adds a new entry from import
	void addEntry(wxString& name, wxString& categoryname, wxInputStream& instream);
protected:

private:
	// attributes
	// TreeControl to manage
	wxTreeCtrl* m_treeCtrl;
	
	// flag if new cat
	bool m_newCat;
	
	// GNRLibrary pointer
	GNRLibrary* m_library;
	
	// vector to store all groups
	std::vector<GNRLibraryCategory>* m_ptrCategories;
	
	// vector to store all entrys
	std::vector<GNRLibraryEntry>* m_ptrEntries;
	
	// functions
	// if library does not exist, create an empty one
	void createEmptyLibrary();
	
	// builds the tree control and shows it
	void buildTreeCtrl();
	
	// adds a new category
	unsigned int addCategory(wxString& name);
	
	// create imagelist
	void createImageList(int size = 16);
};

#endif // _GNRTREELIBRARYCONTROLLER_H_
