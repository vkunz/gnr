/**
 * GNROpxImport
 * @name        GNROpxImport.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
GNROpxImport::GNROpxImport(GNRScene* scene, wxString filename)
{
	// set GNRScene pointer
	m_camera = scene->getGLCamera3D();
	
	// asign scene
	m_scene = scene;
	
	// load
	Load(filename);
}

/**
 * Virtual Destructor.
 */
GNROpxImport::~GNROpxImport()
{
}

/**
 * Loads the given filename. See Load(wxString filename).
 * @param       wxString    Filepath to read from.
 * @param       GNRScene*   Assigns pointer to actual scene.
 */
void GNROpxImport::Load(GNRScene* scene, wxString filename)
{
	// set GNRCamera pointer
	m_camera = scene->getGLCamera3D();
	
	// asign scene
	m_scene = scene;
	
	// load
	Load(filename);
}

/**
 * Loads the given file and get all its data.
 * @param       wxString    Filepath to read from.
 */
void GNROpxImport::Load(wxString filename)
{
	// create inputstream of file
	m_inFile = new wxFFileInputStream(filename);
	
	// create zipinpustream of fileIn
	m_inZip = new wxZipInputStream(*m_inFile);
	
	// get first entry
	m_ptrZipEntry = m_inZip->GetNextEntry();
	
	// walk through all entrys and push them into vector
	while (m_ptrZipEntry)
	{
		// push pointer to vector
		m_vector.push_back(m_ptrZipEntry);
		
		// get next Entry
		m_ptrZipEntry = m_inZip->GetNextEntry();
	}
	
	// walk through all vector-entrys, find *.xml
	for (m_vectorit = m_vector.begin(); m_vectorit != m_vector.end(); m_vectorit++)
	{
		// get actual zipEntry
		m_ptrZipEntry = *m_vectorit;
		
		// search entryname matches "*.xml"
		if (m_ptrZipEntry->GetName().Matches(wxT("*.xml")))
		{
			// openEntry
			m_inZip->OpenEntry(*m_ptrZipEntry);
			
			// load xmlstream
			loadXml(*m_inZip);
			
			// entry found
			continue;
		}
	}
}

/**
 * Loads the given stream and get its all data.
 * @param       wxInputStream    Load xml-File as wxInputStream.
 */
void GNROpxImport::loadXml(wxInputStream& stream)
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
				GNRAssembly* newGroup = new GNRAssembly(value);
				
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
				wxLogDebug(wxT("assembly"));
				
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
				
				// get oax
				GNRAssembly* assembly = loadOax(value);
				
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
GNRAssembly* GNROpxImport::loadOax(wxString reference)
{
	// wxZipnEntry pointer
	wxZipEntry* entry;
	
	// walk through all entrys
	for (m_vectorit = m_vector.begin(); m_vectorit != m_vector.end(); m_vectorit++)
	{
		// get actual entry
		entry = *m_vectorit;
		
		wxLogDebug(entry->GetName());
		
	}
}
