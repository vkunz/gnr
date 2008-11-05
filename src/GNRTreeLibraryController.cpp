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

#include "GNRTreeLibraryController.h"
#include "md5.h"

#include "resources/icon_library_folder.xpm"
#include "resources/icon_library_assembly.xpm"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * Constructor.
 * @param       wxTreeCtrl*     Assigns pointer to wxTreeCtrl.
 */
GNRTreeLibraryController::GNRTreeLibraryController(wxTreeCtrl* treectrl)
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
	// do nothing
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

void GNRTreeLibraryController::addEntry(wxString& name, wxString& categoryname, wxInputStream& instream)
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
}

unsigned int GNRTreeLibraryController::addCategory(wxString& name)
{
	// check if already exist
	m_newCat = true;
	
	unsigned int ret;
	
	// iterator
	std::vector<GNRLibraryCategory>::iterator it;
	
	for (it = m_ptrCategories->begin(); it != m_ptrCategories->end(); it++)
	{
		if (it->getName() == name)
		{
			// set ret
			ret = it->getCategoryId();
			
			// set found
			m_newCat = false;
		}
	}
	
	// not found, create new one
	if (m_newCat)
	{
		m_ptrCategories->push_back(GNRLibraryCategory(name, m_ptrCategories->size() + 1, 0));
		
		ret = (m_ptrCategories->size());
	}
	
	return ret;
}

void GNRTreeLibraryController::createImageList(int size)
{
	// Make an image list containing small icons
	wxImageList *images = new wxImageList(size, size, true);
	
	// should correspond to TreeCtrlIcon_xxx enum
	wxBusyCursor wait;
	
	// 2 icons
	wxIcon icons[2];
	icons[0] = wxIcon(icon_library_folder_xpm);
	icons[1] = wxIcon(icon_library_assembly_xpm);
	
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
	std::map<unsigned int, wxTreeItemId> groups;
	
	// local map to store entryid and wxTreeItemid
	std::map<unsigned int, wxTreeItemId> entries;
	
	// cat iterator
	std::vector<GNRLibraryCategory>::iterator catit;
	
	// ent iterator
	std::vector<GNRLibraryEntry>::iterator entit;
	
	// groups iterator
	std::map<unsigned int, wxTreeItemId>::iterator groit;
	
	// local wxTreeItemId
	wxTreeItemId tiid;
	wxTreeItemId root;
	
	// set root
	root = tiid = m_treeCtrl->AddRoot(wxT("GNRBibliothek"));
	
	// store root tiid
	groups.insert(std::pair<unsigned int, wxTreeItemId>(0, tiid));
	
	// walk through all groups and append to tree control
	for (catit = m_ptrCategories->begin(); catit != m_ptrCategories->end(); catit++)
	{
		// append to treectrl
		tiid = m_treeCtrl->AppendItem(groups[catit->getParentId()], catit->getName());
		
		// set image
		m_treeCtrl->SetItemImage(tiid, (int)TreeCtrlIcon_Folder);
		
		// store tiid into map
		groups.insert(std::pair<unsigned int, wxTreeItemId>(catit->getCategoryId(), tiid));
	}
	
	// walk through all entrys and append to tree control
	for (entit = m_ptrEntries->begin(); entit != m_ptrEntries->end(); entit++)
	{
		// append to treectrl
		tiid = m_treeCtrl->AppendItem(groups[entit->getCategoryId()], entit->getName());
		
		// set image
		m_treeCtrl->SetItemImage(tiid, (int)TreeCtrlIcon_Assembly);
		
		// store tiid into map
		//entries.insert(std::pari<unsigned int, wxTreeItemId>(
	}
	
	// sort
	for (groit = groups.begin(); groit != groups.end(); groit++)
	{
		m_treeCtrl->SortChildren(groit->second);
	}
	
	// expand root
	m_treeCtrl->Expand(root);
}
