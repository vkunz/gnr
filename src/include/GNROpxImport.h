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
	
	GNROpxImport(GNRScene* scene, wxString filename);
	
	// dtor
	virtual ~GNROpxImport();
	
	// functions
	// get pointer to scene and loads filename
	void Load(GNRScene* scene, wxString filename);
	
protected:

private:
	// attributes
	// string to store obj-filename
	wxString m_objFilename;
	
	// pointer to GNRAssembly
	GNRAssembly* m_actual;
	
	// pointer to oax-importer
	GNROaxImport* m_oaxImport;
	
	// pointer to wxFFileInputStream
	wxFFileInputStream* m_inFile;
	
	// pointer to wxZipInputStream
	wxZipInputStream* m_inZip;
	
	// pointer of scene
	GNRScene* m_scene;
	
	// pointer of camera
	GNRGLCamera* m_camera;
	
	// pointer to actual zip entry
	wxZipEntry* m_ptrZipEntry;
	
	// create pointer to xmlnode
	wxXmlNode* m_node;
	
	// create pointer to xmlproperty
	wxXmlProperty* m_prop;
	
	// create wxString to store propertyvalues
	wxString m_value;
	
	// temporary attribute tokenizer
	wxStringTokenizer m_tok;
	
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
	GNRAssembly* LoadOax(wxZipInputStream& stream);
	
	// create new assembly
	void CreateAssembly(wxZipInputStream& stream);
	
	// create new group
	void CreateGroup(wxZipInputStream& stream);
};

#endif // _GNROPXIMPORT_H_
