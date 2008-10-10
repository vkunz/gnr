/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * obj file importer for reading and parsing obj-files
 * @name        GNRObjectImport.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/msgdlg.h>

#include "GNRObjectImport.h"
#include "GNRVertex.h"
#include "GNRFace.h"

#if defined(__WXDEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GNRObjectImport
 * @access      public
 */
GNRObjectImport::GNRObjectImport()
{
	this->isFirstPart = true;
}

/**
 * constructor of GNRObjectImport
 * @param       wxString    name of imported file
 * @access      public
 */
GNRObjectImport::GNRObjectImport(wxString filename)
{
#if defined(__WXDEBUG__)

	wxLogMessage(wxT("ObjectFileCreated"));
	
#endif
	this->isFirstPart = true;
	this->parse(filename);
}

/**
 * setter for importer filename
 * @param       wxString    name of imported file
 * @access      public
 */
void GNRObjectImport::SetFilename(wxString filename)
{
	m_filename = filename;
}

/**
 * destructor of GNRObjectImport
 * @access      public
 */
GNRObjectImport::~GNRObjectImport()
{
	// do nothing
}

/**
 * parses filename for obj statements
 * @param       wxString    name of imported file
 * @access      public
 */
void GNRObjectImport::parse(wxString filename)
{
	// temporary attribut
	wxString curLine;
	
	// generate a new filehandler
	wxTextFile file(filename);
	
	file.Open();
	
#if defined(__WXDEBUG__)
	
	wxLogMessage(wxT("File opened"));
	
#endif
	
	curLine = file.GetFirstLine();
	
	while (!file.Eof())
	{
		switch ((wxChar)curLine[0])
		{
			// comment, ignore
		case '#':
			break;
		case 'v':
			this->createVertex(curLine);
			break;
		case 'f':
			this->createFace(curLine);
			break;
		case 's':
			break;
		case 'o':
			this->createAssembly(curLine);
			break;
		case 'g':
			createAssembly(curLine);
			break;
		default:
			break;
		}
		
		// get next line
		curLine = file.GetNextLine();
	}
	
	// push last Object
	//this->m_LAssemblyPart.push_back(*m_ptrAssemblyPart);
	//delete this->m_ptrAssemblyPart;
	
#if defined(__WXDEBUG__)
	
	wxLogMessage(wxT("Hier fertig mit einlesen"));
	// iterator to walk through
	//std::list<GNRAssemblyPart>::iterator it;
	
	//for(it = m_LAssemblyPart.begin(); it != m_LAssemblyPart.end(); it++)
	{
		//it->debugOutput();
	}
	
#endif
}

/**
 * create vertex from string
 * @param       wxString    content of line to parse
 * @access      public
 */
void GNRObjectImport::createVertex(wxString str)
{
	// tokenize the current Line to get the floats
	wxStringTokenizer tok(str, wxT(" "));
	
	// temporary attributes
	double x, y, z;
	
	// ignore first token
	tok.GetNextToken();
	
	// get x
	tok.GetNextToken().ToDouble(&x);
	
	// get y
	tok.GetNextToken().ToDouble(&y);
	
	// get z
	tok.GetNextToken().ToDouble(&z);
	
	// create new GNRPoint-Object
	GNRVertex point(x, y, z);
	
	// push GNRPoint-Object to vector
	//this->m_ptrAssemblyPart->addPoint(point);
}

/**
 * create face from string
 * @param       wxString    content of line to parse
 * @access      public
 */
void GNRObjectImport::createFace(wxString str)
{
	// create new GNRPoly-Object
	GNRFace poly;
	
	// temporary attribut
	long tmp;
	
	// tokenize the current Line to get the floats
	wxStringTokenizer tok(str, wxT(" "));
	
	// ignore first token
	tok.GetNextToken();
	
	// add all vertex
	while (tok.HasMoreTokens())
	{
		tok.GetNextToken().ToLong(&tmp);
		poly.addVertex(tmp);
	}
	
	// push GNRPoly-Object to vector
	//this->m_ptrAssemblyPart->addPoly(poly);
}

/**
 * create assembly
 * @param       wxString    content of line to parse
 * @access      public
 */
void GNRObjectImport::createAssembly(wxString str)
{
	if (this->isFirstPart == false)
	{
		//this->m_LAssemblyPart.push_back(*m_ptrAssemblyPart);
		//delete this->m_ptrAssemblyPart;
	}
	
	// create new GNRAssemblyPart
	//this->m_ptrAssemblyPart = new GNRAssemblyPart();
	
	// Object exist, now can be pushed
	this->isFirstPart = false;
	
	// tokenize the current Line to get the floats
	wxStringTokenizer tok(str, wxT(" "));
	
	// temporary attribut
	wxString tmp;
	
	// ignore first token
	tok.GetNextToken();
	
	tmp = tok.GetNextToken();
	
	// set title of Part
	//this->m_ptrAssemblyPart->setTitle(tmp);
}
