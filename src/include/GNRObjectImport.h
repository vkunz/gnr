/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * obj file importer for reading and parsing obj-files
 * @name        GNRObjectImport.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNROBJECTIMPORT_H_
#define _GNROBJECTIMPORT_H_

#include <queue>
#include <list>
#include <wx/string.h>

#include "GNRAssembly.h"
#include "GNRImportFile.h"
#include "GNRVertex.h"
#include "GNRFace.h"

class GNRObjectImport : public GNRImportFile
{
public:
	// ctor
	GNRObjectImport();
	
	// ctor, takes filename
	GNRObjectImport(wxString filename);
	
	// dtor
	virtual ~GNRObjectImport();
	
	// functions
	// method to set the filename
	void SetFilename(wxString filename);
	
	// method to return the pointer of the new obj-File Assembly
	GNRAssembly* GetAssembly();
	
protected:

private:
	// attributes
	
	// list of GNRAssembly
	std::list<GNRAssembly> m_LAssembly;
	
	// stores data if first part
	bool isFirstPart;
	
	// pointer to GNRAssembly
	GNRAssembly* m_ptrAssembly;
	
	// filename to parse
	wxString m_filename;
	
	// functions
	// parse the file
	void parse(wxString filename);
	
	// create Vertex
	void createVertex(wxString str);
	
	// create Face
	void createFace(wxString str);
	
	// create Assembly
	void createAssembly(wxString str);
	
	// create Normal
	void createNormal(wxString str);
};

#endif // _GNROBJECTIMPORT_H_
