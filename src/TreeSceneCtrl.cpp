/**
 * TreeSceneCtrl
 * @name        	TreeSceneCtrl.cpp
 * @date        	2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "TreeSceneCtrl.h"

#include <wx/menu.h>
#include <wx/textdlg.h>
#include <wx/defs.h>

#include "NotifyEvent.h"
#include "TreeControlEvent.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

const long TreeSceneCtrl::idMenuEdit     = wxNewId();
const long TreeSceneCtrl::idMenuRename   = wxNewId();
const long TreeSceneCtrl::idMenuVisible  = wxNewId();
const long TreeSceneCtrl::idMenuHide     = wxNewId();
const long TreeSceneCtrl::idMenuSelect   = wxNewId();
const long TreeSceneCtrl::idMenuDeselect = wxNewId();
const long TreeSceneCtrl::idMenuDelete   = wxNewId();
const long TreeSceneCtrl::idMenuUndelete = wxNewId();
const long TreeSceneCtrl::idMenuEmptyTrash = wxNewId();

BEGIN_EVENT_TABLE(TreeSceneCtrl, wxTreeCtrl)
	EVT_CHAR(TreeSceneCtrl::OnKeyDown)
	EVT_TREE_ITEM_MENU(wxID_ANY, TreeSceneCtrl::OnItemMenu)
	EVT_TREE_ITEM_ACTIVATED(wxID_ANY, TreeSceneCtrl::OnItemActivated)
	EVT_MENU(idMenuEdit, TreeSceneCtrl::OnEdit)
	EVT_MENU(idMenuRename, TreeSceneCtrl::OnRename)
	EVT_MENU(idMenuVisible, TreeSceneCtrl::OnVisible)
	EVT_MENU(idMenuHide, TreeSceneCtrl::OnHide)
	EVT_MENU(idMenuSelect, TreeSceneCtrl::OnSelect)
	EVT_MENU(idMenuDeselect, TreeSceneCtrl::OnDeselect)
	EVT_MENU(idMenuDelete, TreeSceneCtrl::OnDelete)
	EVT_MENU(idMenuUndelete, TreeSceneCtrl::OnUndelete)
	EVT_MENU(idMenuEmptyTrash, TreeSceneCtrl::OnEmptyTrash)
END_EVENT_TABLE()

/**
 * constructor of TreeSceneCtrl
 * @param[in]       parent       		parent of TreeCtrl
 * @param[in]       id      			wx-id for window
 * @param[in]       pos         		TreeCtrl-position
 * @param[in]       size		          size of TreeCtrl
 * @param[in]       style            		TreeCtrl-style
 * @param[in]       validator     		validator for input
 * @param[in]       name        		name of TreeCtrl
 */
TreeSceneCtrl::TreeSceneCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
                             const wxValidator &validator, const wxString &name) : wxTreeCtrl(parent, id, pos, size, style, validator, name)
{
	m_currentTreeID = 0;
}

/**
 * destructor of TreeSceneCtrl
 */
TreeSceneCtrl::~TreeSceneCtrl() {}

/**
 * gets called by right click on tree-item, reads tree-item and initiates menu-building
 * @param     	  event	  	  event with information to clicked item
 */
void TreeSceneCtrl::OnItemMenu(wxTreeEvent& event)
{
	m_currentTreeID = event.GetItem();
	
	m_treeItemData = (TreeSceneItemData *)GetItemData(m_currentTreeID);
	
	if (m_treeItemData != NULL)
	{
		// build menu for item-operation
		wxPoint clientpt = event.GetPoint();
		buildMenu(clientpt);
	}
	else if (m_currentTreeID.IsOk() && GetItemText(m_currentTreeID) == wxT("Papierkorb"))
	{
		// build menu to empty trash
		wxMenu menu;
		menu.Append(idMenuEmptyTrash, wxT("Papierkorb leeren"));
		PopupMenu(&menu, event.GetPoint());
	}
}

/**
 * gets called by double-klick on a item
 * @param    	   event		    event with information to clicked item
 */
void TreeSceneCtrl::OnItemActivated(wxTreeEvent& event)
{
	m_currentTreeID = event.GetItem();
	
	m_treeItemData = (TreeSceneItemData *)GetItemData(m_currentTreeID);
	
	if (m_treeItemData != NULL && m_treeItemData->getAssembly()->getType() != IS_GROUP)
	{
		createAssemblyDataFrame();
	}
}

/**
 * builds dropdown menu for items, depending on state of clicked item
 * @param       pt        	 position, the menu should be displayed (wxPoint)
 */
