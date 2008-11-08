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

#include <wx/tokenzr.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>
#include <wx/zipstrm.h>

#include "GNRTreeLibraryController.h"
#include "GNRGLCamera.h"
#include "GNROaxImport.h"
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
	
	GNROpxImport(GNRTreeLibraryController* controller, GNRScene* scene, wxString filename);
	
	// dtor
	virtual ~GNROpxImport();
	
protected:

private:
	// attributes
	// string to store filename of opx
	wxString m_filename;
	
	// pointer to librarycontroller to store oax
	GNRTreeLibraryController* m_libctrl;
	
	// string to store obj-filename
	wxString m_objFilename;
	
	// pointer to GNRAssembly
	GNRAssembly* m_actual;
	
	// pointer of scene
	GNRScene* m_scene;
	
	// pointer of camera
	GNRGLCamera* m_camera;
	
	// vector of all entrys
	std::vector<wxZipEntry*> m_vector;
	
	// string to store projectInformation -> ProjectName
	wxString m_name;
	
	// string to store projectInformation -> Author
	wxString m_author;
	
	// functions
	// loads file
	void Load(wxZipInputStream& stream);
	
	// load xml
	void loadXml(wxZipInputStream& stream);
	
	// load oax
	GNRAssembly* loadOax(wxZipInputStream& stream, wxString reference);
	
	// create new assembly
	void CreateAssembly(wxZipInputStream& stream);
	
	// create new group
	void CreateGroup(wxZipInputStream& stream);
};

#endif // _GNROPXIMPORT_H_
