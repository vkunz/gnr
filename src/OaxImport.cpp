/**
 * OaxImport
 * @name        OaxImport.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <string>
#include <wx/sstream.h>
#include <wx/tokenzr.h>
#include <wx/xml/xml.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "Assembly.h"
#include "OaxImport.h"
#include "ObjectImport.h"
#include "PrimitiveCreator.h"

/**
 * Default Constructor.
 */
OaxImport::OaxImport()
{
	// create new map
	m_map = new std::map<wxString, wxString>;
}

/**
 * Loads the given filename. See Load().
 * @param       filename        wxString Filepath to read from.
 */
OaxImport::OaxImport(wxString filename)
{
	// create stream of filename
	wxFFileInputStream inFile(filename);

	// create zipstream
	wxZipInputStream stream(inFile);

	// create new map
	m_map = new std::map<wxString, wxString>;

	// create new map
	m_map = new std::map<wxString, wxString>;

	// load stream
	Load(stream);
}

/**
 * Virtual Destructor.
 */
OaxImport::~OaxImport()
{
	// delete map
	delete m_map;
}

/**
 * Returns a pointer to generated Assembly
 */
Assembly* OaxImport::getAssembly()
{
	return m_ptrAssembly;
}

/**
 * Parses @a stream as an zip stream and loads its data.
 * @param       stream          wxZipInputStream to read from.
 */
