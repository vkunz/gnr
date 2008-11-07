#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include <wx/menu.h>
#include <wx/textdlg.h>

#include "GNREnum.h"
#include "GNRTreeControlEvent.h"
#include "GNRTreeLibraryCtrl.h"
#include "GNRTreeLibraryItemData.h"

const long GNRTreeLibraryCtrl::idMenuDelete     = wxNewId();
const long GNRTreeLibraryCtrl::idMenuPaste      = wxNewId();
const long GNRTreeLibraryCtrl::idMenuExport     = wxNewId();
const long GNRTreeLibraryCtrl::idMenuCreateCat  = wxNewId();

// ctor
GNRTreeLibraryCtrl::GNRTreeLibraryCtrl(wxWindow* parent, wxWindowID id)
{
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_EDIT_LABELS, wxDefaultValidator, wxT("TreeControl"));
	
	m_currentTreeID = 0;
	
	// connects menu with OnMenu
	Connect(wxID_ANY, wxEVT_COMMAND_TREE_ITEM_MENU,(wxObjectEventFunction)&GNRTreeLibraryCtrl::OnItemMenu);
	
	// connects rename with OnRename
	Connect(wxID_ANY,wxEVT_COMMAND_TREE_END_LABEL_EDIT,(wxObjectEventFunction)&GNRTreeLibraryCtrl::OnRename);
	
	// connects delete with OnDelete
	Connect(idMenuDelete,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRTreeLibraryCtrl::OnDelete);
	
	// connects newCat with OnNewCategory
	Connect(idMenuCreateCat,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRTreeLibraryCtrl::OnNewCategory);
	
	// connects export with OnExport
	Connect(idMenuExport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRTreeLibraryCtrl::OnExport);
	
	// connects pase with OnPaste
	Connect(idMenuPaste,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRTreeLibraryCtrl::OnPaste);
}

// dtor
GNRTreeLibraryCtrl::~GNRTreeLibraryCtrl()
{
	// do nothing
}

void GNRTreeLibraryCtrl::showMenu(wxTreeItemId id, const wxPoint& pt, bool cat)
{
	// create dropdown-menu
	wxMenu menu(GetItemText(id));
	
	if (cat)
	{
		// menu for categories
		menu.Append(idMenuCreateCat, wxT("&Neue Kategorie"));
		menu.Append(idMenuDelete, wxT("&L\u00F6schen"));
	}
	else
	{
		// menu for assemblies
		menu.Append(idMenuPaste, wxT("&Einf\u00FCgen"));
		menu.Append(idMenuDelete, wxT("&L\u00F6schen"));
		menu.AppendSeparator();
		menu.Append(idMenuExport, wxT("E&xportieren"));
	}
	
	PopupMenu(&menu, pt);
}

void GNRTreeLibraryCtrl::OnItemMenu(wxTreeEvent& event)
{
	m_currentTreeID = event.GetItem();
	
	GNRTreeLibraryItemData* item = (GNRTreeLibraryItemData*)GetItemData(m_currentTreeID);
	
	if (item != NULL)
	{
		wxPoint clientpt = event.GetPoint();
		showMenu(m_currentTreeID, clientpt, item->getCat());
	}
}

void GNRTreeLibraryCtrl::OnRename(wxTreeEvent& event)
{
	// create event
	GNRTreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// set event type
	gnr.setEventType(LIBRARYRENAME);
	
	m_currentTreeID = event.GetItem();
	
	// set name
	GNRTreeLibraryItemData* item = (GNRTreeLibraryItemData*)GetItemData(m_currentTreeID);
	gnr.SetInt(m_currentTreeID);
	gnr.SetString(item->getName());
	gnr.setNewName(event.GetLabel());
	
	// set cat
	gnr.setCat(item->getCat());
	
	// fire event
	ProcessEvent(gnr);
}

void GNRTreeLibraryCtrl::OnDelete(wxTreeEvent& event)
{
	// create event
	GNRTreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// set event type
	gnr.setEventType(LIBRARYDELETE);
	
	// set name
	GNRTreeLibraryItemData* item = (GNRTreeLibraryItemData*)GetItemData(m_currentTreeID);
	gnr.SetString(item->getName());
	
	// set cat
	gnr.setCat(item->getCat());
	
	// fire event
	ProcessEvent(gnr);
}

void GNRTreeLibraryCtrl::OnNewCategory(wxTreeEvent& event)
{
	wxTextEntryDialog ted(this, wxT("Name der neuen Kategorie."));
	
	if (ted.ShowModal() == wxID_CANCEL)
	{
		// if pressed cancel, do nothing
		return;
	}
	
	// create event
	GNRTreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// set event type
	gnr.setEventType(LIBRARYNEWCAT);
	
	// set name
	GNRTreeLibraryItemData* item = (GNRTreeLibraryItemData*)GetItemData(m_currentTreeID);
	gnr.SetString(item->getName());
	
	// set name of new category
	gnr.setNewName(ted.GetValue());
	
	// fire event
	ProcessEvent(gnr);
}

void GNRTreeLibraryCtrl::OnPaste(wxTreeEvent& event)
{
	// create event
	GNRTreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// set event type
	gnr.setEventType(LIBRARYPASTE);
	
	// set name
	GNRTreeLibraryItemData* item = (GNRTreeLibraryItemData*)GetItemData(m_currentTreeID);
	gnr.SetString(item->getName());
	
	// fire event
	ProcessEvent(gnr);
}

void GNRTreeLibraryCtrl::OnExport(wxTreeEvent& event)
{
	// create event
	GNRTreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// set event type
	gnr.setEventType(LIBRARYEXPORT);
	
	// set name
	GNRTreeLibraryItemData* item = (GNRTreeLibraryItemData*)GetItemData(m_currentTreeID);
	gnr.SetString(item->getName());
	
	// fire event
	ProcessEvent(gnr);
}
