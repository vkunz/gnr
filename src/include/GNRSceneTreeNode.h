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
	void setOwnTreeItem(GNRTreeSceneItemData* data);
	void setName(wxString name);
	
	GNRSceneTreeNode* getTreeNode();
	GNRTreeSceneItemData* getTreeItem();
	GNRTreeSceneItemData* getOwnTreeItem();
	wxString getName();
protected:
private:
	std::list<GNRSceneTreeNode*> m_listSceneTreeNode;
	std::list<GNRTreeSceneItemData*> m_listTreeItem;
	
	std::list<GNRSceneTreeNode*>::iterator m_iterSceneTreeNode;
	std::list<GNRTreeSceneItemData*>::iterator m_iterTreeItem;
	
	GNRTreeSceneItemData* m_itemData;
	
	wxString m_name;
	
	bool m_STN_valid, m_TI_valid;
};

#endif // _GNRSCENETREENODE_H_
