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
	void OnItemRClick(wxTreeEvent& event);
	void OnItemMenu(wxTreeEvent& event);
	void OnEdit(wxCommandEvent& WXUNUSED(event));
	void OnAbout(wxCommandEvent& WXUNUSED(event));
	void ShowMenu(wxTreeItemId id, const wxPoint& pt);
	
	wxTreeItemId m_currentTreeID;
	GNRTreeSceneItemData* treeItemData;
	
	GNRAssemblyDataFrame* m_assemblyDataFrame;
	
	static const long idMenuEdit;
	static const long idMenuAbout;
	
	DECLARE_EVENT_TABLE()
};

#endif // _GNRTREESCENECTRL_H_
