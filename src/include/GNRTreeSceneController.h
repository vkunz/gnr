/**
 * GNRTreeSceneController
 * @name                GNRTreeSceneController.h
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRTreeSceneController_H_
#define _GNRTreeSceneController_H_

#include <wx/treectrl.h>
#include "GNRSceneTreeNode.h"

/**
 * @class GNRTreeSceneController
 *
 * This class manages the treelibrary on the left side of the Application.
 */
class GNRTreeSceneController
{
public:
	// ctor
	GNRTreeSceneController(wxTreeCtrl* treectrl);
	
	// dtor
	virtual ~GNRTreeSceneController();
	
	void updateTree(GNRSceneTreeNode* tree);
	
protected:

private:
	// attributes
	wxTreeCtrl* m_treeCtrl;
	
	void evaluateTree(GNRSceneTreeNode* node, wxTreeItemId id);
};

#endif // _GNRTreeSceneController_H_
