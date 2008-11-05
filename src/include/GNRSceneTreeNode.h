#ifndef _GNRSCENETREENODE_H_
#define _GNRSCENETREENODE_H_

#include <list>
#include "GNRAssemblyData.h"

class GNRSceneTreeNode
{
public:
	GNRSceneTreeNode();
	virtual ~GNRSceneTreeNode();
	void addTreeNode(GNRSceneTreeNode* node);
	void addAssemblyData(GNRAssemblyData* data);
	void setName(wxString name);
	
	GNRSceneTreeNode* getTreeNode();
	GNRAssemblyData* getAssemblyData();
	wxString getName();
protected:
private:
	std::list<GNRSceneTreeNode*> m_listSceneTreeNode;
	std::list<GNRAssemblyData*> m_listAssemblyData;
	
	std::list<GNRSceneTreeNode*>::iterator m_iterSceneTreeNode;
	std::list<GNRAssemblyData*>::iterator m_iterAssemblyData;
	
	wxString m_name;
	
};

#endif // _GNRSCENETREENODE_H_
