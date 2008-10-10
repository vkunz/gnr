/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRImportFile
 * @name        GNRImportFile.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
