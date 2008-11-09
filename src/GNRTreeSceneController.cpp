/**
 * GNRTreeSceneController
 * @name        GNRTreeSceneController.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/image.h>
#include <wx/imaglist.h>

#include "GNRTreeSceneController.h"
#include "GNRTreeSceneItemData.h"
#include "GNRScene.h"

#include "resources/icon_library_root.xpm"
#include "resources/icon_library_scene.xpm"
#include "resources/icon_library_trash.xpm"
#include "resources/icon_library_assembly.xpm"
#include "resources/icon_library_folder.xpm"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * Constructor.
 * @param       	treectrl		     Assigns pointer to wxTreeCtrl.
 */
GNRTreeSceneController::GNRTreeSceneController(wxTreeCtrl* treectrl)
{
	// store Pointer to TreeCtrl
	m_treeCtrl = treectrl;
	
	createImageList(16);
}

/**
 * Virtual Destructor.
 */
GNRTreeSceneController::~GNRTreeSceneController() {}

/**
 * creates a tree-image list
 * @param       size        size of image-list
 */
void GNRTreeSceneController::createImageList(int size)
{
	// Make an image list containing small icons
	wxImageList *images = new wxImageList(size, size, true);
	
	// should correspond to TreeCtrlIcon_xxx enum
	wxBusyCursor wait;
	
	// 5 icons
	wxIcon icons[5];
	icons[0] = wxIcon(icon_library_root_xpm);
	icons[1] = wxIcon(icon_library_scene_xpm);
	icons[2] = wxIcon(icon_library_trash_xpm);
	icons[3] = wxIcon(icon_library_assembly_xpm);
	icons[4] = wxIcon(icon_library_folder_xpm);
	
	int sizeOrig = icons[0].GetWidth();
	
	for (size_t i = 0; i < WXSIZEOF(icons); i++)
	{
		if (size == sizeOrig)
		{
			images->Add(icons[i]);
		}
		else
		{
			images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size, size)));
		}
	}
	
	// asign images
	m_treeCtrl->AssignImageList(images);
}

/**
 * builds new scene-treectrl
 */
void GNRTreeSceneController::createSceneTree()
{
	GNRScene* scene = GNRScene::getInstance();
	
	// reset tree
	m_treeCtrl->DeleteAllItems();
	
	// create root-entry
	wxTreeItemId rootID = m_treeCtrl->AddRoot(wxT("Root"));
	m_treeCtrl->SetItemImage(rootID, TreeCtrlIcon_Root);
	
	// create scene tree
	wxTreeItemId newID = m_treeCtrl->AppendItem(rootID, wxT("Szene"));
	m_treeCtrl->SetItemImage(newID, TreeCtrlIcon_Scene);
	createSceneTree(newID, scene->getRootAssembly());
	
	newID = m_treeCtrl->AppendItem(rootID, wxT("Papierkorb"));
	m_treeCtrl->SetItemImage(newID, TreeCtrlIcon_Trash);
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
 * @param   id       		id, the items are insert to
 * @param   assembly	        	assemlby to analyze
 */
void GNRTreeSceneController::createSceneTree(wxTreeItemId id, GNRAssembly* assembly)
{
	if (assembly->getType() == IS_OBJECT || assembly->getType() == IS_PRIMITIVE)
	{
		// generate ItemData for object and insert to tree
		GNRTreeSceneItemData* data = new GNRTreeSceneItemData;
		data->setAssembly(assembly);
		wxTreeItemId newID = m_treeCtrl->AppendItem(id, assembly->getName(), -1, -1, data);
		m_treeCtrl->SetItemImage(newID, TreeCtrlIcon_Assembly);
		
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
		m_treeCtrl->SetItemImage(newID, TreeCtrlIcon_Folder);
		
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
