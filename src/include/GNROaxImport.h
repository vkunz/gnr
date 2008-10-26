/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNROaxImport
 * @name        GNROaxImport.h
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
#include <wx/txtstrm.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>

#include "GNRAssembly.h"

/**
    @class GNROaxImport

    This class creates a GNRAssembly of oax-Files.

    Internally a GNRObjectImport is used.

    @see GNRObjectImport
*/
class GNROaxImport
{
public:
	// ctor
	GNROaxImport();
	
	// load file case: library
	GNROaxImport(wxString filename);
	
	// load stream case: opx-import
	GNROaxImport(wxInputStream& instream);
	
	// dtor
	virtual ~GNROaxImport();
	
	// functions
	GNRAssembly* getAssembly();
	
	// load stream
	void Load(wxZipInputStream& stream);
	
	// load file
	void Load(wxString& filename);
	
protected:

private:
	// attributes
	// x - y - z - scale
	float m_scalex, m_scaley, m_scalez;
	
	// x - y - z - offset
	float m_offsetx, m_offsety, m_offsetz;
	
	// x - y - z - orientation
	float m_orientationx, m_orientationy, m_orientationz;
	
	// pointer to actual zip entry
	wxZipEntry* m_ptrZipEntry;
	
	// pointer to assembly
	GNRAssembly* m_ptrAssembly;
	
	// map to store mtlfilenames and inputstream
	std::map<wxString, wxInputStream*> m_map;
	
	// vector of all entrys
	std::vector<wxZipEntry*> m_vector;
	
	// random access iterator
	std::vector<wxZipEntry*>::iterator m_vectorit;
	
	// string to store name of obj-file
	wxString m_objFilename;
	
	// functions
	// load xml
	void LoadXml(wxInputStream& stream);
	
	// load obj
	void LoadObj(wxInputStream& stream);
};

#endif // _GNROAXIMPORT_H_
