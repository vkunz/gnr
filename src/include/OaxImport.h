/**
 * OaxImport
 * @name        OaxImport.h
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNROAXIMPORT_H_
#define _GNROAXIMPORT_H_

#include <map>
#include <vector>
#include <wx/string.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>

#include "Assembly.h"
#include "ObjectImport.h"

/**
 * @class OaxImport
 *
 * This class creates a Assembly of oax-Files.
 *
 * Internally a ObjectImport is used.
 *
 * @see ObjectImport
 */
class OaxImport
{
public:
	// ctor
	OaxImport();
	
	// load file case: library
	OaxImport(wxString filename);
	
	// dtor
	virtual ~OaxImport();
	
	// functions
	Assembly* getAssembly();
	
	// load stream
	void Load(wxZipInputStream& stream);
	
	// load file
	void Load(wxString& filename);
	
protected:

private:
	// attributes
	// store hashes
	wxString xmlHash;
	wxString objHash;
	
	// x - y - z - scale
	float m_scaleX, m_scaleY, m_scaleZ;
	
	// x - y - z - offset
	float m_locationOffsetX, m_locationOffsetY, m_locationOffsetZ;
	
	// x - y - z - orientation
	float m_orientationOffsetX, m_orientationOffsetY, m_orientationOffsetZ;
	
	// pointer to actual zip entry
	wxZipEntry* m_ptrZipEntry;
	
	// pointer to assembly
	Assembly* m_ptrAssembly;
	
	// map to store mtlfilenames and inputstream
	std::map<wxString, wxString>* m_map;
	
	// vector of all entrys
	std::vector<wxZipEntry*> m_vector;
	
	// random access iterator
	std::vector<wxZipEntry*>::iterator m_vectorit;
	
	// string to store name of obj-file
	wxString m_objFilename;
	
	// string to store assemblyInformation -> Name
	wxString m_name;
	
	// string to store assemblyInformation -> Author
	wxString m_author;
	
	// vector of string to store assemblyInformation -> Tags
	std::vector<wxString> m_vecTags;
	
	// random access iterator
	std::vector<wxString>::iterator m_vecTagsit;
	
	// float to store cuboid width
	float m_width;
	
	// float to store cuboid/cylinder height
	float m_height;
	
	// float to store cuboid depth
	float m_depth;
	
	// float to store cylinder radiusBottom and sphere radius
	float m_radiusBottom;
	
	// float to store cylinder radiusTop
	float m_radiusTop;
	
	// bool to store visibility of primitives
	bool m_visible;
	
	// functions
	// load assembly xml
	void LoadAssemblyXml(wxInputStream& stream);
	
	// load primitives xml
	void LoadPrimitivesXml(wxInputStream& stream);
	
	// load obj
	void LoadObj(wxInputStream& stream);
};

#endif // _GNROAXIMPORT_H_
