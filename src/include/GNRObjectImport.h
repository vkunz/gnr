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
	
	// method to set the filename
	void SetFilename(wxString filename);
	
	// dtor
	virtual ~GNRObjectImport();
	
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
	
	// create and add new GNRPoint
	void createVertex(wxString str);
	
	// create face
	void createFace(wxString str);
	
	// create Part
	void createAssembly(wxString str);
};

#endif // _GNROBJECTIMPORT_H_
