/**
 * GNROpxExport
 * @name        GNROpxExport.cpp
 * @date        2008-11-02
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <list>

#include "GNREnum.h"
#include "GNROpxExport.h"

// ctor
GNROpxExport::GNROpxExport()
{
}

GNROpxExport::GNROpxExport(GNRScene* scene, wxString filename)
{
	// asign scene
	m_scene = scene;
	
	// create new outputstream to file
	m_outStream = new wxFFileOutputStream(filename);
	
	// create new zipoutputstream
	m_outZip = new wxZipOutputStream(m_outStream);
	
	// create OpxStream and save to FileSystem
	createOpxStream();
}

// dtor
GNROpxExport::~GNROpxExport()
{
	// do nothing
}

void GNROpxExport::createXmlEntry()
{
	// temporary string
	wxString tmp;
	
	// local list of assembly pointer
	std::list<GNRAssembly*> list;
	
	// create new empty xml document
	wxXmlDocument xml;
	
	// set xml version
	xml.SetVersion(wxT("1.0"));
	
	// set file encoding
	xml.SetFileEncoding(wxT("utf-8"));
	
	// create root, future root
	wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("opxml"));
	
	// add property "standard="oaxml.hs-ulm.de""
	root->AddProperty(wxT("standard"), wxT("oaxml.hs-ulm.de"));
	
	// add property "version="0.1.0""
	root->AddProperty(wxT("version"), wxT("0.1.0"));
	
	// add projectInformation
	root->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("projectInformation")));
	
	// node to projectInformation
	m_node = root->GetChildren();
	
	// add name + GNRProject
	m_node->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("name")));
	m_node = m_node->GetChildren();
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("name"), wxT("GNRProject")));
	
	// node to projectInformation
	m_node = m_node->GetParent();
	
	// add author + GNR
	m_node->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("author")));
	m_node = m_node->GetChildren();
	m_node = m_node->GetNext();
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("author"), wxT("GNR")));
	
	// node to projectInformation
	m_node = m_node->GetParent();
	
	// node to opxml
	m_node = m_node->GetParent();
	
	// add data
	m_node->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("data")));
	
	// node to projectInformation
	m_node = m_node->GetChildren();
	
	// node to data
	m_node = m_node->GetNext();
	
	// add camera
	m_node->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("camera")));
	
	// node to camera
	m_node = m_node->GetChildren();
	
	// add type
	m_node->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("type")));
	m_node = m_node->GetChildren();
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("type"), wxT("perspective")));
	
	// node to camera
	m_node = m_node->GetParent();
	
	// add position
	m_node->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("position")));
	
	// node to type
	m_node = m_node->GetChildren();
	
	// node to position
	m_node = m_node->GetNext();
	
	// add location
	tmp << m_scene->getGLCamera3D()->getPosition().getX() << wxT(" ") << m_scene->getGLCamera3D()->getPosition().getY() << wxT(" ") << m_scene->getGLCamera3D()->getPosition().getX();
	m_node->AddProperty(wxT("location"), tmp);
	tmp.Empty();
	
	// add orientation
	tmp << m_scene->getGLCamera3D()->getRotatedX() << wxT(" ") << m_scene->getGLCamera3D()->getRotatedY() << wxT(" ") << m_scene->getGLCamera3D()->getRotatedZ();
	m_node->AddProperty(wxT("orientation"), tmp);
	tmp.Empty();
	
	// node to camera
	m_node = m_node->GetParent();
	
	// node to data
	m_node = m_node->GetParent();
	
	// add lightsources
	m_node->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("lightsources")));
	
	// add scene
	m_node->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("scene")));
	
	// node to camera
	m_node = m_node->GetChildren();
	
	// node to lightsources
	m_node = m_node->GetNext();
	
	// node to scene
	m_node = m_node->GetNext();
	
	// get partlist of rootassembly
	list = m_scene->getRootAssembly()->getPartList();
	
	// create scene, add groups and assemblies
	createScene(m_node, list);
	
	// set root
	xml.SetRoot(root);
	
	// create new entry
	m_outZip->PutNextEntry(wxT("content.xml"));
	
	// save xml document to zipstream
	xml.Save(*m_outZip);
	
	// close entry
	m_outZip->CloseEntry();
	
	// detach root
	root = xml.DetachRoot();
	
	// data copied to file, root can be deleted
	delete root;
}

void GNROpxExport::createOpxStream()
{
	// wxZipEntry pointer
	wxZipEntry* entry;
	
	// create new xml entry
	createXmlEntry();
	
	// wxFFileInputStream to read lib
	wxFFileInputStream inFile((wxFileName::GetCwd() + wxFileName::GetPathSeparator() + wxT("library.gnr")));
	
	// wxZipInputStream
	wxZipInputStream inZip(inFile);
	
	// vector to store entries
	std::vector<wxZipEntry*> vec;
	
	// vector iterator
	std::vector<wxZipEntry*>::iterator vecIt;
	
	// set iterator
	std::set<wxString>::iterator it;
	
	// get first entry
	entry = inZip.GetNextEntry();
	
	// store all entries
	while (entry)
	{
		// store into vector
		vec.push_back(entry);
		
		// get next entry
		entry = inZip.GetNextEntry();
	}
	
	for (it = m_set.begin(); it != m_set.end(); it++)
	{
		for (vecIt = vec.begin(); vecIt != vec.end(); vecIt++)
		{
			if ((*it) == (*vecIt)->GetName())
			{
				// asign entry
				entry = *vecIt;
				
				// set name
				entry->SetName(wxT("assemblies") + wxFileName::GetPathSeparators() + entry->GetName());
				
				// copy data
				m_outZip->CopyEntry(entry, inZip);
				
				// entry found, leave
				break;
			}
		}
	}
	
	// close zip file
	m_outZip->Close();
}

void GNROpxExport::createScene(wxXmlNode* node, std::list<GNRAssembly*> list)
{
	// iterator
	std::list<GNRAssembly*>::iterator it;
	
	// walk through part list
	for (it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->getType() == IS_OBJECT || (*it)->getType()== IS_PRIMITIVE)
		{
			// create an assembly entry and add into node
			createAssembly(node, (*it));
			
			// insert hash into set
			m_set.insert((*it)->getHash() + wxT(".oax"));
			
			// assemby found
			continue;
		}
		
		if ((*it)->getType() == IS_GROUP)
		{
			// create an group and add into node
			createGroup(node, (*it));
			
			// group found
			continue;
		}
	}
}

void GNROpxExport::createAssembly(wxXmlNode* node, GNRAssembly* assembly)
{
	// temporary string
	wxString tmp;
	
	// add child
	node->InsertChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("assembly")), NULL);
	
	// not to new child
	node = node->GetChildren();
	
	if (assembly->isVisible())
	{
		// add hidden
		node->AddProperty(wxT("visible"), wxT("true"));
	}
	else
	{
		// add visible
		node->AddProperty(wxT("visible"), wxT("false"));
	}
	
	// add name
	node->AddProperty(wxT("name"), assembly->getName());
	
	// add location
	tmp << assembly->getX() << wxT(" ") << assembly->getY() << wxT(" ") << assembly->getZ();
	node->AddProperty(wxT("location"), tmp);
	tmp.Empty();
	
	// add orientation
	tmp << assembly->getPhi() << wxT(" ") << assembly->getTheta() << wxT(" ") << assembly->getRho();
	node->AddProperty(wxT("orientation"), tmp);
	tmp.Empty();
	
	// add ref
	node->AddProperty(wxT("ref"), (assembly->getHash() + wxT(".oax")));
	
	// node to scene
	node = node->GetParent();
}

void GNROpxExport::createGroup(wxXmlNode* node, GNRAssembly* assembly)
{
	// temporary string
	wxString tmp;
	
	// local list
	std::list<GNRAssembly*> list = assembly->getPartList();
	
	// iterator
	std::list<GNRAssembly*>::iterator it;
	
	// add group
	node->InsertChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("group")), NULL);
	
	// node to new child
	node = node->GetChildren();
	
	if (assembly->isVisible())
	{
		// add hidden
		node->AddProperty(wxT("visible"), wxT("true"));
	}
	else
	{
		// add visible
		node->AddProperty(wxT("visible"), wxT("false"));
	}
	// add name
	node->AddProperty(wxT("name"), assembly->getName());
	
	// add location
	tmp << assembly->getX() << wxT(" ") << assembly->getY() << wxT(" ") << assembly->getZ();
	node->AddProperty(wxT("location"), tmp);
	tmp.Empty();
	
	// add orientation
	tmp << assembly->getPhi() << wxT(" ") << assembly->getTheta() << wxT(" ") << assembly->getRho();
	node->AddProperty(wxT("orientation"), tmp);
	tmp.Empty();
	
	// walk through part list
	for (it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->getType() == IS_OBJECT || (*it)->getType()== IS_PRIMITIVE)
		{
			// create an assembly entry and add into node
			createAssembly(node, (*it));
			
			// assemby found
			continue;
		}
		
		if ((*it)->getType() == IS_GROUP)
		{
			// create an group and add into node
			createGroup(node, (*it));
			
			// group found
			continue;
		}
	}
	
	// node to parent
	node = node->GetParent();
}
