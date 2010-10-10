/**
 * OpxExport
 * @name        OpxExport.cpp
 * @date        2008-11-02
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <list>
#include <wx/msgdlg.h>

#include "Assembly.h"
#include "GLCamera.h"
#include "md5.h"
#include "OpxExport.h"
#include "Scene.h"

// ctor
OpxExport::OpxExport()
{
}

OpxExport::OpxExport(Scene* scene, wxString filename)
{
	// asign scene
	m_scene = scene;

	// no primitives at beginning
	m_incPrim = false;

	// create new outputstream to file
	m_outStream = new wxFFileOutputStream(filename);

	// create new zipoutputstream
	m_outZip = new wxZipOutputStream(m_outStream);

	// create OpxStream and save to FileSystem
	createOpxStream();

	// inform user about successful saving
	wxMessageBox(wxT("Die Datei '") + filename.AfterLast(wxFileName::GetPathSeparator()) + wxT("' wurde erfolgreich gespeichert!"),wxT("Speichern erfolgreich..."),wxOK);
}

// dtor
OpxExport::~OpxExport()
{
}

void OpxExport::createXmlEntry()
{
	// temporary string
	wxString tmp;

	// local list of assembly pointer
	std::list<Assembly*> list;

	// create new empty xml document
	wxXmlDocument xml;

	// set xml version
	xml.SetVersion(wxT("1.0"));

	// set file encoding
	xml.SetFileEncoding(wxT("utf-8"));

	// create root, future root
	wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("opxml"));

	// add property "standard="oaxml.hs-ulm.de""
	root->AddProperty(wxT("standard"), wxT("opxml.hs-ulm.de"));

	// add property "version="0.1.0""
	root->AddProperty(wxT("version"), wxT("0.1.0"));

	// add projectInformation
	root->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("projectInformation")));

	// node to projectInformation
	m_node = root->GetChildren();

	// add name + Project
	m_node->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("name")));
	m_node = m_node->GetChildren();
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("name"), wxT("Project")));

	// node to projectInformation
	m_node = m_node->GetParent();

	// add author +
	m_node->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("author")));
	m_node = m_node->GetChildren();
	m_node = m_node->GetNext();
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("author"), wxT("")));

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
	tmp << m_scene->getGLCamera3D()->getPosition().getX() << wxT(" ");
	tmp << m_scene->getGLCamera3D()->getPosition().getY() << wxT(" ");
	tmp << m_scene->getGLCamera3D()->getPosition().getZ();
	m_node->AddProperty(wxT("location"), tmp);
	tmp.Empty();

	// add orientation
	tmp << m_scene->getGLCamera3D()->getRotatedX() << wxT(" ");
	tmp << m_scene->getGLCamera3D()->getRotatedY() << wxT(" ");
	tmp << m_scene->getGLCamera3D()->getRotatedZ();
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

void OpxExport::createOpxStream()
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

	if (m_incPrim)
	{
		// list iterator
		std::map<wxString, wxMemoryOutputStream*>::iterator itm;

		for (itm = m_primitives.begin(); itm != m_primitives.end(); itm++)
		{
			// add to opx container
			m_outZip->PutNextEntry(wxT("assemblies/") + itm->first + wxT(".oax"));

			// wxMemoryOutputStream pointer
			wxMemoryOutputStream* memOut = itm->second;

			// wxMemoryInputStream
			wxMemoryInputStream inMem(*memOut);

			// copy data
			inMem.Read(*m_outZip);
		}
	}

	// close zip file
	m_outZip->Close();

	// close out stream
	m_outStream->Close();
}

void OpxExport::createScene(wxXmlNode* node, std::list<Assembly*> list)
{
	// iterator
	std::list<Assembly*>::iterator it;

	// walk through part list
	for (it = list.begin(); it != list.end(); it++)
	{
		switch ((int)(*it)->getType())
		{
		case IS_GROUP:

			// create an group and add into node
			createGroup(node, (*it));

			break;
		case IS_OBJECT:

			// create an assembly entry and add into node
			createAssembly(node, (*it));

			break;
		case IS_PRIMITIVE:

			// create primitives and wrote into opx
			createPrimitive(node, (*it));

			//we can use primitiveType getPrimitiveType() to ask assembly for type!!!

			break;
		}
	}
}

void OpxExport::createAssembly(wxXmlNode* node, Assembly* assembly)
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
	tmp << assembly->position().getX() << wxT(" ") << assembly->position().getY() << wxT(" ") << assembly->position().getZ();
	node->AddProperty(wxT("location"), tmp);
	tmp.Empty();

	// add orientation
	tmp << assembly->rotation().getX() << wxT(" ") << assembly->rotation().getY() << wxT(" ") << assembly->rotation().getZ();
	node->AddProperty(wxT("orientation"), tmp);
	tmp.Empty();

	// add ref
	node->AddProperty(wxT("ref"), (wxT("assemblies/") + assembly->getHash() + wxT(".oax")));

	// node to scene
	node = node->GetParent();

	// insert hash into set
	m_set.insert(assembly->getHash() + wxT(".oax"));
}

void OpxExport::createGroup(wxXmlNode* node, Assembly* assembly)
{
	// temporary string
	wxString tmp;

	// local list
	std::list<Assembly*> list = assembly->getPartList();

	// if group is empty, do not export
	if (list.size() == 0)
	{
		return;
	}

	// iterator
	std::list<Assembly*>::iterator it;

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
	tmp << assembly->position().getX() << wxT(" ") << assembly->position().getY() << wxT(" ") << assembly->position().getZ();
	node->AddProperty(wxT("location"), tmp);
	tmp.Empty();

	// add orientation
	tmp << assembly->rotation().getX() << wxT(" ") << assembly->rotation().getY() << wxT(" ") << assembly->rotation().getZ();
	node->AddProperty(wxT("orientation"), tmp);
	tmp.Empty();

	// walk through part list
	for (it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->getType() == IS_OBJECT)
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

		if ((*it)->getType() == IS_PRIMITIVE)
		{
			// create a primitive and add into node
			createPrimitive(node, (*it));

			// primitive found
			continue;
		}
	}

	// node to parent
	node = node->GetParent();
}

void OpxExport::createPrimitive(wxXmlNode* node, Assembly* assembly)
{
	// set with primitives
	m_incPrim = true;

	// temporary attributes
	float x, y, z;

	// create primitive oax
	// memory output stream
	wxMemoryOutputStream* memOut = new wxMemoryOutputStream();

	// wxZipoutputstream
	wxZipOutputStream outZip(*memOut);

	// new primitive oax
	wxXmlDocument xml;

	// set xml version
	xml.SetVersion(wxT("1.0"));

	// set file encoding
	xml.SetFileEncoding(wxT("utf-8"));

	// create root, future root
	wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("oaxml"));

	// add property "standard="oaxml.hs-ulm.de""
	root->AddProperty(wxT("standard"), wxT("oaxml.hs-ulm.de"));

	// add property "version="0.1.0""
	root->AddProperty(wxT("version"), wxT("0.1.0"));

	// set actual as root
	m_actual = root;

	// add assemblyInformation
	m_actual->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("assemblyInformation")));

	// m_actual to assemblyInformation
	m_actual = m_actual->GetChildren();

	// add name
	m_actual->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("name")));

	// node to new child
	m_node = m_actual->GetChildren();

	// add value
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("name"), wxT("")));

	// add author
	m_actual->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("author")));

	// node to new child
	m_node = m_actual->GetChildren();

	// node to author
	m_node = m_node->GetNext();

	// add value
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("author"), wxT("")));

	// add tags
	m_actual->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("tags")));

	// m_actual to oaxml
	m_actual = m_actual->GetParent();

	// add data
	m_actual->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("data")));

	// m_actual to assemblyInformation
	m_actual = m_actual->GetChildren();

	// m_actual to data
	m_actual = m_actual->GetNext();

	// switch between primitives
	switch (assembly->getPrimitiveType())
	{
	case CUBOID:
		m_actual->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("cuboid")));
		break;
	}

	// m_actual to new child
	m_actual = m_actual->GetChildren();

	// add visible
	m_actual->AddProperty(wxT("visible"), wxT("true"));

	// add locationOffset
	m_actual->AddProperty(wxT("locationOffset"), wxT("0 0 0"));

	// add orientationOffset
	m_actual->AddProperty(wxT("orientationOffset"), wxT("0 0 0"));

	// get width, height, depth
	assembly->world_dimension().getAll(x, y, z);

	// add child
	m_actual->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("width")));

	// node to new child
	m_node = m_actual->GetChildren();

	// add width
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("width"), wxString() << x));

	// add child
	m_actual->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("height")));

	// node to new child
	m_node = m_actual->GetChildren();

	// node to height
	m_node = m_node->GetNext();

	// add height
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("height"), wxString() << y));

	// add child
	m_actual->AddChild(new wxXmlNode(wxXML_ELEMENT_NODE, wxT("depth")));

	// node to new child
	m_node = m_actual->GetChildren();

	// node to height
	m_node = m_node->GetNext();

	// node to depth
	m_node = m_node->GetNext();

	// add height
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("depth"), wxString() << z));

	// set root
	xml.SetRoot(root);

	// string to store md5
	wxString xmlHash;

	// get xml content
	wxStringOutputStream strOut(&xmlHash);

	// save into string
	xml.Save(strOut);

	// calc md5
	xmlHash = MD5wxString(xmlHash);

	// create new entry
	outZip.PutNextEntry(wxT("content.xml"));

	// save xml document to zipstream
	xml.Save(outZip);

	// close entry
	outZip.CloseEntry();

	// add mem to list
	m_primitives.insert(std::pair<wxString, wxMemoryOutputStream*>(xmlHash + xmlHash, memOut));

	// create opx content.xml entry
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

	// get location
	assembly->position().getAll(x, y, z);

	// add location
	node->AddProperty(wxT("location"), wxString() << x << wxT(" ") << y << wxT(" ") << z);

	// get orientation
	assembly->rotation().getAll(x, y, z);

	// add orientation
	node->AddProperty(wxT("orientation"), wxString() << x << wxT(" ") << y << wxT(" ") << z);

	// add ref
	node->AddProperty(wxT("ref"), (wxT("assemblies/") + xmlHash + xmlHash + wxT(".oax")));

	// node to scene
	node = node->GetParent();
}
