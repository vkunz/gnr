/**
 * GNROpxImport
 * @name        GNROpxImport.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/mstream.h>
#include <wx/string.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>

#include "GNROpxImport.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * Default Constructor.
 */
GNROpxImport::GNROpxImport()
{
}

/**
 * Loads the given filename. See Load(wxString filename).
 * @param       wxString        Filepath to read from.
 * @param       GNRScene*       Assigns pointer to actual scene.
 */
GNROpxImport::GNROpxImport(GNRTreeLibraryController* controller, GNRScene* scene, wxString filename)
{
	// assign librarycontroller
	m_libctrl = controller;
	
	// set GNRScene pointer
	m_camera = scene->getGLCamera3D();
	
	// asign scene
	m_scene = scene;
	
	// store filename
	m_filename = filename;
	
	// create stream of filename
	wxFFileInputStream inFile(filename);
	
	// create zipstream
	wxZipInputStream stream(inFile);
	
	// load
	Load(stream);
}

/**
 * Virtual Destructor.
 */
GNROpxImport::~GNROpxImport()
{
}

/**
 * Loads the given file and get all its data.
 * @param       wxString    Filepath to read from.
 */
void GNROpxImport::Load(wxZipInputStream& stream)
{
	// wxZipEntry pointer
	wxZipEntry* entry;
	
	// iterator
	std::vector<wxZipEntry*>::iterator it;
	
	// get first entry
	entry = stream.GetNextEntry();
	
	// walk through all entrys and push them into vector
	while (entry)
	{
		// push pointer to vector
		m_vector.push_back(entry);
		
		// get next Entry
		entry = stream.GetNextEntry();
	}
	
	// walk through all vector-entrys, find *.xml
	for (it = m_vector.begin(); it != m_vector.end(); it++)
	{
		// assign entry
		entry = *it;
		
		// search entryname matches "*.xml"
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			// openEntry
			stream.OpenEntry(*entry);
			
			// load xmlstream
			loadXml(stream);
			
			// entry found
			continue;
		}
	}
	
	// refresh
	m_scene->refreshTreeAndCanvas();
}

/**
 * Loads the given stream and get its all data.
 * @param       wxInputStream    Load xml-File as wxInputStream.
 */
