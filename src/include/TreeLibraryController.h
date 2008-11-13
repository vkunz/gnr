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
#include <wx/treectrl.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>

#include "Library.h"
#include "LibraryCategory.h"
#include "LibraryEntry.h"
#include "TreeLibraryCtrl.h"
#include "TreeControlEvent.h"

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
	
	// add new category
	unsigned int addCategory(wxString newName);
	
	// adds a new category
	bool addCategory(const unsigned int parent_id, const wxString& newName);
	
	// adds a new entry from import
	wxString addEntry(wxInputStream& instream, wxString entry_name, unsigned int cat_id = 0);
	
	// delete a category
	void deleteCategory(const unsigned int& cat_id);
	// delete an entry
	void deleteEntry(const wxString& reference);
	
	// delete a category
	void renameCategory(const unsigned int& cat_id, const wxString& new_name);
	// rename an entry
	void renameEntry(const wxString& reference, const wxString& new_name);
	
	// move a category
	void moveCategory(const unsigned int& cat_id, const unsigned int& new_parent_id);
	// move an entry
	void moveEntry(const wxString& reference, const unsigned int& new_parent_id);
	// drag and drop
	void dragNdrop(TreeControlEvent& event);
	
	// merge both cats into new_cat
	void mergeCategories(const unsigned int& cat_id, const unsigned int& new_cat_id);
	
	// edit an entry (like in scene tree)
	void editEntry(const wxString& reference);
	// paste an entry into scene
	void pasteEntry(const wxString& reference);
	
	// export an entry onto fileystem
	wxMemoryOutputStream* exportEntry(const wxString& reference);
	
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
	
	// create imagelist
	void createImageList(const int& size = 16);
};

#endif // _GNRTREELIBRARYCONTROLLER_H_
