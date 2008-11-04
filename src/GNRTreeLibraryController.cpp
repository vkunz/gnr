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
	m_library->addEntry(instream);
	
//
//    // create new outputzip
//    wxZipOutputStream tmpout(outzip);
//
//    // copy all meta data
//    tmpout.CopyArchiveMetaData();
//
//    // entry to first entry
//    entry = inZip.GetNextEntry();
//
//    while(entry)
//    {
//        tmpout.CopyEntry(entry, inZip);
//
//        entry = inZip.GetNextEntry();
//    }
//
//    //add entry
//    outzip.PutNextEntry(objhash + xmlhash + wxT(".oax"));
//
//    // close outzip entry
//    outzip.CloseEntry();
//
//    // reset inFile
//    inFile.reset();
//
//    // close outzip
//    outzip.Close();
//
//    // commit tmp file
//    outFile.Commit();
}

void GNRTreeLibraryController::addCategory(wxString& name)
{
	m_ptrCategories->push_back(GNRLibraryCategory(name, m_ptrCategories->size() + 1, 0));
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
	// local map to store categoryid and wxTreeItemId
	std::map<unsigned int, wxTreeItemId> groups;
	
	// local map to store entryid and wxTreeItemid
	std::map<unsigned int, wxTreeItemId> entries;
	
	// cat iterator
	std::vector<GNRLibraryCategory>::iterator catit;
	
	// ent iterator
	std::vector<GNRLibraryEntry>::iterator entit;
	
	// local wxTreeItemId
	wxTreeItemId tiid;
	
	// set root
	tiid = m_treeCtrl->AddRoot(wxT("GNRBibliothek"));
	
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
}
