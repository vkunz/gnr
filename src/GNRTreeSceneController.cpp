/**
 * GNRTreeSceneController
 * @name        GNRTreeSceneController.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/wfstream.h>
#include <wx/xml/xml.h>

#include "GNRTreeSceneController.h"

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
 * walk through tree and insert all items from nodes to scene-tree
 * @param   GNRSceneTreeNode*   Pointer to root-Node of (part-) tree
 * @param   wxTreeItemId        id, the items are insert to
 * @access  private
 */
void GNRTreeSceneController::evaluateTree(GNRSceneTreeNode* node, wxTreeItemId id)
{
	// start evaluation of childern to a new itemid
	GNRSceneTreeNode* myNode;
	wxTreeItemId newID;
	while (myNode = node->getTreeNode())
	{
		newID = m_treeCtrl->AppendItem(id, myNode->getName());
		evaluateTree(myNode, newID);
	}
	
	// append items of current node to current itemid
	GNRTreeSceneItemData* itemData;
	wxTreeItemId tmpID;
	while (itemData = node->getTreeItem())
	{
		tmpID = m_treeCtrl->AppendItem(id, itemData->getName(), -1, -1, itemData);
		// make selected bold
		if (itemData->getAssembly()->getMaster()->isType(IS_SELECTED))
		{
			m_treeCtrl->SetItemBold(tmpID);
		}
		// make hidden italic
		if (itemData->getAssembly()->isVisible() == false)
		{
			m_treeCtrl->SetItemFont(tmpID, *wxITALIC_FONT);
		}
	}
}

/**
 * builds new scene-treectrl
 * @param       GNRSceneTreeNode*        pointer to tree-root
 * @access      public
 */
void GNRTreeSceneController::updateTree(GNRSceneTreeNode* tree)
{
	// reset tree
	m_treeCtrl->DeleteAllItems();
	
	// set root
	wxTreeItemId rootID = m_treeCtrl->AddRoot(wxT("Root"));
	
	// build Tree
	evaluateTree(tree, rootID);
	
	// expand root + scene
	m_treeCtrl->Expand(rootID);
	wxTreeItemIdValue cookie;
	m_treeCtrl->Expand(m_treeCtrl->GetFirstChild(rootID, cookie));
	
	// delete given internal tree
	delete tree;
}
