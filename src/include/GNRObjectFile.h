#ifndef _GNROBJECTFILE_H_
#define _GNROBJECTFILE_H_

#include <queue>
#include <list>
#include <wx/string.h>

#include "GNRPoint.h"
#include "GNRPoly.h"

class GNRObjectFile
{
public:
	// ctor
	GNRObjectFile();
	
	// ctor, takes filename
	GNRObjectFile(wxString filename);
	
	// method to set the filename
	void SetFilename(wxString filename);
	
	// dtor
	virtual ~GNRObjectFile();
	
protected:

private:
	// attributes
	// vector of GNRPoints
	std::vector<GNRPoint> m_VPoint;
	
	// vector of GNRPolys
	std::vector<GNRPoly> m_VPoly;
	
	// pointer to GNRPoint
	GNRPoint* m_ptrPoint;
	
	// filename to parse
	wxString m_filename;
	
	// functions
	void parse(wxString filename);
	
	// create and add new GNRPoint
	void createVertex(wxString str);
	
	// create face
	void createFace(wxString str);
};

#endif // _GNROBJECTFILE_H_
