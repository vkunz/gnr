#ifndef _GNRTREESCENECTRL_H_
#define _GNRTREESCENECTRL_H_

#include <wx/treectrl.h>
#include "GNRTreeSceneItemData.h"
#include "GNRAssemblyDataFrame.h"

class GNRTreeSceneCtrl: public wxTreeCtrl
{
public:
	GNRTreeSceneCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
	                 const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTreeCtrlNameStr);
	virtual ~GNRTreeSceneCtrl();
protected:
private:
	void OnItemMenu(wxTreeEvent& event);
	void OnItemActivated(wxTreeEvent& event);
	void OnEdit(wxCommandEvent& WXUNUSED(event));
	void OnRename(wxCommandEvent& WXUNUSED(event));
	void OnVisible(wxCommandEvent& WXUNUSED(event));
	void OnHide(wxCommandEvent& WXUNUSED(event));
	void OnSelect(wxCommandEvent& WXUNUSED(event));
	void OnDeselect(wxCommandEvent& WXUNUSED(event));
	void OnDelete(wxCommandEvent& WXUNUSED(event));
	void OnUndelete(wxCommandEvent& WXUNUSED(event));
	
	void buildMenu(wxTreeItemId id, const wxPoint& pt);
	void createAssemblyDataFrame();
	
	wxTreeItemId m_currentTreeID;
	GNRTreeSceneItemData* treeItemData;
	
	GNRAssemblyDataFrame* m_assemblyDataFrame;
	
	static const long idMenuEdit;
	static const long idMenuRename;
	static const long idMenuVisible;
	static const long idMenuHide;
	static const long idMenuSelect;
	static const long idMenuDeselect;
	static const long idMenuDelete;
	static const long idMenuUndelete;
	
	DECLARE_EVENT_TABLE()
};

#endif // _GNRTREESCENECTRL_H_
