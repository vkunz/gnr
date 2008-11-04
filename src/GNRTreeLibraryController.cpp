/**
 * GNRTreeLibraryController
 * @name        GNRTreeLibraryController.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/bitmap.h>
#include <wx/filename.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/msgdlg.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>

#include "GNRTreeLibraryController.h"

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
	
	// open library.xml and store its data
	openLibrary();
	
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
	
	// walk through all categories and store string into vector
	for (m_categoryit = m_category.begin(); m_categoryit != m_category.end(); m_categoryit++)
	{
		ptrCat->push_back(m_categoryit->getName());
	}
	
	return ptrCat;
}

void GNRTreeLibraryController::createEmptyLibrary()
{
	// new filename
	wxFileName file(wxFileName::GetCwd() + wxFileName::GetPathSeparator() + wxT("data") + wxFileName::GetPathSeparator() + wxT("library.gnr"));
	
	// create outputstream
	wxFFileOutputStream outFile(file.GetFullPath());
	
	// create zipoutputstream
	wxZipOutputStream outZip(outFile);
	
	// create new empty xml document
	wxXmlDocument xml;
	
	// set xml version
	xml.SetVersion(wxT("1.0"));
	
	// set file encoding
	xml.SetFileEncoding(wxT("utf-8"));
	
	// create root
	wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("gnr"));
	
	// set root
	xml.SetRoot(root);
	
	// create entries
	wxXmlNode* node = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxT("entries"));
	
	// create categoreis
	node = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxT("categories"));
	
	// new zipEntry
	outZip.PutNextEntry(wxT("library.xml"));
	
	// copy data into entry
	xml.Save(outZip);
	
	// close entry
	outZip.CloseEntry();
	
	// close zipStream
	outZip.Close();
	
	// close file
	outFile.Close();
}

unsigned int GNRTreeLibraryController::getParentId(wxString name)
{
	// tmp int
	unsigned int parentId;
	
	// walk through all entrys, look for name
	for (m_categoryit = m_category.begin(); m_categoryit != m_category.end(); m_categoryit++)
	{
		if (m_categoryit->getName() == name)
		{
			parentId = m_categoryit->getParentId();
		}
	}
	
	return parentId;
}

/**
 * Open library.xml if exist and get all its data.
 */
void GNRTreeLibraryController::openLibrary()
{
	// string to store groupname
	wxString Name;
	
	// integer to store groupId
	unsigned int groupId;
	
	// create pointer to xmlnode
	wxXmlNode* node;
	
	// create pointer to xmlproperty
	wxXmlProperty* prop;
	
	// new filename
	wxFileName file(wxFileName::GetCwd() + wxFileName::GetPathSeparator() + wxT("data") + wxFileName::GetPathSeparator() + wxT("library.gnr"));
	
	// check if file exist
	
	if (!wxFileExists(file.GetFullPath()))
	{
		// create new empty library
		createEmptyLibrary();
	}
	
	// get library.gnr as FileInputStream
	m_inFile = new wxFFileInputStream(file.GetFullPath());
	
	// get inFile as wxZipInputStream
	m_inZip = new wxZipInputStream(*m_inFile);
	
	// m_zipEntry to first entry
	m_zipEntry = m_inZip->GetNextEntry();
	
	// walk through all entrys and look for an xml file
	while (m_zipEntry)
	{
		// lookfor *.xml
		if (m_zipEntry->GetName().Matches(wxT("*.xml")));
		{
			// load xml
			LoadXml();
			
			//entry found
			break;
		}
		
		// get next Entry
		m_zipEntry = m_inZip->GetNextEntry();
	}
}

void GNRTreeLibraryController::addCategory(wxString& name, unsigned int& categoryId, unsigned int& parentId)
{
	m_category.push_back(GNRLibraryCategory(name, categoryId, parentId));
}

void GNRTreeLibraryController::addCategory(wxString& name)
{
	m_category.push_back(GNRLibraryCategory(name, m_category.size() + 1, 0));
}

void GNRTreeLibraryController::addEntry(wxString& name, wxString& reference, wxString& categoryname, wxInputStream& instream)
{

}

void GNRTreeLibraryController::addEntry(wxString& name, wxString& reference, unsigned int& categoryId)
{
	m_entries.push_back(GNRLibraryEntry(name, reference, categoryId));
}

