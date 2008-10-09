#ifndef _GNRIMPORTFILE_H_
#define _GNRIMPORTFILE_H_

#include "GNRVertex.h"
#include "GNRFace.h"

class GNRImportFile
{
private:

protected:

public:
	// dtor
	virtual ~GNRImportFile() { };
	
	// creates a new Assembly
	virtual void createAssembly(wxString str) = 0;
	
	// creates a new Face
	virtual void createFace(wxString str) = 0;
	
	// creates a new Vertex
	virtual void createVertex(wxString str) = 0;
	
	// parse the file
	virtual void parse(wxString filename) = 0;
};

#endif // _GNRIMPORTFILE_H_
