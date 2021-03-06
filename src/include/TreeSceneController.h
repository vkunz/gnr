/**
 * TreeSceneController
 * @name                TreeSceneController.h
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRTreeSceneController_H_
#define _GNRTreeSceneController_H_

#include <wx/treectrl.h>

class Assembly;
class TreeSceneCtrl;

/**
 * @class TreeSceneController
 *
 * This class manages the treelibrary on the left side of the Application.
 */
class TreeSceneController
{
public:
	// ctor
	TreeSceneController(TreeSceneCtrl* treectrl);

	// dtor
	virtual ~TreeSceneController();

	void createSceneTree();

protected:

private:
	// attributes
	wxTreeCtrl* m_treeCtrl;

	void createSceneTree(wxTreeItemId id, Assembly* assembly);
	void createImageList(int size);

	enum { TreeCtrlIcon_Root = 0, TreeCtrlIcon_Scene, TreeCtrlIcon_Trash, TreeCtrlIcon_Assembly, TreeCtrlIcon_Folder };

};

#endif // _GNRTreeSceneController_H_
