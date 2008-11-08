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
#include <wx/wfstream.h>
#include <wx/zipstrm.h>

#include "GNRLibrary.h"
#include "GNRLibraryCategory.h"
#include "GNRLibraryEntry.h"
#include "GNRTreeLibraryCtrl.h"

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
		TreeCtrlIcon_Root = 0,
		TreeCtrlIcon_Folder,
		TreeCtrlIcon_Assembly
	};
	
	// ctor
	GNRTreeLibraryController(GNRTreeLibraryCtrl* treectrl);
	
	// dtor
	virtual ~GNRTreeLibraryController();
	
	// functions
	std::vector<wxString>* getAllCategories();
	
	// adds a new entry from import
	wxString addEntry(wxString& name, wxInputStream& instream, wxString categoryname = wxT("Sonstiges"));
	
	// delete a category
	void deleteCategory(wxString name);
	
	// delete an entry
	void deleteEntry(wxString name);
	
	// delete a category
	void renameCategory(wxString name, wxString newName);
	
	// rename an entry
	void renameEntry(wxString name, wxString newName);
	
	// add new category
	void addCategory(wxString parentName, wxString newName);
	
	// paste an entry into scene
	void pasteEntry(wxString reference);
	
	// export an entry onto fileystem
	wxMemoryOutputStream* exportEntry(wxString reference);
	
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
