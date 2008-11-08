/**
 * GNRTreeSceneController
 * @name        GNRTreeSceneController.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRTreeSceneController.h"
#include "GNRScene.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * Constructor.
 * @param       wxTreeCtrl*     Assigns pointer to wxTreeCtrl.
 * @access  public
 */
GNRTreeSceneController::GNRTreeSceneController(wxTreeCtrl* treectrl)
{
	// store Pointer to TreeCtrl
	m_treeCtrl = treectrl;
}

/**
 * Virtual Destructor.
 * @access  public
 */
GNRTreeSceneController::~GNRTreeSceneController() {}

/**
 * builds new scene-treectrl
 * @param       GNRSceneTreeNode*        pointer to tree-root
 * @access      public
 */
void GNRTreeSceneController::createSceneTree()
{
	GNRScene* scene = GNRScene::getInstance();
	
	// reset tree
	m_treeCtrl->DeleteAllItems();
	
	// create root-entry
	wxTreeItemId rootID = m_treeCtrl->AddRoot(wxT("Root"));
	
	// create scene tree
	wxTreeItemId newID = m_treeCtrl->AppendItem(rootID, wxT("Szene"));
	createSceneTree(newID, scene->getRootAssembly());
	
	newID = m_treeCtrl->AppendItem(rootID, wxT("Papierkorb"));
	createSceneTree(newID, scene->getTrash());
	
	// expand root + scene
	m_treeCtrl->Expand(rootID);
	wxTreeItemIdValue cookie;
	m_treeCtrl->Expand(m_treeCtrl->GetFirstChild(rootID, cookie));
	
	// sort children of scene
	m_treeCtrl->SortChildren(m_treeCtrl->GetFirstChild(rootID, cookie));
}

/**
 * walk through tree and insert all items from nodes to scene-tree
 * @param   wxTreeItemId        id, the items are insert to
 * @param   GNRAssembly*        assemlby to analyze
 * @access  private
 */
void GNRTreeSceneController::createSceneTree(wxTreeItemId id, GNRAssembly* assembly)
{
	if (assembly->getType() == IS_OBJECT || assembly->getType() == IS_PRIMITIVE)
	{
		// generate ItemData for object and insert to tree
		GNRTreeSceneItemData* data = new GNRTreeSceneItemData;
		data->setAssembly(assembly);
		wxTreeItemId newID = m_treeCtrl->AppendItem(id, assembly->getName(), -1, -1, data);
		
		// make selected bold
		if (assembly->getMaster()->getType() == IS_SELECTED)
		{
			m_treeCtrl->SetItemBold(newID);
		}
		// make hidden italic
		if (assembly->isVisible() == false)
		{
			m_treeCtrl->SetItemFont(newID, *wxITALIC_FONT);
		}
	}
	else if (assembly->getType() == IS_GROUP)
	{
		// generate ItemData for group
		GNRTreeSceneItemData* data = new GNRTreeSceneItemData;
		data->setAssembly(assembly);
		
		wxTreeItemId newID = m_treeCtrl->AppendItem(id, assembly->getName(), -1, -1, data);
		
		// make selected bold
		if (assembly->getMaster()->getType() == IS_SELECTED)
		{
			m_treeCtrl->SetItemBold(newID);
		}
		// make hidden italic
		if (assembly->isVisible() == false)
		{
			m_treeCtrl->SetItemFont(newID, *wxITALIC_FONT);
		}
		
		list<GNRAssembly*> parts = assembly->getPartList();
		for (list<GNRAssembly*>::const_iterator it = parts.begin(); it != parts.end(); ++it)
		{
			createSceneTree(newID, (*it));
		}
	}
	else if (assembly->getType() == IS_ROOT || assembly->getType() == IS_TRASH || assembly->getType() == IS_SELECTED)
	{
		list<GNRAssembly*> parts = assembly->getPartList();
		for (list<GNRAssembly*>::const_iterator it = parts.begin(); it != parts.end(); ++it)
		{
			createSceneTree(id, (*it));
		}
	}
}
