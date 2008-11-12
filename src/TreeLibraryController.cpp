/**
 * TreeLibraryController
 * @name        TreeLibraryController.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <memory>
#include <wx/bitmap.h>
#include <wx/filename.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/msgdlg.h>
#include <wx/sstream.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>

#include "OaxImport.h"
#include "Scene.h"
#include "TreeLibraryController.h"
#include "TreeLibraryItemData.h"
#include "GlobalDefine.h"
#include "md5.h"

#include "resources/icon_library_folder.xpm"
#include "resources/icon_library_assembly.xpm"
#include "resources/icon_library_container.xpm"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * Constructor.
 * @param      	 treectrl		     Assigns pointer to wxTreeCtrl.
 */
TreeLibraryController::TreeLibraryController(TreeLibraryCtrl* treectrl)
{
	// store Pointer to TreeCtrl
	m_treeCtrl = treectrl;
	
	// create image list
	createImageList();
	
	// create library
	m_library = new Library();
	
	// get pointer to Categories
	m_ptrCategories = m_library->getCategories();
	
	// get pointer to Entries
	m_ptrEntries = m_library->getEntries();
	
	// build treeCtrl
	buildTreeCtrl();
}

/**
 * Virtual Destructor.
 */
TreeLibraryController::~TreeLibraryController()
{
}

/**
 * get vector of strings for all cats
 * @param[in]   instream        wxInputStream& instream to read from
 * @param[in]   cat_id          int ID of category to add to (0 default)
 * @param[in]   entry_name      wxString categoryname
 * @return      wxString        add new entry and get full hash
 */
wxString TreeLibraryController::addEntry(wxInputStream& instream, wxString entry_name, unsigned int cat_id)
{
	// if found
	bool found = false;
	
	// strings to store md5-hash
	wxString objHash;
	wxString xmlHash;
	
	// pointer to wxZipEntry
	wxZipEntry* entry;
	
	// make zip of inputStream
	wxZipInputStream inZip(instream);
	
	// entry to first inZip entry
	entry = inZip.GetNextEntry();
	
	// walk through all entries and look for xml and obj
	while (entry)
	{
		// check if .xml
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			// make string of inputstream
			wxStringOutputStream strout(&xmlHash);
			
			// open zip stream
			inZip.OpenEntry(*entry);
			
			// read and write to strout
			inZip.Read(strout);
			
			// close zip entry
			inZip.CloseEntry();
			
			// get hash
			xmlHash = MD5wxString(xmlHash);
		}
		
		if (entry->GetName().Matches(wxT("*.obj")))
		{
			// make string of inputstream
			wxStringOutputStream strout(&objHash);
			
			// open zip entry
			inZip.OpenEntry(*entry);
			
			// read and write to strout
			inZip.Read(strout);
			
			// close zip entry
			inZip.CloseEntry();
			
			// get hash
			objHash = MD5wxString(objHash);
		}
		
		// get next Entry
		entry = inZip.GetNextEntry();
	}
	
	// reset stream
	instream.SeekI(0);
	
	// reference
	wxString ref = objHash + xmlHash + wxT(".oax");
	
	// iterator
	std::vector<LibraryEntry>::iterator it;
	
	for (it = m_ptrEntries->begin(); it != m_ptrEntries->end(); it++)
	{
		if (it->getReference() == ref)
		{
			// set found
			found = true;
		}
	}
	
	if (!found)
	{
		// new entry
		m_ptrEntries->push_back(LibraryEntry(entry_name, ref, cat_id));
		
		// add physical to library
		m_library->addEntry(ref, instream);
		
		// rebuild
		buildTreeCtrl();
	}
	
	return objHash + xmlHash;
}

/**
 * new id of cat set by name
 * @param[in]   newName         string to store name of new category
 * @return      unsigned int    new cat id
 */
