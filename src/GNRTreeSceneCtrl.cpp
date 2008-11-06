#include "GNRTreeSceneCtrl.h"
#include "GNRTreeSceneItemData.h"

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
	//EVT_TREE_ITEM_RIGHT_CLICK(wxID_ANY, GNRTreeSceneCtrl::OnItemRClick)
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
	
	GNRTreeSceneItemData* item = (GNRTreeSceneItemData *)GetItemData(m_currentTreeID);
	
	if (item != NULL)
	{
		wxPoint clientpt = event.GetPoint();
		ShowMenu(m_currentTreeID, clientpt);
	}
	
	event.Skip();
}


void GNRTreeSceneCtrl::ShowMenu(wxTreeItemId id, const wxPoint& pt)
{
	// create dropdown-menu
	wxMenu menu(GetItemText(id));
	menu.Append(idMenuEdit, wxT("&Bearbeiten"));
	menu.AppendSeparator();
	menu.Append(idMenuAbout, wxT("&About"));
	
	PopupMenu(&menu, pt);
}

void GNRTreeSceneCtrl::OnEdit(wxCommandEvent& WXUNUSED(event))
{
	wxLogDebug(wxT("OnEdit"));
}

void GNRTreeSceneCtrl::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxString str;
	GNRTreeSceneItemData* item = (GNRTreeSceneItemData *)GetItemData(m_currentTreeID);
	str << wxT("Klicked on ") << item->getName();
	wxLogDebug(str);
}
