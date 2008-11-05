#include "GNRSceneTreeNode.h"

/**
 * constructor of GNRSceneTreeNode
 * @access      public
 */
GNRSceneTreeNode::GNRSceneTreeNode()
{
	m_iterSceneTreeNode = NULL;
	m_iterAssemblyData = NULL;
}

/**
 * virtual destructor of GNRSceneTreeNode
 * @access      public
 */
GNRSceneTreeNode::~GNRSceneTreeNode()
{
	for (std::list<GNRAssemblyData*>::iterator it = m_listAssemblyData.begin(); it != m_listAssemblyData.end(); ++it)
	{
		delete(*it);
	}
	for (std::list<GNRSceneTreeNode*>::iterator it = m_listSceneTreeNode.begin(); it != m_listSceneTreeNode.end(); ++it)
	{
		delete(*it);
	}
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
 * add a new child AssemblyData to current Node
 * @param   GNRAssemblyData*   Pointer to the new GNRAssemblyData
 * @access      public
 */
void GNRSceneTreeNode::addAssemblyData(GNRAssemblyData* data)
{
	m_listAssemblyData.push_back(data);
}

/**
 * get next SceneTreeNode
 * @return   GNRSceneTreeNode*   Pointer to next GNRSceneTreeNode
 * @access      public
 */
GNRSceneTreeNode* GNRSceneTreeNode::getTreeNode()
{
	// if iterator not set yet, set it to first record
	if (m_iterSceneTreeNode == NULL)
	{
		m_iterSceneTreeNode = m_listSceneTreeNode.begin();
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
 * get next SceneTreeNode
 * @return   GNRAssemblyDate*   Pointer to next GNRAssemblyData
 * @access      public
 */
GNRAssemblyData* GNRSceneTreeNode::getAssemblyData()
{
	// if iterator not set yet, set it to first record
	if (m_iterAssemblyData == NULL)
	{
		m_iterAssemblyData = m_listAssemblyData.begin();
	}
	
	// if iterator not already at the end return
	if (m_iterAssemblyData != m_listAssemblyData.end())
	{
		return *m_iterAssemblyData++;
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
