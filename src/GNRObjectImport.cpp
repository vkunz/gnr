#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/msgdlg.h>

#include "GNRObjectImport.h"
#include "GNRVertex.h"
#include "GNRFace.h"

#if defined(__WXDEBUG__)
#include <wx/log.h>
#endif

// ctor
GNRObjectImport::GNRObjectImport()
{
	this->isFirstPart = true;
}

// ctor
GNRObjectImport::GNRObjectImport(wxString filename)
{
#if defined(__WXDEBUG__)

	wxLogMessage(wxT("ObjectFileCreated"));
	
#endif
	this->isFirstPart = true;
	this->parse(filename);
}

// set filename
void GNRObjectImport::SetFilename(wxString filename)
{
	m_filename = filename;
}

// dtor
GNRObjectImport::~GNRObjectImport()
{
	// do nothing
}

// parse the .obj-File
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