unsigned int TreeLibraryController::addCategory(wxString newName)
{
	// iterator
	std::vector<LibraryCategory>::iterator it;
	
	// walk through all categories
	for (it = m_ptrCategories->begin(); it != m_ptrCategories->end(); it++)
	{
		// category found
		if (it->getName() == newName)
		{
			// return cat id of found category
			return it->getCatId();
		}
	}
	
	// not found, create new one
	Library::m_categoryId += 1;
	
	// new category, parent always 0
	m_ptrCategories->push_back(LibraryCategory(newName, Library::m_categoryId, 0));
	
	// add new physical category
	m_library->addCategory(newName);
	
	// return
	return Library::m_categoryId;
}

/**
 * new id of cat set by name
 * @param[in]   parent_id       int ID of parant category
 * @param[in]   name            wxString& name of cat
 * @return      int             new cat id
 */
bool TreeLibraryController::addCategory(const unsigned int& parent_id, const wxString& name)
{
	// iterator
	std::vector<LibraryCategory>::iterator it;
	
	// walk through all categories
	for (it = m_ptrCategories->begin(); it != m_ptrCategories->end(); it++)
	{
		// category found
		if (it->getName() == name && it->getParentId() == parent_id)
		{
			//same name in same category not allowed
			return false;
		}
	}
	
	// not found, create new one
	Library::m_categoryId += 1;
	
	// new category
	m_ptrCategories->push_back(LibraryCategory(name, Library::m_categoryId, parent_id));
	
	// rebuild tree
	buildTreeCtrl();
	
	// everything ok
	return true;
}

/**
 * delete cat by name
 * @param[in]       cat_id            int ID of category to delete
 */
void TreeLibraryController::deleteCategory(const unsigned int& cat_id)
{
	// new message dialog
	int answer = wxMessageBox(wxT("Alle Unterobjekte werden mitgel" ouml "scht. M" ouml "chten Sie fortfahren?"), wxT("Frage"), wxYES_NO);
	if (answer == wxID_YES)
	{
	}
}

/**
 * delete entry by reference
 * @param[in]   reference       wxString hash reference to entry
 */
void TreeLibraryController::deleteEntry(const wxString& reference)
{
	// iterator
	std::vector<LibraryEntry>::iterator it;
	
	// walk through all entries
	for (it = m_ptrEntries->begin(); it != m_ptrEntries->end(); it++)
	{
		// look if correct entry
		if ((it)->getReference() == reference)
		{
			// entry found
			break;
		}
	}
	
	// erase entry
	m_ptrEntries->erase(it);
	
	// delete physically
	m_library->deleteEntry(reference);
	
	// rebuild tree
	buildTreeCtrl();
}

/**
 * rename category by name to new name
 * @param[in]   cat_id          unsigned int ID of category to rename
 * @param[in]   new_name        wxString new name of cat
 */
void TreeLibraryController::renameCategory(const unsigned int& cat_id, const wxString& new_name)
{
	// iterator
	std::vector<LibraryCategory>::iterator it;
	
	// walk through all categories
	for (it = m_ptrCategories->begin(); it != m_ptrCategories->end(); it++)
	{
		// look if correct category
		if (it->getCatId() == cat_id)
		{
			// set new name
			(it)->setName(new_name);
		}
	}
	
	// change name in xml
	m_library->renameCategory(cat_id, new_name);
	
	// rebuild tree
	buildTreeCtrl();
}

/**
 * rename entry by reference to new name
 * @param[in]   reference       wxString old name of cat
 * @param[in]   new_name        wxString new name of cat
 */
void TreeLibraryController::renameEntry(const wxString& reference, const wxString& new_name)
{
	// iterator
	std::vector<LibraryEntry>::iterator it;
	
	// walk through all entries
	for (it = m_ptrEntries->begin(); it != m_ptrEntries->end(); it++)
	{
		// look if correct entry
		if ((it)->getReference() == reference)
		{
			// set new name
			(it)->setName(new_name);
		}
	}
	
	// change name in xml
	m_library->renameEntry(reference, new_name);
	
	// rebuild tree
	buildTreeCtrl();
}

/**
 * move entry to new parent
 * @param[in]       reference               wxString hash of entry
 * @param[in]       new_parent_id           new parent ID of cat
 */
