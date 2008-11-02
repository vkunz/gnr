/**
 * GNROpxExport
 * @name        GNROpxExport.cpp
 * @date        2008-11-02
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
	
	// set actual as root
	m_actual = root;
	
	// create data
	m_node = new wxXmlNode(m_actual, wxXML_ELEMENT_NODE, wxT("data"));
	
	// create scene
	m_node = new wxXmlNode(m_actual, wxXML_ELEMENT_NODE, wxT("scene"));
	
	// set root
	xml.SetRoot(root);
	
	// create new entry
	m_outZip->PutNextEntry(wxT("content.xml"));
	
	// save xml document to zipstream
	xml.Save(*m_outZip);
	
	// close entry
	m_outZip->CloseEntry();
}

void GNROpxExport::createOpxStream()
{
	// create new xml entry
	createXmlEntry();
	
	// close zip file
	m_outZip->Close();
}
