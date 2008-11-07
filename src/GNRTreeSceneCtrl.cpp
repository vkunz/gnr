#include "GNRTreeSceneCtrl.h"

#include <wx/menu.h>
#include "GNRTreeControlEvent.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

const long GNRTreeSceneCtrl::idMenuEdit     = wxNewId();
const long GNRTreeSceneCtrl::idMenuVisible  = wxNewId();
const long GNRTreeSceneCtrl::idMenuHide     = wxNewId();
const long GNRTreeSceneCtrl::idMenuSelect   = wxNewId();
const long GNRTreeSceneCtrl::idMenuDeselect = wxNewId();
const long GNRTreeSceneCtrl::idMenuDelete   = wxNewId();
const long GNRTreeSceneCtrl::idMenuUndelete = wxNewId();

BEGIN_EVENT_TABLE(GNRTreeSceneCtrl, wxTreeCtrl)
	EVT_TREE_ITEM_MENU(wxID_ANY, GNRTreeSceneCtrl::OnItemMenu)
	EVT_MENU(idMenuEdit, GNRTreeSceneCtrl::OnEdit)
	EVT_MENU(idMenuVisible, GNRTreeSceneCtrl::OnVisible)
	EVT_MENU(idMenuHide, GNRTreeSceneCtrl::OnHide)
	EVT_MENU(idMenuSelect, GNRTreeSceneCtrl::OnSelect)
	EVT_MENU(idMenuDeselect, GNRTreeSceneCtrl::OnDeselect)
	EVT_MENU(idMenuDelete, GNRTreeSceneCtrl::OnDelete)
	EVT_MENU(idMenuUndelete, GNRTreeSceneCtrl::OnUndelete)
END_EVENT_TABLE()

/**
 * constructor of GNRTreeSceneCtrl
 * @param       wxWindow*       parent of TreeCtrl
 * @param       wxWindowID      wx-id for window
 * @param       wxPoint         TreeCtrl-position
 * @param       wxSize          size of TreeCtrl
 * @param       long            TreeCtrl-style
 * @param       wxValidator     validator for input
 * @param       wxString        name of TreeCtrl
 * @access      public
 */
GNRTreeSceneCtrl::GNRTreeSceneCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
                                   const wxValidator &validator, const wxString &name) : wxTreeCtrl(parent, id, pos, size, style, validator, name)
{
	m_currentTreeID = 0;
}

/**
 * destructor of GNRTreeSceneCtrl
 * @access      public
 */
GNRTreeSceneCtrl::~GNRTreeSceneCtrl() {}

/**
 * gets called by right click on tree-item, reads tree-item and initiates menu-building
 * @param       wxTreeEvent&    event with information to clicked item
 * @access      private
 */
void GNRTreeSceneCtrl::OnItemMenu(wxTreeEvent& event)
{
	m_currentTreeID = event.GetItem();
	
	treeItemData = (GNRTreeSceneItemData *)GetItemData(m_currentTreeID);
	
	if (treeItemData != NULL)
	{
		wxPoint clientpt = event.GetPoint();
		buildMenu(m_currentTreeID, clientpt);
	}
	
	event.Skip();
}


/**
 * builds dropdown menu for items, depending on state of clicked item
 * @param       wxTreeItemId    id of clicked item
 * @param       wxPoint         position, the menu should be displayed
 * @access      private
 */
void GNRTreeSceneCtrl::buildMenu(wxTreeItemId id, const wxPoint& pt)
{
	// create dropdown-menu
	wxMenu menu;
	
	if (treeItemData->getAssembly()->getMaster()->getType() == IS_TRASH)
	{
		menu.Append(idMenuUndelete, wxT("&Wiederherstellen"));
	}
	else
	{
		// no trash; add other options
		menu.Append(idMenuEdit, wxT("&Bearbeiten"));
		menu.AppendSeparator();
		
		// visible?
		if (treeItemData->getAssembly()->isVisible())
		{
			menu.Append(idMenuHide, wxT("&Verbergen"));
		}
		else
		{
			menu.Append(idMenuVisible, wxT("&Anzeigen"));
		}
		
		// selected?
		if (treeItemData->getAssembly()->getMaster()->getType() == IS_SELECTED)
		{
			menu.Append(idMenuDeselect, wxT("&Deselektieren"));
		}
		else
		{
			menu.Append(idMenuSelect, wxT("&Selektieren"));
		}
		
		menu.Append(idMenuDelete, wxT("&Löschen"));
	}
	
	PopupMenu(&menu, pt);
}

void GNRTreeSceneCtrl::OnEdit(wxCommandEvent& WXUNUSED(event))
{
	m_assemblyDataFrame = new GNRAssemblyDataFrame;
	m_assemblyDataFrame->Show();
	m_assemblyDataFrame->fillFields(treeItemData->getAssembly());
}

void GNRTreeSceneCtrl::OnVisible(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle setVisible
	GNRTreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENEVISIBLE);
	treeEvent.setAssembly(treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}

void GNRTreeSceneCtrl::OnHide(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle setHide
	GNRTreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENEHIDE);
	treeEvent.setAssembly(treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}

void GNRTreeSceneCtrl::OnSelect(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle select
	GNRTreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENESELECT);
	treeEvent.setAssembly(treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}

void GNRTreeSceneCtrl::OnDeselect(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle deselect
	GNRTreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENEDESELECT);
	treeEvent.setAssembly(treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}

void GNRTreeSceneCtrl::OnDelete(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle select
	GNRTreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENEDELETE);
	treeEvent.setAssembly(treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}

void GNRTreeSceneCtrl::OnUndelete(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle select
	GNRTreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENEUNDELETE);
	treeEvent.setAssembly(treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}
