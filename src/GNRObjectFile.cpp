#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/msgdlg.h>

#include "GNRObjectFile.h"
#include "GNRPoint.h"
#include "GNRPoly.h"

#if defined(__WXDEBUG__)
#include <wx/log.h>
#endif

// ctor
GNRObjectFile::GNRObjectFile()
{
}

// ctor
GNRObjectFile::GNRObjectFile(wxString filename)
{
	this->parse(filename);
}

// set filename
void GNRObjectFile::SetFilename(wxString filename)
{
	m_filename = filename;
}

// dtor
GNRObjectFile::~GNRObjectFile()
{
	// do nothing
}

// parse the .obj-File
void GNRObjectFile::parse(wxString filename)
{
	wxString curLine;
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
		default:
			break;
		}
		
		// get next line
		curLine = file.GetNextLine();
	}
	
#if defined(__WXDEBUG__)
	
	// iterator to walk through m_VPoint
	std::vector<GNRPoint>::iterator it;
	
	// iterator to walk through m_VPoly
	std::vector<GNRPoly>::iterator itp;
	
	// print all GNRPoint-Objects to Log
	for (it = m_VPoint.begin(); it != m_VPoint.end(); it++)
	{
		wxLogMessage(it->ToString());
	}
	
	// print all GNRPoly-Objects to Log
	for (itp = m_VPoly.begin(); itp != m_VPoly.end(); itp++)
	{
		wxLogMessage(itp->ToString());
	}
	
#endif
}


void GNRObjectFile::createVertex(wxString str)
{
	// tokenize the current Line to get the floats
	wxStringTokenizer tok(str, wxT(" "));
	
	// temporyfy floats
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
	GNRPoint point(x, y, z);
	
	// push GNRPoint-Object to vector
	this->m_VPoint.push_back(point);
}

void GNRObjectFile::createFace(wxString str)
{
	// create new GNRPoly-Object
	GNRPoly poly;
	
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
	m_VPoly.push_back(poly);
}
