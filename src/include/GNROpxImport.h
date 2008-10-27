/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNROpxImport
 * @name        GNROpxImport.h
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNROPXIMPORT_H_
#define _GNROPXIMPORT_H_

#include <map>
#include <wx/wfstream.h>

#include "GNRGLCamera.h"
#include "GNRScene.h"

/**
 * @class GNROpxImport
 *
 * This class creates a Scene of a opx-File.
 *
 * Internally a GNROaxImport is used.
 *
 * @see GNROaxImport
 */
class GNROpxImport
{
public:
	// ctor
	GNROpxImport();
	
	GNROpxImport(GNRScene* scene, wxString filename);
	
	// dtor
	virtual ~GNROpxImport();
	
	// functions
	// get pointer to scene and loads filename
	void Load(GNRScene* scene, wxString filename);
	
protected:

private:
	// attributes
	// pointer of scene
	GNRGLCamera* m_camera;
	
	// pointer to actual zip entry
	wxZipEntry* m_ptrZipEntry;
	
	// vector of all entrys
	std::vector<wxZipEntry*> m_vector;
	
	// random access iterator
	std::vector<wxZipEntry*>::iterator m_vectorit;
	
	// string to store projectInformation -> ProjectName
	wxString m_name;
	
	// string to store projectInformation -> Author
	wxString m_author;
	
	// functions
	// loads file
	void Load(wxString filename);
	
	// load xml
	void LoadXml(wxInputStream& stream);
	
	// load oax
	void LoadOax(wxInputStream& stream);
};

#endif // _GNROPXIMPORT_H_
