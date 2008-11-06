#include "GNRTreeSceneCtrl.h"

#include <wx/menu.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

const long GNRTreeSceneCtrl::idMenuEdit     = wxNewId();
const long GNRTreeSceneCtrl::idMenuAbout    = wxNewId();

BEGIN_EVENT_TABLE(GNRTreeSceneCtrl, wxTreeCtrl)
	EVT_TREE_ITEM_MENU(wxID_ANY, GNRTreeSceneCtrl::OnItemMenu)
	EVT_MENU(idMenuEdit, GNRTreeSceneCtrl::OnEdit)
	EVT_MENU(idMenuAbout, GNRTreeSceneCtrl::OnAbout)
END_EVENT_TABLE()

GNRTreeSceneCtrl::GNRTreeSceneCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
                                   const wxValidator &validator, const wxString &name) : wxTreeCtrl(parent, id, pos, size, style, validator, name)
{
	m_currentTreeID = 0;
}

GNRTreeSceneCtrl::~GNRTreeSceneCtrl() {}

void GNRTreeSceneCtrl::OnItemRClick(wxTreeEvent& event)
{

}

void GNRTreeSceneCtrl::OnItemMenu(wxTreeEvent& event)
{
	m_currentTreeID = event.GetItem();
	
	treeItemData = (GNRTreeSceneItemData *)GetItemData(m_currentTreeID);
	
	if (treeItemData != NULL)
	{
		wxPoint clientpt = event.GetPoint();
		ShowMenu(m_currentTreeID, clientpt);
	}
	
	event.Skip();
}


void GNRTreeSceneCtrl::ShowMenu(wxTreeItemId id, const wxPoint& pt)
{
	// create dropdown-menu
	wxMenu menu;
	menu.Append(idMenuEdit, wxT("&Bearbeiten"));
	menu.AppendSeparator();
	menu.Append(idMenuAbout, wxT("&Anzeigen/Verbergen"));
	
	PopupMenu(&menu, pt);
}

void GNRTreeSceneCtrl::OnEdit(wxCommandEvent& WXUNUSED(event))
{
	m_assemblyDataFrame = new GNRAssemblyDataFrame;
	m_assemblyDataFrame->Show();
	m_assemblyDataFrame->fillFields(treeItemData->getAssembly());
}

void GNRTreeSceneCtrl::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxString str;
	str << wxT("Klicked on ") << treeItemData->getName();
	//wxLogDebug(str);
}
