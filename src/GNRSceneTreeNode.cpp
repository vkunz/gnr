#include "GNRSceneTreeNode.h"

/**
 * constructor of GNRSceneTreeNode
 * @access      public
 */
GNRSceneTreeNode::GNRSceneTreeNode():
		m_STN_valid(false), m_TI_valid(false)
{
	m_itemData = NULL;
}

/**
 * virtual destructor of GNRSceneTreeNode
 * @access      public
 */
GNRSceneTreeNode::~GNRSceneTreeNode()
{
	for (std::list<GNRSceneTreeNode*>::iterator it = m_listSceneTreeNode.begin(); it != m_listSceneTreeNode.end(); ++it)
	{
		delete(*it);
	}
	
	// GNRTreeSceneItemData gets deleted by the tree itself
}

/**
 * add a new child TreeNode to current Node
 * @param   GNRSceneTreeNode*   Pointer to the new GNRSceneTreeNode
 * @access      public
 */
void GNRSceneTreeNode::addTreeNode(GNRSceneTreeNode* node)
{
	m_listSceneTreeNode.push_back(node);
}

/**
 * add a new child GNRTreeSceneItemData to current Node
 * @param   GNRTreeSceneItemData*   Pointer to the new GNRAssemblyData
 * @access      public
 */
void GNRSceneTreeNode::addTreeItem(GNRTreeSceneItemData* data)
{
	m_listTreeItem.push_back(data);
}

/**
 * get next SceneTreeNode
 * @return   GNRSceneTreeNode*   Pointer to next GNRSceneTreeNode
 * @access      public
 */
GNRSceneTreeNode* GNRSceneTreeNode::getTreeNode()
{
	// if iterator not set yet, set it to first record
	
	if (!m_STN_valid)
	{
		m_iterSceneTreeNode = m_listSceneTreeNode.begin();
		m_STN_valid = true;
	}
	
	// if iterator not already at the end return
	if (m_iterSceneTreeNode != m_listSceneTreeNode.end())
	{
		return *m_iterSceneTreeNode++;
	}
	else
	{
		return NULL;
	}
}

/**
 * get next child ItemData
 * @return   GNRSceneTreeNode*   Pointer to next GNRSceneTreeNode
 * @access      public
 */
GNRTreeSceneItemData* GNRSceneTreeNode::getTreeItem()
{
	// if iterator not set yet, set it to first record
	if (!m_TI_valid)
	{
		m_iterTreeItem = m_listTreeItem.begin();
		m_TI_valid = true;
	}
	
	// if iterator not already at the end return
	if (m_iterTreeItem != m_listTreeItem.end())
	{
		return *m_iterTreeItem++;
	}
	else
	{
		return NULL;
	}
}

/**
 * set name of node
 * @param   wxString   name of node
 * @access      public
 */
void GNRSceneTreeNode::setName(wxString name)
{
	m_name = name;
}

/**
 * return name of node
 * @return   wxString   name of node
 * @access      public
 */
wxString GNRSceneTreeNode::getName()
{
	return m_name;
}

/**
 * set ItemData of this Node
 * @param   GNRTreeSceneItemData*   GNRTreeSceneItemData of this node
 * @access      public
 */
void GNRSceneTreeNode::setOwnTreeItem(GNRTreeSceneItemData* data)
{
	m_itemData = data;
}

/**
 * get ItemData of this Node
 * @return  GNRTreeSceneItemData*   GNRTreeSceneItemData of this node
 * @access      public
 */
GNRTreeSceneItemData* GNRSceneTreeNode::getOwnTreeItem()
{
	return m_itemData;
}
