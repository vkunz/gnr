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

#include <string>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/msgdlg.h>

#include "GNRObjectImport.h"
#include "GNRVertex.h"
#include "GNRFace.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GNRObjectImport
 * @access      public
 */
GNRObjectImport::GNRObjectImport()
{
	this->m_ptrAssembly = new GNRAssembly();
}

/**
 * constructor of GNRObjectImport
 * @param       wxString    name of imported file
 * @access      public
 */
GNRObjectImport::GNRObjectImport(wxString filename)
{
#if defined(__ATHOS_DEBUG__)

	wxLogMessage(wxT("ObjectFileCreated"));
	
#endif
	
	this->m_ptrAssembly = new GNRAssembly();
	this->m_filename = filename;
	this->parse();
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
 * setter for importer filename
 * @param       wxString    name of imported file
 * @access      public
 */
void GNRObjectImport::SetFilename(wxString filename)
{
	m_filename = filename;
}

/**
 * return the pointer to the new GNRAssembly
 * @access      public
 */
GNRAssembly* GNRObjectImport::GetAssembly()
{
	return this->m_ptrAssembly;
}

/**
 * add a new Normal to m_VNormal
 * @param       wxString    content of line to parse
 * @acess       private
 */
void GNRObjectImport::addNormal(wxString str)
{
	// tokenize the current Line to get the floats
	wxStringTokenizer tok(str, wxT(" "));
	
	// temporary attributes
	double x, y, z;
	
	// ignore first Token
	tok.GetNextToken();
	
	// get x
	tok.GetNextToken().ToDouble(&x);
	
	// get y
	tok.GetNextToken().ToDouble(&y);
	
	// get z
	tok.GetNextToken().ToDouble(&z);
	
	// new Normal
	GNRVertex normal(x, y, z);
	
	// push new normal to m_VNormal
	this->m_VNormal.push_back(normal);
}

/**
 * add a new Texture to m_VTexture
 * @param       wxString    content of line to parse
 * @acess       private
 */
void GNRObjectImport::addTexture(wxString str)
{
	// tokenize the current Line to get the floats
	wxStringTokenizer tok(str, wxT(" "));
	
	// temporary attributes
	double x, y, z;
	
	// ignore first Token
	tok.GetNextToken();
	
	// get x
	tok.GetNextToken().ToDouble(&x);
	
	// get y
	tok.GetNextToken().ToDouble(&y);
	
	// get z
	tok.GetNextToken().ToDouble(&z);
	
	// new Texture
	GNRVertex texture(x, y, z);
	
	// push new texture to m_VTexture
	this->m_VTexture.push_back(texture);
}

/**
 * add a new Vertex to m_VVertex
 * @param       wxString    content of line to parse
 * @access      private
 */
void GNRObjectImport::addVertex(wxString str)
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
	
	// new Vertex
	GNRVertex vertex(x, y, z);
	
	// push new vertex to m_VVertex
	this->m_VVertex.push_back(vertex);
}

/**
 * create assembly
 * @param       wxString    content of line to parse
 * @access      private
 */
void GNRObjectImport::createAssembly(wxString str)
{
	// create new GNRAssemblyPart
	GNRAssembly* newAssembly = new GNRAssembly();
	
	// tokenize the current Line to get the floats
	wxStringTokenizer tok(str, wxT(" "));
	
	// temporary attribut
	wxString tmp;
	std::string convStr;
	
	// ignore first token
	tok.GetNextToken();
	
	// get object title
	tmp = tok.GetNextToken();
	
	// wxString -> std::string
	convStr = std::string(tmp.mb_str());
	
	// store object title
	newAssembly->setAssemblyTitle(convStr);
	
	// new Assembly is new child of obj-File coreAssembly
	this->m_ptrAssembly->addChildAssembly(newAssembly);
}

/**
 * create face from string
 * @param       wxString    content of line to parse
 * @access      public
 */
void GNRObjectImport::createFace(wxString str)
{
	// create new GNRPoly-Object
	GNRFace face;
	
	// temporary attribut
	long tmp;
	
	// no normal no texture Face
	GNRVertex* vertex;
	GNRVertex* normal = new GNRVertex(255.0f, 0.0f, 0.0f);
	GNRVertex* texture = new GNRVertex(255.0f, 0.0f, 0.0f);
	
	// tokenize the current Line to get the floats
	wxStringTokenizer tok(str, wxT(" "));
	
	// ignore first token
	tok.GetNextToken();
	
	// add all vertex
	while (tok.HasMoreTokens())
	{
		// get count of the first tripple
		tok.GetNextToken().ToLong(&tmp);
		
		// get address of vertex, normal, texture
		vertex = &m_VVertex[tmp - 1];
		
		// create new GNRPoint3d
		GNRPoint3d point(vertex, texture, normal);
		
		// add a new Point
		face.addGNRPoint3d(&point);
	}
	
#if defined(__ATHOS_DEBUG__)
	
	wxString msg;
	
	msg << wxT("neuer Face hier: ") << face.ToString();
	wxLogMessage(msg);
	
#endif
	
	this->m_ptrAssembly->addFace(face);
}

/**
 * parses filename for obj statements
 * @param       wxString    name of imported file
 * @access      public
 */
void GNRObjectImport::parse()
{
	// temporary attribut
	wxString curLine;
	
	// generate a new filehandler
	wxTextFile file(m_filename);
	
	file.Open();
	
#if defined(__ATHOS_DEBUG__)
	
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
			if (curLine[1] == ' ')
			{
				this->addVertex(curLine);
			}
			else if (curLine[1] == 'n')
			{
				this->addNormal(curLine);
			}
			else if (curLine[1] == 't')
			{
				this->addTexture(curLine);
			}
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
			this->createAssembly(curLine);
			break;
		default:
			break;
		}
		
		// get next line
		curLine = file.GetNextLine();
	}
	
#if defined(__ATHOS_DEBUG__)
	
	wxLogMessage(wxT("Hier fertig mit einlesen"));
	
	std::vector<GNRVertex>::iterator itv;
	std::vector<GNRVertex>::iterator itn;
	std::vector<GNRVertex>::iterator itt;
	
	wxLogMessage(wxT("Vertex-Vector: "));
	for (itv = m_VVertex.begin(); itv != m_VVertex.end(); itv++)
	{
		wxLogMessage(itv->ToString());
	}
	
	wxLogMessage(wxT("Normalen-Vector: "));
	for (itn = m_VNormal.begin(); itn != m_VNormal.end(); itn++)
	{
		wxLogMessage(itn->ToString());
	}
	
	wxLogMessage(wxT("Texturen-Vector: "));
	for (itt = m_VTexture.begin(); itt != m_VTexture.end(); itt++)
	{
		wxLogMessage(itt->ToString());
	}
	
#endif
}