void GNROpxImport::loadXml(wxZipInputStream& stream)
{
	// temporary attributes
	double x, y, z;
	bool isVisible;
	
	// xml node pointer
	wxXmlNode* node;
	
	// xml property pointer
	wxXmlProperty* prop;
	
	// create wxString to store propertyvalues
	wxString value;
	
	// temporary attribute tokenizer
	wxStringTokenizer tok;
	
	// create xmldocument of inpustream
	wxXmlDocument xml(stream);
	
	// node to root
	node = xml.GetRoot();
	
	// node to assemblyInformation
	node = node->GetChildren();
	
	// node to name
	node = node->GetChildren();
	
	// get name
	m_name = node->GetNodeContent();
	
	// node to author
	node = node->GetNext();
	
	// get author
	m_author = node->GetNodeContent();
	
	// node to projectInformation
	node = node->GetParent();
	
	// node to data
	node = node->GetNext();
	
	// node to camera
	node = node->GetChildren();
	
	// node to type
	node = node->GetChildren();
	
	// node to position
	node = node->GetNext();
	
	// prop to location
	prop = node->GetProperties();
	
	// get value of location
	value = prop->GetValue();
	
	// tokenize value
	tok.SetString(value, wxT(" "));
	
	// get camera x-position
	tok.GetNextToken().ToDouble(&x);
	
	// get camera y-position
	tok.GetNextToken().ToDouble(&y);
	
	// get camera z-position
	tok.GetNextToken().ToDouble(&z);
	
	// set camera position
	m_camera->setPosition(x, y, z);
	
	// prop to orientation
	prop = prop->GetNext();
	
	// get value of orientation
	value = prop->GetValue();
	
	// tokenize value
	tok.SetString(value, wxT(" "));
	
	// get camera x-orientation
	tok.GetNextToken().ToDouble(&x);
	
	// get camera y-orientation
	tok.GetNextToken().ToDouble(&y);
	
	// get camera z-orientation
	tok.GetNextToken().ToDouble(&z);
	
	// set camera orientation
	m_camera->setAngles(x, y, z);
	
	// node to camera
	node = node->GetParent();
	
	// node to lightsources
	node = node->GetNext();
	
	// node to scene
	node = node->GetNext();
	
	if (node->GetChildren() != NULL)
	{
		// node to first scene-object
		node = node->GetChildren();
		
		// set m_actual to m_scene->rootAssembly
		m_actual = m_scene->getRootAssembly();
		
		// walk through all next nodes
		while (node)
		{
			if (node->GetName() == wxT("Gruppe"))
			{
				// get visible
				prop = node->GetProperties();
				
				// get value of visible
				value = prop->GetValue();
				
				// check if visible or not
				if (value == wxT("true"))
				{
					// set true
					isVisible = true;
				}
				else
				{
					// set false
					isVisible = false;
				}
				
				// prop to name
				prop = prop->GetNext();
				
				// get value of name
				value = prop->GetValue();
				
				// new group
				GNRAssembly* newGroup = new GNRAssembly(value);
				
				// set group
				newGroup->setType(IS_GROUP);
				
				// set visible
				newGroup->setVisible(isVisible);
				
				// prop to location
				prop = prop->GetNext();
				
				// get value of location
				value = prop->GetValue();
				
				// tokenize value
				tok.SetString(value, wxT(" "));
				
				// set x
				newGroup->setX(wxAtof(tok.GetNextToken()));
				
				// set y
				newGroup->setY(wxAtof(tok.GetNextToken()));
				
				// set z
				newGroup->setZ(wxAtof(tok.GetNextToken()));
				
				// prop to orientation
				prop = prop->GetNext();
				
				// get value of orientation
				value = prop->GetValue();
				
				// tokenize value
				tok.SetString(value, wxT(" "));
				
				// set phi
				newGroup->setPhi(wxAtof(tok.GetNextToken()));
				
				// set theta
				newGroup->setTheta(wxAtof(tok.GetNextToken()));
				
				// set rho
				newGroup->setRho(wxAtof(tok.GetNextToken()));
				
				// add new Assembly
				m_actual->addPart(newGroup);
				
				// set m_actual to new Group
				m_actual = newGroup;
				
				// get children
				node = node->GetChildren();
				
				// found group, begin loop again
				continue;
			}
			else
			{
				// prop to visible
				prop = node->GetProperties();
				
				// get value of visible
				value = prop->GetValue();
				
				// check if visible or not
				if (value == wxT("true"))
				{
					// set true
					isVisible = true;
				}
				else
				{
					// set false
					isVisible = false;
				}
				
				// prop to name
				prop = prop->GetNext();
				
				// get value of name
				wxString name = prop->GetValue();
				
				// prop to location
				prop = prop->GetNext(),
				
				       // get value of location
				       value = prop->GetValue();
				       
				// tokenize value
				tok.SetString(value, wxT(" "));
				
				// get x
				float x = wxAtof(tok.GetNextToken());
				
				// get y
				float y = wxAtof(tok.GetNextToken());
				
				// get z
				float z = wxAtof(tok.GetNextToken());
				
				// prop to orientation
				prop = prop->GetNext();
				
				// get value of orientation
				value = prop->GetValue();
				
				// tokenize value
				tok.SetString(value, wxT(" "));
				
				// get orientationX
				float orientationX = wxAtof(tok.GetNextToken());
				
				// get orientationY
				float orientationY = wxAtof(tok.GetNextToken());
				
				// get orientationZ
				float orientationZ = wxAtof(tok.GetNextToken());
				
				// prop to ref
				prop = prop->GetNext();
				
				// get value of ref
				value = prop->GetValue();
				
				// close entry
				stream.CloseEntry();
				
				// get oax
				GNRAssembly* assembly = loadOax(stream, value);
				
				// set visible
				assembly->setVisible(isVisible);
				
				// set x, y, z
				assembly->setXYZ(x, y, z);
				
				// set x- and y - orientation
				assembly->setPhiTheta(orientationX, orientationY);
				
				// set z-orientation
				assembly->setRho(orientationZ);
				
				// add part
				m_actual->addPart(assembly);
				
				// check if next exist
				if (node->GetNext() != NULL)
				{
					// exist, set node to next
					node = node->GetNext();
				}
				// if not exist
				else
				{
					// node to parent
					node = node->GetParent();
					
					// if parent is scene, break
					if (node->GetName() == wxT("scene"))
					{
						// leave loop
						break;
					}
					
					// set actual
					m_actual = m_actual->getParent();
					
					// while no next
					while (node->GetNext() == NULL)
					{
						// set m_node to next
						node = node->GetParent();
						
						// set actual
						m_actual = m_actual->getParent();
					}
					
					// get next node
					node = node->GetNext();
					
					// start loop from beginning
					continue;
				}
			}
		}
	}
}

/**
 * Loads the given stream and get its all data.
 * @param       wxInputStream    Load obj-File as wxInputStream.
 */
GNRAssembly* GNROpxImport::loadOax(wxZipInputStream& stream, wxString reference)
{
	// wxZipEntry pointer
	wxZipEntry* entry;
	
	// iterator
	std::vector<wxZipEntry*>::iterator it;
	
	// oax importer
	GNROaxImport import;
	
	// walk through all entrys
	for (it = m_vector.begin(); it != m_vector.end(); it++)
	{
		// get actual entry
		entry = *it;
		
		// check if right entry
		if (entry->GetName().AfterFirst('\\') == reference)
		{
			// open entry
			stream.OpenEntry(*entry);
			
			// wxMemoryOutputStream to cache oax
			wxMemoryOutputStream outMem;
			
			// copy data
			stream.Read(outMem);
			
			// wxMemoryInputStream
			wxMemoryInputStream inMem(outMem);
			
			// wxZipInputStream to read content
			wxZipInputStream inZip(inMem);
			
			// reset Stream
			inMem.SeekI(0);
			
			// load oax
			import.Load(inZip);
			
			// add oax to lib
			import.getAssembly()->setHash(m_libctrl->addEntry(reference, inMem, m_filename.BeforeFirst('.')));
		}
	}
	
	return import.getAssembly();
}
