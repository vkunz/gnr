#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include <wx/menu.h>
#include <wx/textdlg.h>

#include "Enum.h"
#include "TreeControlEvent.h"
#include "TreeLibraryCtrl.h"
#include "TreeLibraryItemData.h"

const long TreeLibraryCtrl::idMenuDelete     = wxNewId();
const long TreeLibraryCtrl::idMenuPaste      = wxNewId();
const long TreeLibraryCtrl::idMenuExport     = wxNewId();
const long TreeLibraryCtrl::idMenuCreateCat  = wxNewId();
const long TreeLibraryCtrl::idMenuRename     = wxNewId();

/**
 * constructor
 * @param[in]       	parent		     wxWindow* parent pointer
 * @param[in]       	id  		     wxWindowID id of window
 */
TreeLibraryCtrl::TreeLibraryCtrl(wxWindow* parent, wxWindowID id)
{
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, wxT("TreeControl"));
	
	m_currentTreeID = 0;
	
	// connects menu with OnMenu
	Connect(wxID_ANY, wxEVT_COMMAND_TREE_ITEM_MENU,(wxObjectEventFunction)&TreeLibraryCtrl::OnItemMenu);
	
	// connects double-click with OnItemActivated
	Connect(wxID_ANY, wxEVT_COMMAND_TREE_ITEM_ACTIVATED, (wxObjectEventFunction)&TreeLibraryCtrl::OnItemActivated);
	
	// connects delete with OnDelete
	Connect(idMenuDelete,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TreeLibraryCtrl::OnDelete);
	
	// connects newCat with OnNewCategory
	Connect(idMenuCreateCat,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TreeLibraryCtrl::OnNewCategory);
	
	// connects export with OnExport
	Connect(idMenuExport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TreeLibraryCtrl::OnExport);
	
	// connects pase with OnPaste
	Connect(idMenuPaste,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TreeLibraryCtrl::OnPaste);
	
	// connects rename with OnMenuRename
	Connect(idMenuRename,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TreeLibraryCtrl::OnMenuRename);
	
	// connects begin-drag with OnBeginDrag
	Connect(wxID_ANY, wxEVT_COMMAND_TREE_BEGIN_DRAG, (wxObjectEventFunction)&TreeLibraryCtrl::OnBeginDrag);
	
	// connects end-drag with OnEndDrag
	Connect(wxID_ANY, wxEVT_COMMAND_TREE_END_DRAG, (wxObjectEventFunction)&TreeLibraryCtrl::OnEndDrag);
}

/**
 * destructor
 */
TreeLibraryCtrl::~TreeLibraryCtrl()
{
}

/**
 * show menu item
 * @param[in]       	id		     wxTreeItemId id of item
 * @param[in]       	pt  		 wxPoint& of item
 * @param[in]           cat          boolean if is cat or not
 */
void TreeLibraryCtrl::showMenu(wxTreeItemId id, const wxPoint& pt, bool cat)
{
	// create dropdown-menu
	wxMenu menu(GetItemText(id));
	
	// check if category or assembly
	if (cat)
	{
		// menu for categories
		menu.Append(idMenuCreateCat, wxT("&Neue Kategorie"));
		menu.Append(idMenuDelete, wxT("&L\u00F6schen"));
		menu.Append(idMenuRename, wxT("Umbenennen"));
	}
	else
	{
		// menu for assemblies
		menu.Append(idMenuPaste, wxT("&Einf\u00FCgen"));
		menu.Append(idMenuDelete, wxT("&L\u00F6schen"));
		menu.Append(idMenuRename, wxT("Umbenennen"));
		menu.AppendSeparator();
		menu.Append(idMenuExport, wxT("E&xportieren"));
	}
	
	// show menu
	PopupMenu(&menu, pt);
}

/**
 * show tree item menu
 * @param[in]       	event		     tree event
 */
void TreeLibraryCtrl::OnItemMenu(wxTreeEvent& event)
{
	m_currentTreeID = event.GetItem();
	
	TreeLibraryItemData* item = (TreeLibraryItemData*)GetItemData(m_currentTreeID);
	
	if (item != NULL)
	{
		wxPoint clientpt = event.GetPoint();
		showMenu(m_currentTreeID, clientpt, item->getCat());
	}
}

/**
 * on delete of entry
 * @param[in]       	WXUNUSED		     unused tree event
 */
void TreeLibraryCtrl::OnDelete(wxTreeEvent& WXUNUSED(event))
{
	// create event
	TreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// get item data
	TreeLibraryItemData* item = (TreeLibraryItemData*)GetItemData(m_currentTreeID);
	
	if (item->getCat())
	{
		// set event type
		gnr.setEventType(LIBRARYDELETECAT);
		
		// set cat id
		gnr.setCatId(item->getCatId());
	}
	else
	{
		// set event type
		gnr.setEventType(LIBRARYDELETEENTRY);
		
		// set hash
		gnr.setHash(item->getHash());
	}
	
	// fire event
	ProcessEvent(gnr);
}