void OaxImport::Load(wxZipInputStream& stream)
{
	// empty map
	m_map->clear();

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

	// walk through all vector-entrys, skip .obj-files
	for (m_vectorit = m_vector.begin(); m_vectorit != m_vector.end(); m_vectorit++)
	{
		// get actual zipEntry
		m_ptrZipEntry = *m_vectorit;

		// search entryname matches "*.xml"
		if (m_ptrZipEntry->GetName().Matches(wxT("*.xml")))
		{
			// openEntry
			stream.OpenEntry(*m_ptrZipEntry);

			// check if there is only one entry, if yes, it is a primitive-oax
			if (m_vector.size() == 1)
			{
				// load primitivesXml-Stream
				LoadPrimitivesXml(stream);
			}
			// if more than one entries, assembly-oax
			else
			{
				// load assemblyXml-Stream
				LoadAssemblyXml(stream);
			}

			// entry found
			continue;
		}

		// search entryname matches "*.mtl"
		if (m_ptrZipEntry->GetName().Matches(wxT("*.mtl")))
		{
			// openEntry
			stream.OpenEntry(*m_ptrZipEntry);

			// temporary string
			wxString tmp;

			// create wxStringOutputStream to get content of mtl file
			wxStringOutputStream outString(&tmp);

			// read zipstream and store content into tmp
			stream.Read(outString);

			// insert file name and its content into map
			m_map->insert(std::pair<wxString, wxString>(m_ptrZipEntry->GetName(), tmp));

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
 * @param       filename            wxString Filename to read from.
 */
void OaxImport::Load(wxString& filename)
{
	// create stream of m_filename
	wxFFileInputStream inFile(filename);

	// create zipstream
	wxZipInputStream stream(inFile);

	// load stream
	Load(stream);
}

/**
 * Parses a stream as a InputStream and loads its data.
 * @param       stream       wxInputStream to read from.
 */
void OaxImport::LoadAssemblyXml(wxInputStream& stream)
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

	// node to oaxml
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

	// node to Tags
	node = node->GetNext();

	// node to first Tag
	node = node->GetChildren();

	// walk through all tags
	while (node)
	{
		// get content of tag and store in m_vecTags
		m_vecTags.push_back(node->GetNodeContent());

		// check if next exist, if not, leave
		if (node->GetNext() == NULL)
		{
			break;
		}
		// everything ok, set next node
		else
		{
			// set node to next group
			node = node->GetNext();
		}
	}

	// node to tags
	node = node->GetParent();

	// node to assemblyInformation
	node = node->GetParent();

	// node to data
	node = node->GetNext();

	// node to obj
	node = node->GetChildren();

	// prop to scale
	prop = node->GetProperties();

	// get value of scale
	value = prop->GetValue();

	// tokenize value
	tok.SetString(value, wxT(" "));

	// get x-scale
	tok.GetNextToken().ToDouble(&x);
	m_scaleX = x;

	// get y-scale
	tok.GetNextToken().ToDouble(&y);
	m_scaleY = y;

	// get z-scale
	tok.GetNextToken().ToDouble(&z);
	m_scaleZ = z;

	// prop to locationOffset
	prop = prop->GetNext();

	// get value of locationOffset
	value = prop->GetValue();

	// tokenize value
	tok.SetString(value, wxT(" "));

	// get x-locationOffset
	tok.GetNextToken().ToDouble(&x);
	m_locationOffsetX = x;

	// get y-locationOffset
	tok.GetNextToken().ToDouble(&y);
	m_locationOffsetY = y;

	// get z-locationOffset
	tok.GetNextToken().ToDouble(&z);
	m_locationOffsetZ = z;

	// prop to orientationOffset
	prop = prop->GetNext();

	// get value of orientationOffset
	value = prop->GetValue();

	// tokenize value
	tok.SetString(value, wxT(" "));

	// get x-orientationOffset
	tok.GetNextToken().ToDouble(&x);
	m_orientationOffsetX = x;

	// get y-orientationOffset
	tok.GetNextToken().ToDouble(&y);
	m_orientationOffsetY = y;

	// get z-orientationOffset
	tok.GetNextToken().ToDouble(&z);
	m_orientationOffsetZ = z;

	// prop to ref
	prop = prop->GetNext();

	// get value of ref
	m_objFilename = prop->GetValue();
}

/**
 * load primitive xml
 * @param       stream       wxInputStream to read from.
 */
void OaxImport::LoadPrimitivesXml(wxInputStream& stream)
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

	// node to name
	node = node->GetChildren();

	// get name
	m_name = node->GetNodeContent();

	// node to author
	node = node->GetNext();

	// get author
	m_author = node->GetNodeContent();

	// node to Tags
	node = node->GetNext();

	if (node->GetChildren() != NULL)
	{
		// node to first Tag
		node = node->GetChildren();

		// walk through all tags
		while (node)
		{
			// get content of tag and store in m_vecTags
			m_vecTags.push_back(node->GetNodeContent());

			// check if next exist, if not, leave
			if (node->GetNext() == NULL)
			{
				break;
			}
			// everything ok, set next node
			else
			{
				// set node to next group
				node = node->GetNext();
			}
		}

		// node to tags
		node = node->GetParent();
	}

	// node to assemblyInformation
	node = node->GetParent();

	// node to data
	node = node->GetNext();

	// node to first primitive
	node = node->GetChildren();

	// walk through all primitives
	while (node)
	{
		// check if is cuboid
		if (node->GetName() == wxT("cuboid"))
		{
			// prop to visible
			prop = node->GetProperties();

			// get value of visible
			value = prop->GetValue();

			// check if true
			if (value == wxT("true"))
			{
				m_visible = true;
			}
			// not true -> false
			else
			{
				m_visible = false;
			}

			// prop to locationOffset
			prop = prop->GetNext();

			// get value of locationOffset
			value = prop->GetValue();

			// tokenize value
			tok.SetString(value, wxT(" "));

			// get x-locationOffset
			tok.GetNextToken().ToDouble(&x);
			m_locationOffsetX = x;

			// get y-locationOffset
			tok.GetNextToken().ToDouble(&y);
			m_locationOffsetY = y;

			// get z-locationOffset
			tok.GetNextToken().ToDouble(&z);
			m_locationOffsetZ = z;

			// prop to orientationOffset
			prop = prop->GetNext();

			// get value of orientationOffset
			value = prop->GetValue();

			// tokenize value
			tok.SetString(value, wxT(" "));

			// get x-orientationOffset
			tok.GetNextToken().ToDouble(&x);
			m_orientationOffsetX = x;

			// get y-orientationOffset
			tok.GetNextToken().ToDouble(&y);
			m_orientationOffsetY = y;

			// get z-orientationOffset
			tok.GetNextToken().ToDouble(&z);
			m_orientationOffsetZ = z;

			// node to width
			node = node->GetChildren();

			// get value of width
			node->GetNodeContent().ToDouble(&x);
			m_width = x;

			// node to height
			node = node->GetNext();

			// get value of height
			node->GetNodeContent().ToDouble(&x);
			m_height = x;

			// node to depth
			node = node->GetNext();

			// get value of depth
			node->GetNodeContent().ToDouble(&x);
			m_depth = x;

			// node to parent
			node = node->GetParent();

			// primitive creator
			PrimitiveCreator creator;

			// new cuboid
			creator.createCuboid(Vertex(m_locationOffsetX, m_locationOffsetY, m_locationOffsetZ),
			                     Vertex(m_orientationOffsetX, m_orientationOffsetY, m_orientationOffsetZ),
			                     Vertex(m_width, m_height, m_depth));

			// asign primitive
			m_ptrAssembly = creator.getPrimitive();
			break;

			// check if next exist, if not, leave
			if (node->GetNext() == NULL)
			{
				break;
			}
			// everything ok, set next node
			else
			{
				// set node to next group
				node = node->GetNext();
			}

			// primitive found
			continue;
		}

		// check if is cylinder
		if (node->GetName() == wxT("cylinder"))
		{
			// prop to visible
			prop = node->GetProperties();

			// get value of visible
			value = prop->GetValue();

			// check if true
			if (value == wxT("true"))
			{
				m_visible = true;
			}
			// not true -> false
			else
			{
				m_visible = false;
			}

			// prop to locationOffset
			prop = prop->GetNext();

			// get value of locationOffset
			value = prop->GetValue();

			// tokenize value
			tok.SetString(value, wxT(" "));

			// get x-locationOffset
			tok.GetNextToken().ToDouble(&x);
			m_locationOffsetX = x;

			// get y-locationOffset
			tok.GetNextToken().ToDouble(&y);
			m_locationOffsetY = y;

			// get z-locationOffset
			tok.GetNextToken().ToDouble(&z);
			m_locationOffsetZ = z;

			// prop to orientationOffset
			prop = prop->GetNext();

			// get value of orientationOffset
			value = prop->GetValue();

			// tokenize value
			tok.SetString(value, wxT(" "));

			// get x-orientationOffset
			tok.GetNextToken().ToDouble(&x);
			m_orientationOffsetX = x;

			// get y-orientationOffset
			tok.GetNextToken().ToDouble(&y);
			m_orientationOffsetY = y;

			// get z-orientationOffset
			tok.GetNextToken().ToDouble(&z);
			m_orientationOffsetZ = z;

			// node to radiusBottom
			node = node->GetChildren();

			// get value of radiusBottom
			node->GetNodeContent().ToDouble(&x);
			m_radiusBottom = x;

			// node to radiusTop
			node = node->GetNext();

			// get value of radiusTop
			node->GetNodeContent().ToDouble(&x);
			m_radiusTop = x;

			// node to height
			node = node->GetNext();

			// get value of height
			node->GetNodeContent().ToDouble(&x);
			m_height = x;

			// node to parent
			node = node->GetParent();

			// check if next exist, if not, leave
			if (node->GetNext() == NULL)
			{
				break;
			}
			// everything ok, set next node
			else
			{
				// set node to next group
				node = node->GetNext();
			}

#warning "INFO: Need to create an cylinder here, waiting for api."
			// primitive found
			continue;
		}

		// check if is sphere
		if (node->GetName() == wxT("sphere"))
		{
			// prop to visible
			prop = node->GetProperties();

			// get value of visible
			value = prop->GetValue();

			// check if true
			if (value == wxT("true"))
			{
				m_visible = true;
			}
			// not true -> false
			else
			{
				m_visible = false;
			}

			// prop to locationOffset
			prop = prop->GetNext();

			// get value of locationOffset
			value = prop->GetValue();

			// tokenize value
			tok.SetString(value, wxT(" "));

			// get x-locationOffset
			tok.GetNextToken().ToDouble(&x);
			m_locationOffsetX = x;

			// get y-locationOffset
			tok.GetNextToken().ToDouble(&y);
			m_locationOffsetY = y;

			// get z-locationOffset
			tok.GetNextToken().ToDouble(&z);
			m_locationOffsetZ = z;

			// prop to orientationOffset
			prop = prop->GetNext();

			// get value of orientationOffset
			value = prop->GetValue();

			// tokenize value
			tok.SetString(value, wxT(" "));

			// get x-orientationOffset
			tok.GetNextToken().ToDouble(&x);
			m_orientationOffsetX = x;

			// get y-orientationOffset
			tok.GetNextToken().ToDouble(&y);
			m_orientationOffsetY = y;

			// get z-orientationOffset
			tok.GetNextToken().ToDouble(&z);
			m_orientationOffsetZ = z;

			// node to radius
			node = node->GetChildren();

			// get value of radius
			node->GetNodeContent().ToDouble(&x);
			m_radiusBottom = x;

			// node to parent
			node = node->GetParent();

			// check if next exist, if not, leave
			if (node->GetNext() == NULL)
			{
				break;
			}
			// everything ok, set next node
			else
			{
				// set node to next group
				node = node->GetNext();
			}

#warning "INFO: Need to create an sphere here, waiting for api."
			// primitive found
			continue;
		}
	}
}

/**
 * Parses @a stream as a InputStream and loads its data.
 * @param       stream       wxInputStream to read from.
 */
void OaxImport::LoadObj(wxInputStream& stream)
{
	// create ObjectImportobject
	ObjectImport import(&stream, m_map);

	// placeholder for ObjectImport-call
	m_ptrAssembly = import.getAssembly();

	// set scale
	m_ptrAssembly->scale().setAll(m_scaleX,m_scaleY,m_scaleZ);

	// set assemly-name
	m_ptrAssembly->setName(m_name);

	// set assembly type
	m_ptrAssembly->setType(IS_OBJECT);

	// temporary pointer to get access to wrapper
	Assembly* wrapper = import.getWrapper();

	// set x-offset
	wrapper->position().setAll(m_locationOffsetX,m_locationOffsetY,m_locationOffsetZ);

	// set x-orientation
	wrapper->rotation().setAll(m_orientationOffsetX,m_orientationOffsetY,m_orientationOffsetZ);
}