void GNRTreeLibraryController::LoadXml()
{
	// store name
	wxString name;
	
	// store reference
	wxString reference;
	
	// store id
	unsigned int categoryId;
	
	
	// open m_zipEntry
	m_inZip->OpenEntry(*m_zipEntry);
	
	// create xml document of m_inZip
	wxXmlDocument xml(*m_inZip);
	
	// create pointer to node
	wxXmlNode* node;
	
	// create pointer to prop
	wxXmlProperty* prop;
	
	// node to root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	if (node->GetChildren() != NULL)
	{
		// node to first category
		node = node->GetChildren();
		
		// set parentId to 0
		m_parentId = 0;
		
		// walk through all next nodes
		while (node)
		{
			// walk through all children
			while (node)
			{
				// prop to name
				prop = node->GetProperties();
				
				// get value of name
				name = prop->GetValue();
				
				// prop to categoryid
				prop = prop->GetNext();
				
				// get value of categoryId
				categoryId = wxAtoi(prop->GetValue());
				
				// add new category
				addCategory(name, categoryId, m_parentId);
				
				// check if there are children
				if (node->GetChildren() != NULL)
				{
					// set new parentId
					m_parentId = categoryId;
					
					// set to next children
					node = node->GetChildren();
				}
				
				// another children
				else if (node->GetNext() != NULL)
				{
					// node to next
					node = node->GetNext();
				}
				// no children anymore
				else
				{
					// set node to parent
					node = node->GetParent();
					
					// check if categories
					if (node->GetProperties())
					{
						// get first property
						prop = node->GetProperties();
						
						// get value
						name = prop->GetValue();
						
						// get parentId
						m_parentId = getParentId(name);
					}
					// if not possible, parent => 0
					else
					{
						m_parentId = 0;
					}
					
					// leave loop
					break;
				}
			}
			
			// check if next exist
			if (node->GetNext() != NULL)
			{
				// exist, set node to next
				node = node->GetNext();
				
				// check if finisched with categories
				if (node->GetName() == wxT("entries"))
				{
					// leave loop
					break;
				}
			}
			// next does not exist
			else
			{
				// set node to parent
				node = node->GetParent();
				
				// get first property
				prop = node->GetProperties();
				
				// get value
				name = prop->GetValue();
				
				// get parentId
				m_parentId = getParentId(name);
				
				// set node to next
				node = node->GetNext();
			}
		}
	}
	
	// node to first entry
	node = node->GetChildren();
	
	// walk through all entries
	while (node)
	{
		// prop to name
		prop = node->GetProperties();
		
		// get name
		name = prop->GetValue();
		
		// prop to reference
		prop = prop->GetNext();
		
		// get reference
		reference = prop->GetValue();
		
		// prop to categoryid
		prop = prop->GetNext();
		
		// get categoryid
		categoryId = wxAtoi(prop->GetValue());
		
		// add new entry
		addEntry(name, reference, categoryId);
		
		// check if next node exist
		if (node->GetNext())
		{
			// everything ok, next exist
			node = node->GetNext();
		}
		// no next node
		else
		{
			// no next node, jump out
			break;
		}
	}
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
	
	// local wxTreeItemId
	wxTreeItemId tiid;
	
	// set root
	tiid = m_treeCtrl->AddRoot(wxT("GNRBibliothek"));
	
	// store root tiid
	groups.insert(std::pair<unsigned int, wxTreeItemId>(0, tiid));
	
	// walk through all groups and append to tree control
	for (m_categoryit = m_category.begin(); m_categoryit != m_category.end(); m_categoryit++)
	{
		// append to treectrl
		tiid = m_treeCtrl->AppendItem(groups[m_categoryit->getParentId()], m_categoryit->getName());
		
		// set image
		m_treeCtrl->SetItemImage(tiid, (int)TreeCtrlIcon_Folder);
		
		// store tiid into map
		groups.insert(std::pair<unsigned int, wxTreeItemId>(m_categoryit->getCategoryId(), tiid));
	}
	
	// walk through all entrys and append to tree control
	for (m_entriesit = m_entries.begin(); m_entriesit != m_entries.end(); m_entriesit++)
	{
		// append to treectrl
		tiid = m_treeCtrl->AppendItem(groups[m_entriesit->getCategoryId()], m_entriesit->getName());
		
		// set image
		m_treeCtrl->SetItemImage(tiid, (int)TreeCtrlIcon_Assembly);
		
		// store tiid into map
		//entries.insert(std::pari<unsigned int, wxTreeItemId>(
	}
}