void TreeLibraryController::moveEntry(const wxString& reference, const unsigned int& new_parent_id)
{
	// iterator
	std::vector<LibraryEntry>::iterator it;
	
	// walk through all entries
	for (it = m_ptrEntries->begin(); it != m_ptrEntries->end(); it++)
	{
		// look if correct entry
		if ((it)->getReference() == reference)
		{
#if defined(__ATHOS_DEBUG__)
			wxLogDebug((it)->toString());
#endif
			// set new name
			(it)->setCategoryId(new_parent_id);
		}
	}
	
	// change id of entry in xml
	//m_library->changeEntry(reference, new_parent_id);
	
#warning "entry has to be changed in xml..."
	
	// rebuild tree
	buildTreeCtrl();
}

/**
 * move category to new place
 * @param[in]       cat_id                      int ID of category to be moved
 * @param[in]       new_parent_id               int ID of new parent category
 */
void TreeLibraryController::moveCategory(const unsigned int& cat_id, const unsigned int& new_parent_id)
{
#if defined(__ATHOS_DEBUG__)
	wxString str;
	str << cat_id << wxT("\n");
	str << new_parent_id << wxT("\n");
	wxLogDebug(str);
#endif
	
	// iterator
	std::vector<LibraryCategory>::iterator it;
	
	// walk through all entries
	for (it = m_ptrCategories->begin(); it != m_ptrCategories->end(); it++)
	{
		// look if correct entry
		if ((it)->getCatId() == cat_id)
		{
#if defined(__ATHOS_DEBUG__)
			wxLogDebug((it)->toString());
#endif
			// set new name
			(it)->setParentId(new_parent_id);
		}
	}
	
	// change id of entry in xml
	//m_library->changeCategory(cat_id, new_parent_id);
	
#warning "category has to be changed in xml..."
	
	// rebuild tree
	buildTreeCtrl();
	
}

/**
 * on dragging decide what to drag to where
 * @param[in]       event                      TreeControlEvent of drag
 */
void TreeLibraryController::dragNdrop(TreeControlEvent& event)
{
	TreeLibraryItemData* src = event.getTreeItemSrc();
	TreeLibraryItemData* dst = event.getTreeItemDst();
	
	//if source was cat, move cat
	if (src->getCat())
	{
		moveCategory(src->getCatId(), dst->getCatId());
	}
	//else move entry
	else
	{
		moveEntry(src->getHash(), dst->getCatId());
	}
}


/**
 * merge two cats together
 * @param[in]       cat_id              int ID of first category to be merged
 * @param[in]       new_cat_id          int ID of second category to be merged to
 */
void TreeLibraryController::mergeCategories(const unsigned int& cat_id, const unsigned int& new_cat_id)
{

}

/**
 * edit entry with details
 * @param[in]       reference               wxString hash of entry
 */
void TreeLibraryController::editEntry(const wxString& reference)
{

}

/**
 * paste item to world
 * @param[in]   reference             wxString reference hash
 */
void TreeLibraryController::pasteEntry(const wxString& reference)
{
	// oax import
	OaxImport import;
	
	// get scene and prepare assembly
	Scene* scene = Scene::getInstance();
	Assembly* assembly;
	
	//query scene for assembly from hash or load from file
	assembly = scene->getOrigialFromHash(reference.BeforeFirst('.'));
	
	//found one, just clone from
	if (assembly != NULL)
	{
		//overwrite pointer here
		assembly = assembly->clone();
		
		//reset clone
		assembly->setXYZ(0.0,0.0,0.0);
		assembly->setPhi(0.0);
		assembly->setRho(0.0);
		assembly->setTheta(0.0);
	}
	//or load from library container
	else
	{
		// wxMemoryOutputStream to store oax data
		wxMemoryOutputStream* memOut;
		
		// get data
		memOut = m_library->getEntryData(reference);
		
		// wxMemoryInputStream to store oax data
		wxMemoryInputStream memIn(*memOut);
		
		// wxZipInputStream
		wxZipInputStream inZip(memIn);
		
		// import
		import.Load(inZip);
		
		// assembly pointer
		assembly = import.getAssembly();
		
		// set hash
		assembly->setHash(reference.BeforeFirst('.'));
		
		// delete memOut
		delete memOut;
	}
	
	// insert assembly
	scene->insertAssembly(assembly);
	
	// update gl
	scene->glRefresh();
}

