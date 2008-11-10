#ifndef _GNRTREELIBRARYCTRL_H_
#define _GNRTREELIBRARYCTRL_H_

#include <wx/treectrl.h>

class TreeLibraryCtrl : public wxTreeCtrl
{
public:
	// ctor
	TreeLibraryCtrl(wxWindow *parent, const wxWindowID id);
	
	// dtor
	virtual ~TreeLibraryCtrl();
	
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
	void OnItemActivated(wxTreeEvent& event);
	void OnRename(wxTreeEvent& WXUNUSED(event));
	void OnDelete(wxTreeEvent& WXUNUSED(event));
	void OnNewCategory(wxTreeEvent& WXUNUSED(event));
	void OnExport(wxTreeEvent& WXUNUSED(event));
	void OnPaste(wxTreeEvent& WXUNUSED(event));
	void OnMenuRename(wxTreeEvent& WXUNUSED(event));
};

#endif // _GNRTREELIBRARYCTRL_H_
