/**
 * FrameData
 * @name        GNRFrameData.h
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/xml/xml.h>

#include "GNROaxExport.h"

// ctor
GNROaxExport::GNROaxExport(GNRFrameData* data)
{
	// data from ObjOaxConv -> export to FileSystem
	m_saveToFileSystem = true;
	
	// asign data
	m_frameData = data;
	
	// create oax output stream and store in internal pointer
	createOaxStream();
}

GNROaxExport::GNROaxExport(GNRAssembly* assembly)
{
	// data from an Assembly -> return wxZipOutputStream
	m_saveToFileSystem = false;
	
	// create a new GNRFrameData object
	m_frameData = new GNRFrameData();
}

// dtor
GNROaxExport::~GNROaxExport()
{
	// do nothing
}

void GNROaxExport::createXmlEntry()
{
	// temporary string for converting
	wxString conv;
	
	// create new empty xml document
	wxXmlDocument xml;
	
	// set xml version
	xml.SetVersion(wxT("1.0"));
	
	// set file encoding
	xml.SetFileEncoding(wxT("UTF-8"));
	
	// create root, future root
	wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("oaxml"));
	
	// add property "standard="oaxml.hs-ulm.de""
	root->AddProperty(wxT("standard"), wxT("oaxml.hs-ulm.de"));
	
	// add property "version="0.1.0""
	root->AddProperty(wxT("version"), wxT("0.1.0"));
	
	// set actual as root
	m_actual = root;
	
	// create data
	m_node = new wxXmlNode(m_actual, wxXML_ELEMENT_NODE, wxT("data"));
	
	// set m_actual to data
	m_actual = m_actual->GetChildren();
	
	// create obj
	m_node = new wxXmlNode(m_actual, wxXML_ELEMENT_NODE, wxT("obj"));
	
	// add scale attribute
	conv << (float)m_frameData->m_scaleWidth;
	conv += wxT(" ");
	conv << (float)m_frameData->m_scaleHeight;
	conv += wxT(" ");
	conv << (float)m_frameData->m_scaleDepth;
	m_node->AddProperty(wxT("scale"), conv);
	
	// emtpy conv
	conv.Empty();
	
	// add locationOffset
	conv << (float)m_frameData->m_offsetX;
	conv += wxT(" ");
	conv << (float)m_frameData->m_offsetY;
	conv += wxT(" ");
	conv << (float)m_frameData->m_offsetZ;
	m_node->AddProperty(wxT("locationOffset"), conv);
	
	// add orientationOffset
	m_node->AddProperty(wxT("orientationOffset"), wxT("0 0 0"));
	
	// iterator to walk through m_frameData->m_listFiles and m_frameData->m_tags
	std::list<wxString>::iterator it;
	
	// set it to first entry
	it = m_frameData->m_listFiles.begin();
	
	// add ref
	m_node->AddProperty(wxT("ref"), (*it).AfterLast('\\'));
	
	// set m_actual to oaxml
	m_actual = m_actual->GetParent();
	
	// create assemblyInformation
	m_node = new wxXmlNode(m_actual, wxXML_ELEMENT_NODE, wxT("assemblyInformation"));
	
	// set m_actual to assemblyInformation
	m_actual = m_actual->GetChildren();
	
	// create tags
	m_node = new wxXmlNode(m_actual, wxXML_ELEMENT_NODE, wxT("tags"));
	
	// set m_actual to tags
	m_actual = m_actual->GetChildren();
	
	// create tags
	for (it = m_frameData->m_tags.begin(); it != m_frameData->m_tags.end(); it++)
	{
		// create tag
		m_node = new wxXmlNode(m_actual, wxXML_ELEMENT_NODE, wxT("tag"));
		
		// set tag content
		m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("tag"), (*it)));
	}
	
	// set m_actual to assemblyInformation
	m_actual = m_actual->GetParent();
	
	// create author
	m_node = new wxXmlNode(m_actual, wxXML_ELEMENT_NODE, wxT("author"));
	
	// create author content
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("author"), wxT("GNR")));
	
	// create name
	m_node = new wxXmlNode(m_actual, wxXML_ELEMENT_NODE, wxT("name"));
	
	// set m_actual to name
	m_node->AddChild(new wxXmlNode(wxXML_TEXT_NODE, wxT("name"), m_frameData->m_name));
	
	// set root
	xml.SetRoot(root);
	
	// create new entry
	m_outZip->PutNextEntry(wxT("content.xml"));
	
	xml.Save(*m_outZip);
	m_outZip->CloseEntry();
}

void GNROaxExport::createOaxStream()
{
	// check if stream has to be written to file, if yes, create outputstream
	if (m_saveToFileSystem)
	{
		// create FileOutputStream
		m_outStream = new wxFFileOutputStream(wxT("data\\") + m_frameData->m_name + wxT(".oax"));
		
		// create new wxZipOutputStream object
		m_outZip = new wxZipOutputStream(m_outStream, -1);
	}
	// if not, use m_outStream
	else
	{
		// create new wxZipOutputStream object and use m_outStream as parent
		m_outZip = new wxZipOutputStream(m_outStream, -1, wxConvUTF8);
	}
	
	// create new xml entry
	createXmlEntry();
	
	// copy all needed files by this assembly
	for (std::list<wxString>::const_iterator it = m_frameData->m_listFiles.begin(); it != m_frameData->m_listFiles.end(); it++)
	{
		// create new inputstream
		wxFFileInputStream inFile((*it));
		
		// put nex entry
		wxString filename = (*it).AfterLast('\\');
		
		m_outZip->PutNextEntry(filename);
		
		// copy data
		inFile.Read(*m_outZip);
		
		// close entry
		m_outZip->CloseEntry();
	}
	
	m_outZip->Close();
}