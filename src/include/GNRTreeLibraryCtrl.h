#ifndef _GNRTREELIBRARYCTRL_H_
#define _GNRTREELIBRARYCTRL_H_

#include <wx/treectrl.h>

class GNRTreeLibraryCtrl : public wxTreeCtrl
{
public:
	// ctor
	GNRTreeLibraryCtrl(wxWindow *parent, const wxWindowID id);
	
	// dtor
	virtual ~GNRTreeLibraryCtrl();
	
protected:

private:
	// attributes
	// current TreeId
	wxTreeItemId m_currentTreeID;
	
	// Id's
	static const long idMenuDelete;
	static const long idMenuPaste;
	static const long idMenuExport;
	static const long idMenuCreateCat;
	static const long idMenuRename;
	
	// functions
	void showMenu(wxTreeItemId id, const wxPoint& pt, bool cat);
	
	// event handler
	void OnItemMenu(wxTreeEvent& event);
	void OnRename(wxTreeEvent& event);
	void OnDelete(wxTreeEvent& event);
	void OnNewCategory(wxTreeEvent& event);
	void OnExport(wxTreeEvent& event);
	void OnPaste(wxTreeEvent& event);
	void OnMenuRename(wxTreeEvent& event);
};

#endif // _GNRTREELIBRARYCTRL_H_
