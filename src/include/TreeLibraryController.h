/**
 * TreeLibraryController
 * @name                TreeLibraryController.h
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

#include "Library.h"
#include "LibraryCategory.h"
#include "LibraryEntry.h"
#include "TreeLibraryCtrl.h"

/**
 * @class TreeLibraryController
 *
 * This class manages the treelibrary on the left side of the Application.
 */
class TreeLibraryController
{
public:
	enum
	{
		TreeCtrlIcon_Root = 0,
		TreeCtrlIcon_Folder,
		TreeCtrlIcon_Assembly
	};
	
	// ctor
	TreeLibraryController(TreeLibraryCtrl* treectrl);
	
	// dtor
	virtual ~TreeLibraryController();
	
	// functions
	std::vector<wxString>* getAllCategories();
	
	// adds a new entry from import
	wxString addEntry(wxString& name, wxInputStream& instream, wxString categoryname = wxT("Sonstiges"));
	
	// delete a category
	void deleteCategory(wxString name);
	
	// delete an entry
	void deleteEntry(wxString reference);
	
	// delete a category
	void renameCategory(wxString name, wxString newName);
	
	// rename an entry
	void renameEntry(wxString reference, wxString newName);
	
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
	
	// Library pointer
	Library* m_library;
	
	// vector to store all groups
	std::vector<LibraryCategory>* m_ptrCategories;
	
	// vector to store all entrys
	std::vector<LibraryEntry>* m_ptrEntries;
	
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