/**
 * paste item to world
 * @param[in]   reference                   wxString reference hash
 * @return      wxMemoryOutputStream*       stream to data
 */
wxMemoryOutputStream* TreeLibraryController::exportEntry(const wxString& reference)
{
	return m_library->getEntryData(reference);
}

/**
 * create image list
 * @param[in]   size                int size of images used
 */
void TreeLibraryController::createImageList(const int& size)
{
	// Make an image list containing small icons
	wxImageList *images = new wxImageList(size, size, true);
	
	// should correspond to TreeCtrlIcon_xxx enum
	wxBusyCursor wait;
	
	// 3 icons
	wxIcon icons[3];
	icons[0] = wxIcon(icon_library_container_xpm);
	icons[1] = wxIcon(icon_library_folder_xpm);
	icons[2] = wxIcon(icon_library_assembly_xpm);
	
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
 * Build TreeControll on actual data.
 */
void TreeLibraryController::buildTreeCtrl()
{
	// delete old tree
	m_treeCtrl->DeleteAllItems();
	
	// local map to store categoryid and wxTreeItemId
	std::map<unsigned int, wxTreeItemId> catId;
	
	// category iterator
	std::vector<LibraryCategory>::iterator catit;
	
	// entry iterator
	std::vector<LibraryEntry>::iterator entit;
	
	// category-id iterator
	std::map<unsigned int, wxTreeItemId>::iterator catIdit;
	
	// local wxTreeItemId
	wxTreeItemId tiid;
	wxTreeItemId root;
	
	// new itemdata
	TreeLibraryItemData* itemData = new TreeLibraryItemData();
	
	// set category
	itemData->setCat(true);
	
	// set id
	itemData->setCatId(0);
	
	// set root
	root = tiid = m_treeCtrl->AddRoot(wxT("Bibliothek"), -1, -1, itemData);
	
	// set root image
	m_treeCtrl->SetItemImage(tiid, (int)TreeCtrlIcon_Root);
	
	// store root tiid
	catId.insert(std::pair<unsigned int, wxTreeItemId>(0, tiid));
	
	// walk through all categories and append to tree control
	for (catit = m_ptrCategories->begin(); catit != m_ptrCategories->end(); catit++)
	{
		// new itemdata
		TreeLibraryItemData* itemData = new TreeLibraryItemData();
		
		// set category
		itemData->setCat(true);
		
		// set cat id
		itemData->setCatId(catit->getCatId());
		
		// set parent id
		itemData->setParentId(catit->getParentId());
		
		// append to treectrl
		tiid = m_treeCtrl->AppendItem(catId[catit->getParentId()], catit->getName(), -1, -1, itemData);
		
		// set image
		m_treeCtrl->SetItemImage(tiid, (int)TreeCtrlIcon_Folder);
		
		// store tiid into map
		catId.insert(std::pair<unsigned int, wxTreeItemId>(catit->getCatId(), tiid));
	}
	
	// walk through all entrys and append to tree control
	for (entit = m_ptrEntries->begin(); entit != m_ptrEntries->end(); entit++)
	{
		// new itemdata
		TreeLibraryItemData* itemData = new TreeLibraryItemData();
		
		// set assembly
		itemData->setCat(false);
		
		// set hash
		itemData->setHash(entit->getReference());
		
		// set cat id
		itemData->setCatId(entit->getCategoryId());
		
		// append to treectrl
		tiid = m_treeCtrl->AppendItem(catId[entit->getCategoryId()], entit->getName(), -1, -1, itemData);
		
		// set image
		m_treeCtrl->SetItemImage(tiid, (int)TreeCtrlIcon_Assembly);
	}
	
	// sort
	for (catIdit = catId.begin(); catIdit != catId.end(); catIdit++)
	{
		m_treeCtrl->SortChildren(catIdit->second);
	}
	
	// expand root
	m_treeCtrl->Expand(root);
}
