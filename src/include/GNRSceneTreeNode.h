#ifndef _GNRSCENETREENODE_H_
#define _GNRSCENETREENODE_H_

#include <list>
#include "GNRTreeSceneItemData.h"

class GNRSceneTreeNode
{
public:
	GNRSceneTreeNode();
	virtual ~GNRSceneTreeNode();
	void addTreeNode(GNRSceneTreeNode* node);
	void addTreeItem(GNRTreeSceneItemData* data);
	void setName(wxString name);
	
	GNRSceneTreeNode* getTreeNode();
	GNRTreeSceneItemData* getTreeItem();
	wxString getName();
protected:
private:
	std::list<GNRSceneTreeNode*> m_listSceneTreeNode;
	std::list<GNRTreeSceneItemData*> m_listTreeItem;
	
	std::list<GNRSceneTreeNode*>::iterator m_iterSceneTreeNode;
	std::list<GNRTreeSceneItemData*>::iterator m_iterTreeItem;
	
	wxString m_name;
	
};

#endif // _GNRSCENETREENODE_H_