/**
 * OpxImport
 * @name        OpxImport.cpp
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

#include "NotifyEvent.h"
#include "OpxImport.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * Default Constructor.
 */
OpxImport::OpxImport()
{
}

/**
 * Loads the given filename. See Load(wxString filename).
 * @param[in]   controller      Pointer to LibraryTree
 * @param[in]   filename        Filepath to read from.
 */
OpxImport::OpxImport(TreeLibraryController* controller, wxString filename)
{
	// assign librarycontroller
	m_libctrl = controller;
	
	// asign scene
	m_scene = Scene::getInstance();
	
	// set camera pointer
	m_camera = m_scene->getGLCamera3D();
	
	// store filename
	m_filename = filename;
}

/**
 * Is called on thread-start
 */
void* OpxImport::Entry()
{
	// create stream of filename
	wxFFileInputStream inFile(m_filename);
	
	// create zipstream
	wxZipInputStream stream(inFile);
	
	// load
	Load(stream);
	
	return NULL;
}

/**
 * Virtual Destructor.
 */
OpxImport::~OpxImport()
{
}

/**
 * Loads the given file and get all its data.
 * @param       stream    wxZipInputStream to load from
 */
void OpxImport::Load(wxZipInputStream& stream)
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
}

/**
 * Loads the given stream and get its all data.
 * @param       stream    Load xml-File as wxZipInputStream.
 */
void OpxImport::loadXml(wxZipInputStream& stream)
{
	// temporary attributes
	double x, y, z, p, t, r;
	bool isVisible;
	
	// assembly pointer
	Assembly* assembly;
	
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
	
	// prop to orientation
	prop = prop->GetNext();
	
	// get value of orientation
	value = prop->GetValue();
	
	// tokenize value
	tok.SetString(value, wxT(" "));
	
	// get camera x-orientation
	tok.GetNextToken().ToDouble(&p);
	
	// get camera y-orientation
	tok.GetNextToken().ToDouble(&t);
	
	// get camera z-orientation
	tok.GetNextToken().ToDouble(&r);
	
	// set camera position
	m_camera->setCamera(x, y, z, p, t, r);
	
	// node to camera
	node = node->GetParent();
	
	// node to lightsources
	node = node->GetNext();
	
	// node to scene
	node = node->GetNext();
	
	// check if scene has childs
	if (node->GetChildren() != NULL)
	{
		// node to first scene-object
		node = node->GetChildren();
		
		// set m_actual to m_scene->rootAssembly
		m_actual = m_scene->getRootAssembly();
		
		// walk through all next nodes
		while (node)
		{
			if (node->GetName() == wxT("group"))
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
				Assembly* newGroup = new Assembly(value);
				
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
				newGroup->position().setX(wxAtof(tok.GetNextToken()));
				
				// set y
				newGroup->position().setY(wxAtof(tok.GetNextToken()));
				
				// set z
				newGroup->position().setZ(wxAtof(tok.GetNextToken()));
				
				// prop to orientation
				prop = prop->GetNext();
				
				// get value of orientation
				value = prop->GetValue();
				
				// tokenize value
				tok.SetString(value, wxT(" "));
				
				// set phi
				newGroup->rotation().setX(wxAtof(tok.GetNextToken()));
				
				// set theta
				newGroup->rotation().setY(wxAtof(tok.GetNextToken()));
				
				// set rho
				newGroup->rotation().setZ(wxAtof(tok.GetNextToken()));
				
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
				prop = prop->GetNext();
				
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
				
				// create assembly and ask if already exist
				assembly = m_scene->getOrigialFromHash(value.BeforeFirst('.'));
				
				// check if already known
				if (assembly != NULL)
				{
					assembly = assembly->clone();
				}
				// if not
				else
				{
					// get oax
					assembly = loadOax(stream, value);
				}
				
				// set visible
				assembly->setVisible(isVisible);
				
				// set name
				assembly->setName(name);
				
				// set x, y, z
				assembly->position().setAll(x, y, z);
				
				// set x- and y - orientation
				assembly->rotation().setAll(orientationX, orientationY, orientationZ);
				
				// set object
				assembly->setType(IS_OBJECT);
				
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
					while (node->GetNext() == NULL && !m_actual->isType(IS_ROOT))
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
 * @param       stream          Load obj-File as wxInputStream.
 * @param       reference       find md5 hash combination
 */
Assembly* OpxImport::loadOax(wxZipInputStream& stream, wxString reference)
{
	// wxZipEntry pointer
	wxZipEntry* entry;
	
	// iterator
	std::vector<wxZipEntry*>::iterator it;
	
	// oax importer
	OaxImport import;
	
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
			
			// add oax to lib (default base cat = 0)
			import.getAssembly()->setHash(m_libctrl->addEntry(inMem, m_filename.BeforeFirst('.'),0));
		}
	}
	
	return import.getAssembly();
}

/**
 * gets called when thread stops running
 */
void OpxImport::OnExit()
{
	// Event for signaling end of thread
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(OPXIMPORTFINISHED);
	myevent.SetEventObject(this);
	ProcessEvent(myevent);
}
