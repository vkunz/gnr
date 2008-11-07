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
	//dtor
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
	
	// create GNROaxImport
	m_oaxImport = new GNROaxImport();
	
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
			LoadXml(*m_inZip);
			
			// entry found
			continue;
		}
	}
}

/**
 * Loads the given stream and get its all data.
 * @param       wxInputStream    Load xml-File as wxInputStream.
 */
void GNROpxImport::LoadXml(wxInputStream& stream)
{
	// temporary attributes
	double x, y, z;
	
	// create xmldocument of inpustream
	wxXmlDocument xml(stream);
	
	// node to root
	m_node = xml.GetRoot();
	
	// node to assemblyInformation
	m_node = m_node->GetChildren();
	
	// node to name
	m_node = m_node->GetChildren();
	
	// get name
	m_name = m_node->GetNodeContent();
	
	// node to author
	m_node = m_node->GetNext();
	
	// get author
	m_author = m_node->GetNodeContent();
	
	// node to projectInformation
	m_node = m_node->GetParent();
	
	// node to data
	m_node = m_node->GetNext();
	
	// node to camera
	m_node = m_node->GetChildren();
	
	// node to type
	m_node = m_node->GetChildren();
	
	// node to position
	m_node = m_node->GetNext();
	
	// prop to location
	m_prop = m_node->GetProperties();
	
	// get value of location
	m_value = m_prop->GetValue();
	
	// tokenize value
	m_tok.SetString(m_value, wxT(" "));
	
	// get camera x-position
	m_tok.GetNextToken().ToDouble(&x);
	
	// get camera y-position
	m_tok.GetNextToken().ToDouble(&y);
	
	// get camera z-position
	m_tok.GetNextToken().ToDouble(&z);
	
	// set camera position
	m_camera->setPosition(x, y, z);
	
	// prop to orientation
	m_prop = m_prop->GetNext();
	
	// get value of orientation
	m_value = m_prop->GetValue();
	
	// tokenize value
	m_tok.SetString(m_value, wxT(" "));
	
	// get camera x-orientation
	m_tok.GetNextToken().ToDouble(&x);
	
	// get camera y-orientation
	m_tok.GetNextToken().ToDouble(&y);
	
	// get camera z-orientation
	m_tok.GetNextToken().ToDouble(&z);
	
	// set camera orientation
	m_camera->setAngles(x, y, z);
	
	// node to camera
	m_node = m_node->GetParent();
	
	// node to lightsources
	m_node = m_node->GetNext();
	
	// node to scene
	m_node = m_node->GetNext();
	
	// node to first scene children
	m_node = m_node->GetChildren();
	
	// set m_actual to m_scene->rootAssembly
	m_actual = m_scene->getRootAssembly();
	
	// walk through all scene-children
	while (m_node)
	{
		// check if is an assembly
		if (m_node->GetName() == wxT("assembly"))
		{
			// create new Assembly
			CreateAssembly(*m_inZip);
		}
		// check if is a group
		else if (m_node->GetName() == wxT("group"))
		{
			// create new group
			CreateGroup(*m_inZip);
		}
		
		// check if next node is available
		if (m_node->GetNext() == NULL)
		{
			break;
		}
		// everything ok, set next node
		else
		{
			// set node to next children
			m_node = m_node->GetNext();
		}
	}
}

/**
 * Loads the given stream and get its all data.
 * @param       wxInputStream    Load obj-File as wxInputStream.
 */
GNRAssembly* GNROpxImport::LoadOax(wxInputStream& stream)
{
	// create new wxZipInputStream
	wxZipInputStream inZip(stream);
	
	// start oaximport and return assembly
	m_oaxImport->Load(inZip);
	
	// return assembly
	return m_oaxImport->getAssembly();
}

