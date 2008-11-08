/**
 * GNRTreeLibraryController
 * @name        GNRTreeLibraryController.cpp
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

#include "GNROaxImport.h"
#include "GNRScene.h"
#include "GNRTreeLibraryController.h"
#include "GNRTreeLibraryItemData.h"
#include "md5.h"

#include "resources/icon_library_folder.xpm"
#include "resources/icon_library_assembly.xpm"
#include "resources/icon_library_container.xpm"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * Constructor.
 * @param       wxTreeCtrl*     Assigns pointer to wxTreeCtrl.
 */
GNRTreeLibraryController::GNRTreeLibraryController(GNRTreeLibraryCtrl* treectrl)
{
	// store Pointer to TreeCtrl
	m_treeCtrl = treectrl;
	
	// create image list
	createImageList();
	
	// create library
	m_library = new GNRLibrary();
	
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
GNRTreeLibraryController::~GNRTreeLibraryController()
{
}

std::vector<wxString>* GNRTreeLibraryController::getAllCategories()
{
	// create pointer of a vector
	std::vector<wxString>* ptrCat =  new std::vector<wxString>;
	
	// iterator
	std::vector<GNRLibraryCategory>::iterator it;
	
	// walk through all categories and store string into vector
	for (it = m_ptrCategories->begin(); it != m_ptrCategories->end(); it++)
	{
		ptrCat->push_back(it->getName());
	}
	
	return ptrCat;
}

wxString GNRTreeLibraryController::addEntry(wxString& name, wxInputStream& instream, wxString categoryname)
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
	std::vector<GNRLibraryEntry>::iterator it;
	
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
		// cat-id
		unsigned int cat = addCategory(categoryname);
		
		// new entry
		m_ptrEntries->push_back(GNRLibraryEntry(name, ref, cat));
		
		// add physical to library
		m_library->addEntry(ref, instream, m_newCat);
		
		// rebuild
		buildTreeCtrl();
	}
	
	return objHash + xmlHash;
}

unsigned int GNRTreeLibraryController::addCategory(wxString& name)
{
	// check if already exist
	m_newCat = true;
	
	// return
	unsigned int ret;
	
	// iterator
	std::vector<GNRLibraryCategory>::iterator it;
	
	// walk through all categories
	for (it = m_ptrCategories->begin(); it != m_ptrCategories->end(); it++)
	{
		// category found
		if (it->getName() == name)
		{
			// set return
			ret = it->getCategoryId();
			
			// set found
			m_newCat = false;
		}
	}
	
	// not found, create new one
	if (m_newCat)
	{
		// increment id
		GNRLibrary::m_categoryId += 1;
		
		// new category
		m_ptrCategories->push_back(GNRLibraryCategory(name, GNRLibrary::m_categoryId, 0));
		
		// set return
		ret = GNRLibrary::m_categoryId;
	}
	
	// return
	return ret;
}

void GNRTreeLibraryController::deleteCategory(wxString name)
{
	// new message dialog
	int answer = wxMessageBox(wxT("Alle Unterobjekte werden mitgelöscht. Möchten Sie fortfahren?"), wxT("Frage"), wxYES_NO);
	if (answer == wxID_YES)
	{
	}
}

void GNRTreeLibraryController::deleteEntry(wxString reference)
{
	// iterator
	std::vector<GNRLibraryEntry>::iterator it;
	
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

void GNRTreeLibraryController::renameCategory(wxString name, wxString newName)
{
	// iterator
	std::vector<GNRLibraryCategory>::iterator it;
	
	// walk through all categories
	for (it = m_ptrCategories->begin(); it != m_ptrCategories->end(); it++)
	{
		// look if correct category
		if ((it->getName() == name))
		{
			// set new name
			(it)->setName(newName);
		}
	}
	
	// change name in xml
	m_library->renameCategory(name, newName);
	
	// rebuild tree
	buildTreeCtrl();
}

void GNRTreeLibraryController::renameEntry(wxString reference, wxString newName)
{
	// iterator
	std::vector<GNRLibraryEntry>::iterator it;
	
	// walk through all entries
	for (it = m_ptrEntries->begin(); it != m_ptrEntries->end(); it++)
	{
		// look if correct entry
		if ((it)->getReference() == reference)
		{
			// set new name
			(it)->setName(newName);
		}
	}
	
	// change name in xml
	m_library->renameEntry(reference, newName);
	
	// rebuild tree
	buildTreeCtrl();
}

void GNRTreeLibraryController::addCategory(wxString parentName, wxString catName)
{

}

void GNRTreeLibraryController::pasteEntry(wxString reference)
{
	// oax import
	GNROaxImport import;
	
	// get scene and prepare assembly
	GNRScene* scene = GNRScene::getInstance();
	GNRAssembly* assembly;
	
	//query scene for hash or load from file
	assembly = scene->getOrigialFromHash(reference.BeforeFirst('.'));
	
	//found one, just clone from
	if (assembly != NULL)
	{
		//overwrite pointer here
		assembly = assembly->clone();
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

wxMemoryOutputStream* GNRTreeLibraryController::exportEntry(wxString reference)
{
	return m_library->getEntryData(reference);
}

void GNRTreeLibraryController::createImageList(int size)
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
void GNRTreeLibraryController::buildTreeCtrl()
{
	// delete old tree
	m_treeCtrl->DeleteAllItems();
	
	// local map to store categoryid and wxTreeItemId
	std::map<unsigned int, wxTreeItemId> catId;
	
	// category iterator
	std::vector<GNRLibraryCategory>::iterator catit;
	
	// entry iterator
	std::vector<GNRLibraryEntry>::iterator entit;
	
	// category-id iterator
	std::map<unsigned int, wxTreeItemId>::iterator catIdit;
	
	// local wxTreeItemId
	wxTreeItemId tiid;
	wxTreeItemId root;
	
	// new itemdata
	GNRTreeLibraryItemData* itemData = new GNRTreeLibraryItemData();
	
	// set category
	itemData->setCat(true);
	
	// set root
	root = tiid = m_treeCtrl->AddRoot(wxT("GNRBibliothek"), -1, -1, itemData);
	
	// set root image
	m_treeCtrl->SetItemImage(tiid, (int)TreeCtrlIcon_Root);
	
	// store root tiid
	catId.insert(std::pair<unsigned int, wxTreeItemId>(0, tiid));
	
	// walk through all categories and append to tree control
	for (catit = m_ptrCategories->begin(); catit != m_ptrCategories->end(); catit++)
	{
		// new itemdata
		GNRTreeLibraryItemData* itemData = new GNRTreeLibraryItemData();
		
		// set category
		itemData->setCat(true);
		itemData->setName(catit->getName());
		
		// append to treectrl
		tiid = m_treeCtrl->AppendItem(catId[catit->getParentId()], catit->getName(), -1, -1, itemData);
		
		// set image
		m_treeCtrl->SetItemImage(tiid, (int)TreeCtrlIcon_Folder);
		
		// store tiid into map
		catId.insert(std::pair<unsigned int, wxTreeItemId>(catit->getCategoryId(), tiid));
	}
	
	// walk through all entrys and append to tree control
	for (entit = m_ptrEntries->begin(); entit != m_ptrEntries->end(); entit++)
	{
		// new itemdata
		GNRTreeLibraryItemData* itemData = new GNRTreeLibraryItemData();
		
		// set assembly
		itemData->setCat(false);
		itemData->setName(entit->getReference());
		
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
