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

/**
 * @class GNRTreeLibraryController
 *
 * This class manages the treelibrary on the left side of the Application.
 */
class GNRTreeLibraryController
{
public:
	// ctor
	GNRTreeLibraryController(wxTreeCtrl* treectrl);
	
	// dtor
	virtual ~GNRTreeLibraryController();
	
	// functions
	std::vector<wxString>* getAllCategories();
	
protected:

private:
	// attributes
	wxTreeCtrl* m_treeCtrl;
	
	// map to store groupname and groupid
	std::map<wxString, unsigned long int> m_groups;
	std::map<wxString, unsigned long int>::iterator m_groupsit;
	
	// map to store entryreference and groupid
	std::map<wxString, unsigned long int> m_entries;
	std::map<wxString, unsigned long int>::iterator m_entriesit;
	
	// functions
	void openLibrary();
	void buildTreeCtrl();
};

#endif // _GNRTREELIBRARYCONTROLLER_H_