void GNROpxImport::CreateAssembly(wxZipInputStream& stream)
{
	// temporary attributes
	// GNRAssembly pointer
	GNRAssembly* assembly;
	
	// flag if assembly is visible
	bool isVisible;
	
	// double for converting
	double x, y, z;
	
	// location
	float locationX, locationY, locationZ;
	
	// orientation
	float orientationX, orientationY, orientationZ;
	
	// prop to visible
	m_prop = m_node->GetProperties();
	
	// set visibility
	if (m_prop->GetValue() == wxT("true"))
	{
		isVisible = true;
	}
	else
	{
		isVisible = false;
	}
	
	// m_prop to location
	m_prop = m_prop->GetNext();
	
	// get value of location
	m_value = m_prop->GetValue();
	
	// tokenize value
	m_tok.SetString(m_value, wxT(" "));
	
	// get x-position
	m_tok.GetNextToken().ToDouble(&x);
	locationX = x;
	
	// get y-position
	m_tok.GetNextToken().ToDouble(&y);
	locationY = y;
	
	// get z-position
	m_tok.GetNextToken().ToDouble(&z);
	locationZ = z;
	
	// m_prop to orientation
	m_prop = m_prop->GetNext();
	
	// get value of orientation
	m_value = m_prop->GetValue();
	
	// tokenize value
	m_tok.SetString(m_value, wxT(" "));
	
	// get x-orientation
	m_tok.GetNextToken().ToDouble(&x);
	orientationX = x;
	
	// get y-orientation
	m_tok.GetNextToken().ToDouble(&y);
	orientationY = y;
	
	// get z-orientation
	m_tok.GetNextToken().ToDouble(&z);
	orientationZ = z;
	
	// m_prop to ref
	m_prop = m_prop->GetNext();
	
	// get filename
	m_objFilename = m_prop->GetValue();
	
	// walk through all vector-entrys, find specified oax
	for (m_vectorit = m_vector.begin(); m_vectorit != m_vector.end(); m_vectorit++)
	{
		// get actual zipEntry
		m_ptrZipEntry = *m_vectorit;
		
		// set path separator
		wxString sep = wxFileName::GetPathSeparator();
		
		// search entryname matches m_objFilename
		if (m_ptrZipEntry->GetName().Matches(wxT("assemblies") + sep + m_objFilename))
		{
			// openEntry
			m_inZip->OpenEntry(*m_ptrZipEntry);
			
			// load oax
			assembly = LoadOax(*m_inZip);
			
			// entry found
			continue;
		}
	}
	
	// set locationOffset
	assembly->setXYZ(locationX, locationY, locationZ);
	
	// set orientationOffset x and z
	assembly->setPhiTheta(orientationX, orientationZ);
	
	// set orientationOffset y
	assembly->setRho(locationY);
	
	// check if m_actual is rootAssembly
	if (m_actual == m_scene->getRootAssembly())
	{
		// if isVisible true, insert visble assembly
		if (isVisible)
		{
			m_scene->insertAssembly(assembly);
		}
		// if not, insert hidden assembly
		else
		{
			assembly->setVisible(false);
			m_scene->insertAssembly(assembly);
		}
	}
	else
	{
		m_actual->addPart(assembly);
	}
}

void GNROpxImport::CreateGroup(wxZipInputStream& stream)
{
	// temporary attributes
	// store visibility
	bool isVisible;
	
	// double for converting
	double x, y, z;
	
	// prop to visible
	m_prop = m_node->GetProperties();
	
	// set visibility
	if (m_prop->GetValue() == wxT("true"))
	{
		isVisible = true;
	}
	else
	{
		isVisible = false;
	}
	
	// m_prop to name
	m_prop = m_prop->GetNext();
	
	// create new Assembly -> new group
	GNRAssembly* assembly = new GNRAssembly(m_prop->GetValue());
	
	// set type as group
	assembly->setType(IS_GROUP);
	
	// set m_actual
	m_actual = assembly;
	
	// m_prop to location
	m_prop = m_prop->GetNext();
	
	// get value of location
	m_value = m_prop->GetValue();
	
	// tokenize value
	m_tok.SetString(m_value, wxT(" "));
	
	// get x-position
	m_tok.GetNextToken().ToDouble(&x);
	
	// get y-position
	m_tok.GetNextToken().ToDouble(&y);
	
	// get z-position
	m_tok.GetNextToken().ToDouble(&z);
	
	// set location x, y, z
	m_actual->setXYZ(x, y, z);
	
	// m_prop to orientation
	m_prop = m_prop->GetNext();
	
	// get value of orientation
	m_value = m_prop->GetValue();
	
	// tokenize value
	m_tok.SetString(m_value, wxT(" "));
	
	// get x-orientation
	m_tok.GetNextToken().ToDouble(&x);
	
	// get y-orientation
	m_tok.GetNextToken().ToDouble(&y);
	
	// get z-orientation
	m_tok.GetNextToken().ToDouble(&z);
	
	// set orientation x and z
	m_actual->setPhiTheta(x, z);
	
	// set orientation y
	m_actual->setRho(y);
	
	// set node to children
	m_node = m_node->GetChildren();
	
	// walk through all scene-children
	while (m_node)
	{
		// check if is an assembly
		if (m_node->GetName() == wxT("assembly"))
		{
			// create new Assembly
			CreateAssembly(*m_inZip);
		}
		// check if is a group
		else if (m_node->GetName() == wxT("group"))
		{
			// create new group
			CreateGroup(*m_inZip);
		}
		
		// check if next node is available
		if (m_node->GetNext() == NULL)
		{
			break;
		}
		// everything ok, set next node
		else
		{
			// set node to next children
			m_node = m_node->GetNext();
		}
	}
	
	// check if m_actual is rootAssembly
	if (m_actual == m_scene->getRootAssembly())
	{
		// if isVisible true, insert visble assembly
		if (isVisible)
		{
			m_scene->insertAssembly(assembly);
		}
		// if not, insert hidden assembly
		else
		{
			assembly->setVisible(false);
			m_scene->insertAssembly(assembly);
		}
	}
	else
	{
		m_actual->addPart(assembly);
	}
	
	// node to parent
	m_node = m_node->GetParent();
	
	// m_actual to parent
	m_actual = m_actual->getParent();
}
