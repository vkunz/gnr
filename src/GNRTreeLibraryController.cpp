/**
 * GNRTreeLibraryController
 * @name        GNRTreeLibraryController.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/wfstream.h>
#include <wx/xml/xml.h>

#include "GNRTreeLibraryController.h"

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
	for (m_groupsit = m_groups.begin(); m_groupsit != m_groups.end(); m_groupsit++)
	{
		ptrCat->push_back(m_groupsit->first);
	}
	
	return ptrCat;
}

/**
 * Open library.xml if exist and get all its data.
 */
void GNRTreeLibraryController::openLibrary()
{
	// string to store groupname
	wxString Name;
	
	// integer to store groupId
	unsigned long int groupId;
	
	// create pointer to xmlnode
	wxXmlNode* node;
	
	// create pointer to xmlproperty
	wxXmlProperty* prop;
	
	// get library.xml as FileInputStream
	wxFFileInputStream inFile(wxT("library.xml"));
	
	// create xmldocument of inpustream
	wxXmlDocument xml(inFile);
	
	// node to groups
	node = xml.GetRoot()->GetChildren();
	
	// node to first group
	node = node->GetChildren();
	
	// walk through all group-tags
	while (node)
	{
		// set prop to first propertie of actual node
		prop = node->GetProperties();
		
		// get name of prop
		Name = prop->GetValue();
		
		// get groupid of prop
		prop->GetValue().ToULong(&groupId);
		
		// stores data into map
		m_groups.insert(std::pair<wxString, unsigned long int>(Name, groupId));
		
		// check if next exist, if not, leave
		if (node->GetNext() == NULL)
		{
			break;
		}
		// everything ok, set next node
		else
		{
			// set node to next group
			node = node->GetNext();
		}
	}
	
	// node to groups
	node = node->GetParent();
	
	// node to entries
	node = node->GetChildren();
	
	// walk through all group-tags
	while (node)
	{
		// set prop to first propertie of actual node
		prop = node->GetProperties();
		
		// get ref of prop
		Name = prop->GetValue();
		
		// get groupid of prop
		prop->GetValue().ToULong(&groupId);
		
		// stores data into map
		m_entries.insert(std::pair<wxString, unsigned long int>(Name, groupId));
		
		// check if there is no next node, leave
		if (node->GetNext() == NULL)
		{
			break;
		}
		// everything ok, set next node
		else
		{
			// set node to next group
			node = node->GetNext();
		}
	}
}

/**
 * Build TreeControll on actual data.
 */
void GNRTreeLibraryController::buildTreeCtrl()
{
	// set root
	wxTreeItemId tiid = m_treeCtrl->AddRoot(wxT("GNRBibliothek"));
	
	// walk through all groups and append to root
	for (m_groupsit = m_groups.begin(); m_groupsit != m_groups.end(); m_groupsit++)
	{
		m_treeCtrl->AppendItem(tiid, m_groupsit->first);
	}
}
