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
 */
GNRTreeSceneController::GNRTreeSceneController(wxTreeCtrl* treectrl)
{
	// store Pointer to TreeCtrl
	m_treeCtrl = treectrl;
}

/**
 * Virtual Destructor.
 */
GNRTreeSceneController::~GNRTreeSceneController()
{
	// do nothing
}


/**
 * Build TreeControll on actual data.
 */
void GNRTreeSceneController::buildTreeCtrl()
{
	// set root
	//wxTreeItemId tiid = m_treeCtrl->AddRoot(wxT("Szene"));
	
	//wxTreeItemId newId = m_treeCtrl->(tiid, wxT("abc"), 2, 2, item);
	
	
	return;
	
	//wxTreeItemId tiid = m_treeCtrl->AddRoot(wxT("GNRBibliothek"));
	
	// walk through all groups and append to root
	//for (m_groupsit = m_groups.begin(); m_groupsit != m_groups.end(); m_groupsit++) {
	//	m_treeCtrl->AppendItem(tiid, m_groupsit->first);
	//}
}


void GNRTreeSceneController::traverseTree(GNRSceneTreeNode* node, wxTreeItemId id)
{
	GNRSceneTreeNode* myNode;
	while (myNode = node->getTreeNode())
	{
		evaluateTree(myNode, id);
	}
}


void GNRTreeSceneController::evaluateTree(GNRSceneTreeNode* node, wxTreeItemId id)
{
	GNRSceneTreeNode* myNode;
	wxTreeItemId newID;
	while (myNode = node->getTreeNode())
	{
		newID = m_treeCtrl->AppendItem(id, myNode->getName());
		evaluateTree(myNode, newID);
	}
	
	GNRAssemblyData* assemblyData;
	while (assemblyData = node->getAssemblyData())
	{
		m_treeCtrl->AppendItem(id, assemblyData->m_name);
	}
	
}

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
	
	delete tree;
}
