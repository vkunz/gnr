/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNROaxImport
 * @name        GNROaxImport.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <string>
#include <wx/xml/xml.h>
#include <wx/tokenzr.h>

#include "GNROaxImport.h"
#include "GNRObjectImport.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * Default Constructor.
 */
GNROaxImport::GNROaxImport()
{
}

/**
 * Loads the given filename. See Load().
 * @param       wxString    Filepath to read from.
 */
GNROaxImport::GNROaxImport(wxString filename)
{
	// create stream of m_filename
	wxFFileInputStream inFile(filename);
	
	// create zipstream
	wxZipInputStream stream(inFile);
	
	// load stream
	Load(stream);
}

/**
 * Loads the given InputStream. See Load().
 * @param       wxInputStream       InputStream to read from.
 */
GNROaxImport::GNROaxImport(wxInputStream& instream)
{
	// create zipstream
	wxZipInputStream stream(instream);
	
	// load stream
	Load(stream);
}

/**
 * Virtual Destructor.
 */
GNROaxImport::~GNROaxImport()
{
	// do nothing
}

/**
 * Returns a pointer to generated GNRAssembly
 */
GNRAssembly* GNROaxImport::getAssembly()
{
	return m_ptrAssembly;
}

/**
 * Parses @a stream as an zip stream and loads its data.
 * @param       wxZipInputStream       InputStream to read from.
 */
void GNROaxImport::Load(wxZipInputStream& stream)
{
	// set pointer to first entry
	m_ptrZipEntry = stream.GetNextEntry();
	
	// walk through all entrys and push them into vector
	while (m_ptrZipEntry)
	{
		// push pointer to vector
		m_vector.push_back(m_ptrZipEntry);
		
		// get next Entry
		m_ptrZipEntry = stream.GetNextEntry();
	}
	
	// walk thorug all vector-entrys, skip .obj-files
	for (m_vectorit = m_vector.begin(); m_vectorit != m_vector.end(); m_vectorit++)
	{
		// get actual zipEntry
		m_ptrZipEntry = *m_vectorit;
		
		// search entryname matches "*.xml"
		if (m_ptrZipEntry->GetName().Matches(wxT("*.xml")))
		{
			// openEntry
			stream.OpenEntry(*m_ptrZipEntry);
			
			// load xmlstream
			LoadXml(stream);
			
			// entry found
			continue;
		}
		
		// search entryname matches "*.mtl"
		if (m_ptrZipEntry->GetName().Matches(wxT("*.mtl")))
		{
			// openEntry
			stream.OpenEntry(*m_ptrZipEntry);
			
			wxStreamBuffer blub(stream, wxStreamBuffer::read_write);
			
			// insert pail into map
			m_map.insert(std::pair<wxString, wxInputStream*>(m_ptrZipEntry->GetName(), &stream));
			
			// entry found
			continue;
		}
	}
	
	// walk thorug all vector-entrys
	for (m_vectorit = m_vector.begin(); m_vectorit != m_vector.end(); m_vectorit++)
	{
		// get actual zipEntry
		m_ptrZipEntry = *m_vectorit;
		
		// search entryname matches obj-filename
		if (m_ptrZipEntry->GetName().Matches(m_objFilename))
		{
			// openEntry
			stream.OpenEntry(*m_ptrZipEntry);
			
			// load objfile
			LoadObj(stream);
			
			// obj-file found
			continue;
		}
	}
}

/**
 * Parses @a filename as a InputFile stream and loads its data.
 * @param       wxString       Filename to read from.
 */
void GNROaxImport::Load(wxString& filename)
{
	// create stream of m_filename
	wxFFileInputStream inFile(filename);
	
	// create zipstream
	wxZipInputStream stream(inFile);
	
	// load stream
	Load(stream);
}

/**
 * Parses @a stream as a InputStream and loads its data.
 * @param       wxInputStream       InputStream to read from.
 */
void GNROaxImport::LoadXml(wxInputStream& stream)
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
	
	// node to assemblyInformation
	node = xml.GetRoot()->GetChildren();
	
	// node to data
	node = node->GetNext();
	
	// node to lightsource
	node = node->GetChildren();
	
	// node to obj
	node = node->GetNext();
	
	// prop to scale
	prop = node->GetProperties();
	
	// get value of scale
	value = prop->GetValue();
	
	// tokenize value
	tok.SetString(value, wxT(" "));
	
	// get x-scale
	tok.GetNextToken().ToDouble(&x);
	m_scalex = x;
	
	// get y-scale
	tok.GetNextToken().ToDouble(&y);
	m_scaley = y;
	
	// get z-scale
	tok.GetNextToken().ToDouble(&z);
	m_scalez = z;
	
	// prop to locationOffset
	prop = prop->GetNext();
	
	// get value of locationOffset
	value = prop->GetValue();
	
	// tokenize value
	tok.SetString(value, wxT(" "));
	
	// get x-offset
	tok.GetNextToken().ToDouble(&x);
	m_offsetx = x;
	
	// get y-offset
	tok.GetNextToken().ToDouble(&y);
	m_offsety = y;
	
	// get z-offset
	tok.GetNextToken().ToDouble(&z);
	m_offsetz = z;
	
	// prop to orientation
	prop = prop->GetNext();
	
	// get value of orientation
	value = prop->GetValue();
	
	// tokenize value
	tok.SetString(value, wxT(" "));
	
	// get x-orientation
	tok.GetNextToken().ToDouble(&x);
	m_orientationx = x;
	
	// get y-orientation
	tok.GetNextToken().ToDouble(&y);
	m_orientationy = y;
	
	// get z-orientation
	tok.GetNextToken().ToDouble(&z);
	m_orientationz = z;
	
	// prop to ref
	prop = prop->GetNext();
	
	// get value of ref
	m_objFilename = prop->GetValue();
}

/**
 * Parses @a stream as a InputStream and loads its data.
 * @param       wxInputStream       InputStream to read from.
 */
void GNROaxImport::LoadObj(wxInputStream& stream)
{
	// create ObjectImportobject
	GNRObjectImport import;
	
	// placeholder for GNRObjectImport-call
	//m_ptrAssembly = import.read()
	
	// set x-offset
	m_ptrAssembly->setX(m_offsetx);
	
	// set y-offset
	m_ptrAssembly->setY(m_offsety);
	
	// set z-offset
	m_ptrAssembly->setZ(m_offsetz);
	
	
	// set x-orientation
	m_ptrAssembly->setPhi(m_orientationx);
	
	// set y-orientation
	m_ptrAssembly->setRho(m_orientationy);
	
	// set z-orientation
	m_ptrAssembly->setTheta(m_orientationz);
	
	
	// set x-scale
	m_ptrAssembly->setScaleX(m_scalex);
	
	// set y-scale
	m_ptrAssembly->setScaleY(m_scaley);
	
	// set z-scale
	m_ptrAssembly->setScaleZ(m_scalez);
	
	// set assemly-name
	m_ptrAssembly->setName(std::string(std::string(m_objFilename.BeforeLast('.').mb_str())));
}