/**
 * on new category
 * @param[in]       	WXUNUSED		     unused tree event
 */
void TreeLibraryCtrl::OnNewCategory(wxTreeEvent& WXUNUSED(event))
{
	wxTextEntryDialog ted(this, wxT("Name der neuen Kategorie."));
	
	if (ted.ShowModal() == wxID_CANCEL)
	{
		// if pressed cancel, do nothing
		return;
	}
	
	// create event
	TreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// set event type
	gnr.setEventType(LIBRARYNEWCAT);
	
	// get item data
	TreeLibraryItemData* item = (TreeLibraryItemData*)GetItemData(m_currentTreeID);
	
	// set parentId
	gnr.setParentId(item->getCatId());
	
	// set name of new category
	gnr.setNewName(ted.GetValue());
	
	// fire event
	ProcessEvent(gnr);
}

/**
 * on paste in tree
 * @param[in]       	WXUNUSED		     unused tree event
 */
void TreeLibraryCtrl::OnPaste(wxTreeEvent& WXUNUSED(event))
{
	// create event
	TreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// set event type
	gnr.setEventType(LIBRARYPASTE);
	
	// set name
	TreeLibraryItemData* item = (TreeLibraryItemData*)GetItemData(m_currentTreeID);
	gnr.setHash(item->getHash());
	
	// fire event
	ProcessEvent(gnr);
}

/**
 * on export from tree
 * @param[in]       	WXUNUSED		     unused tree event
 */
void TreeLibraryCtrl::OnExport(wxTreeEvent& WXUNUSED(event))
{
	// create event
	TreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// set event type
	gnr.setEventType(LIBRARYEXPORT);
	
	// set name
	TreeLibraryItemData* item = (TreeLibraryItemData*)GetItemData(m_currentTreeID);
	gnr.SetString(item->getName());
	
	// fire event
	ProcessEvent(gnr);
}

/**
 * on rename in tree
 * @param[in]       	WXUNUSED		     unused tree event
 */
void TreeLibraryCtrl::OnMenuRename(wxTreeEvent& WXUNUSED(event))
{
	// create event
	TreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// set name
	TreeLibraryItemData* item = (TreeLibraryItemData*)GetItemData(m_currentTreeID);
	
	// entry dialog
	wxTextEntryDialog ted(this, wxT("Neuer Name:"));
	
	if (ted.ShowModal() == wxID_CANCEL)
	{
		// if pressed cancel, do nothing
		return;
	}
	
	if (item->getCat())
	{
		// set event type
		gnr.setEventType(LIBRARYMENURENAMECAT);
		gnr.setCatId(item->getCatId());
		
		if (ted.GetValue().IsEmpty())
		{
			// set new name
			gnr.setNewName(wxT("neu"));
		}
		else
		{
			// set new name
			gnr.setNewName(ted.GetValue());
		}
	}
	else
	{
		// set event type
		gnr.setEventType(LIBRARYMENURENAMEENTRY);
		gnr.setHash(item->getHash());
		
		if (ted.GetValue().IsEmpty())
		{
			// set new name
			gnr.setNewName(wxT("neu"));
		}
		else
		{
			// set new name
			gnr.setNewName(ted.GetValue());
		}
	}
	
	// fire event
	ProcessEvent(gnr);
}

/**
 * on activate item in tree
 * @param[in]       	event		     tree event
 */
void TreeLibraryCtrl::OnItemActivated(wxTreeEvent& event)
{
	m_currentTreeID = event.GetItem();
	
	TreeLibraryItemData* treeItemData = (TreeLibraryItemData*)GetItemData(m_currentTreeID);
	
	if (treeItemData != NULL && treeItemData->getCat() == false)
	{
		OnPaste(event);
	}
}

/**
 * on begin dragging an item
 * @param[in]       	event		     tree event
 */
void TreeLibraryCtrl::OnBeginDrag(wxTreeEvent& event)
{
	// need to explicitly allow drag
	if (event.GetItem() != GetRootItem())
	{
		m_draggedItem = event.GetItem();
		event.Allow();
	}
}

/**
 * on end dragging an item
 * @param[in]       	event		     tree event
 */
void TreeLibraryCtrl::OnEndDrag(wxTreeEvent& event)
{
	wxTreeItemId itemSrc = m_draggedItem, itemDst = event.GetItem();
	m_draggedItem = (wxTreeItemId)0l;
	
	// get data from tree item
	TreeLibraryItemData* dst = (TreeLibraryItemData*)GetItemData(itemDst);
	TreeLibraryItemData* src = (TreeLibraryItemData*)GetItemData(itemSrc);
	
	// if null, cancel
	if (dst == NULL || src == NULL)
	{
		return;
	}
	
	// create event
	TreeControlEvent gnr(wxEVT_COMMAND_GNR_TREE_CONTROL);
	
	// set event type
	gnr.setEventType(LIBRARYMOVE);
	
	// set source and destination of drag
	gnr.setTreeItemDst(dst);
	gnr.setTreeItemSrc(src);
	
	// fire event
	ProcessEvent(gnr);
}
