/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNROpxImport
 * @name        GNROpxImport.cpp
 * @date        2008-10-23
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/tokenzr.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>

#include "GNROpxImport.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

//ctor
GNROpxImport::GNROpxImport()
{

}

GNROpxImport::GNROpxImport(GNRScene* scene, wxString filename)
{
	// set GNRScene pointer
	m_camera = scene->getGLCamera();
	
	// load
	Load(filename);
}

GNROpxImport::~GNROpxImport()
{
	//dtor
}

void GNROpxImport::Load(GNRScene* scene, wxString filename)
{
	// set GNRScene pointer
	m_camera = scene->getGLCamera();
	
	// load
	Load(filename);
}

void GNROpxImport::Load(wxString filename)
{
	// create inputstream of file
	wxFFileInputStream fileIn(filename);
	
	// create zipinpustream of fileIn
	wxZipInputStream zipIn(fileIn);
	
	// get first entry
	m_ptrZipEntry = zipIn.GetNextEntry();
	
	// walk through all entrys and push them into vector
	while (m_ptrZipEntry)
	{
		// push pointer to vector
		m_vector.push_back(m_ptrZipEntry);
		
		// get next Entry
		m_ptrZipEntry = zipIn.GetNextEntry();
	}
	
	// walk thorug all vector-entrys, find *.xml
	for (m_vectorit = m_vector.begin(); m_vectorit != m_vector.end(); m_vectorit++)
	{
		// get actual zipEntry
		m_ptrZipEntry = *m_vectorit;
		
		// search entryname matches "*.xml"
		if (m_ptrZipEntry->GetName().Matches(wxT("*.xml")))
		{
			// openEntry
			zipIn.OpenEntry(*m_ptrZipEntry);
			
			// load xmlstream
			LoadXml(zipIn);
			
			// entry found
			continue;
		}
	}
}

void GNROpxImport::LoadXml(wxInputStream& stream)
{
	// temporary attributes
	double x, y, z;
	
	// temporary attribute tokenizer
	wxStringTokenizer tok;
	
	// create xmldocument of inpustream
	wxXmlDocument xml(stream);
	
	// create pointer to xmlnode
	wxXmlNode* node;
	
	// create pointer to xmlproperty
	wxXmlProperty* prop;
	
	// create wxString to store propertyvalues
	wxString value;
	
	// node to projectInformation
	node = xml.GetRoot()->GetChildren();
	
	// node to data
	node = node->GetNext();
	
	// node to camera
	node = node->GetNext();
	
	// node to type
	node = node->GetChildren();
	
	// node to position
	node = node->GetNext();
	
	// prop to location
	prop = node->GetProperties();
	
	// get value of location
	value = prop->GetValue();
	
	wxLogDebug(value);
	
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
}

void GNROpxImport::LoadOax(wxInputStream& stream)
{

}