void TreeSceneCtrl::buildMenu(const wxPoint& pt)
{
	// create dropdown-menu
	wxMenu menu;
	
	if (m_treeItemData->getAssembly()->getMaster()->getType() == IS_TRASH)
	{
		menu.Append(idMenuUndelete, wxT("&Wiederherstellen"));
	}
	else if (m_treeItemData->getAssembly()->getMaster()->getParent() == NULL ||
	         m_treeItemData->getAssembly()->getMaster()->getParent()->getType() == IS_ROOT ||
	         m_treeItemData->getAssembly()->getMaster()->getParent()->getType() == IS_SELECTED)
	{
		// no trash; add other options
		
		// group or item?
		if (m_treeItemData->getAssembly()->getType() != IS_GROUP)
		{
			menu.Append(idMenuEdit, wxT("&Bearbeiten"));
		}
		else
		{
			menu.Append(idMenuRename, wxT("&Umbennenen"));
		}
		
		menu.AppendSeparator();
		
		// selected?
		if (m_treeItemData->getAssembly()->getMaster()->getType() == IS_SELECTED)
		{
			menu.Append(idMenuDeselect, wxT("&Deselektieren"));
		}
		else
		{
			menu.Append(idMenuSelect, wxT("&Selektieren"));
		}
		
		// visible?
		if (m_treeItemData->getAssembly()->isVisible())
		{
			menu.Append(idMenuHide, wxT("&Verbergen"));
		}
		else
		{
			menu.Append(idMenuVisible, wxT("&Anzeigen"));
		}
		
		menu.Append(idMenuDelete, wxT("&Löschen"));
	}
	
	PopupMenu(&menu, pt);
}

void TreeSceneCtrl::OnEdit(wxCommandEvent& WXUNUSED(event))
{
	createAssemblyDataFrame();
}

void TreeSceneCtrl::createAssemblyDataFrame()
{
	m_assemblyDataFrame = new AssemblyDataFrame;
	m_assemblyDataFrame->Show();
	m_assemblyDataFrame->fillFields(m_treeItemData->getAssembly());
}

void TreeSceneCtrl::OnRename(wxCommandEvent& WXUNUSED(event))
{
	renameItem();
}

/**
 * fetches key down event
 * @param   	event		     key event of current canvas
 */
void TreeSceneCtrl::OnKeyDown(wxKeyEvent& event)
{
	if (event.GetKeyCode() == WXK_F2)
	{
		m_currentTreeID = GetSelection();
		
		m_treeItemData = (TreeSceneItemData *)GetItemData(m_currentTreeID);
		
		if (m_treeItemData != NULL)
		{
			renameItem();
		}
	}
}

void TreeSceneCtrl::renameItem()
{
	// create dialog and ask for name
	wxTextEntryDialog ted(this, wxT("Neuer Name"));
	if (ted.ShowModal() == wxID_CANCEL)
	{
		// if pressed cancel, do nothing
		return;
	}
	m_treeItemData->getAssembly()->setName(ted.GetValue());
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

void TreeSceneCtrl::OnVisible(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle setVisible
	TreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENEVISIBLE);
	treeEvent.setAssembly(m_treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}

void TreeSceneCtrl::OnHide(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle setHide
	TreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENEHIDE);
	treeEvent.setAssembly(m_treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}

void TreeSceneCtrl::OnSelect(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle select
	TreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENESELECT);
	if (m_treeItemData->getMaster()->isType(IS_GROUP))
	{
		treeEvent.setAssembly(m_treeItemData->getMaster());
	}
	else
	{
		treeEvent.setAssembly(m_treeItemData->getAssembly());
	}
	ProcessEvent(treeEvent);
}

void TreeSceneCtrl::OnDeselect(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle deselect
	TreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENEDESELECT);
	treeEvent.setAssembly(m_treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}

void TreeSceneCtrl::OnDelete(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle delete
	TreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENEDELETE);
	treeEvent.setAssembly(m_treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}

void TreeSceneCtrl::OnUndelete(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle undelete
	TreeControlEvent treeEvent(wxEVT_COMMAND_GNR_TREE_CONTROL);
	treeEvent.setEventType(SCENEUNDELETE);
	treeEvent.setAssembly(m_treeItemData->getAssembly());
	ProcessEvent(treeEvent);
}

void TreeSceneCtrl::OnEmptyTrash(wxCommandEvent& WXUNUSED(event))
{
	// send event to handle emptytrash
	NotifyEvent notifyEvent(wxEVT_COMMAND_GNR_NOTIFY);
	notifyEvent.setGNREventType(EMPTYTRASH);
	ProcessEvent(notifyEvent);
}
