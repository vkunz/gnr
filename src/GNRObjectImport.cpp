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
	m_ptrAssembly = new GNRAssembly();
	m_ptrAssemblyActual = m_ptrAssembly;
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
	
	m_ptrAssembly = new GNRAssembly();
	m_ptrAssemblyActual = m_ptrAssembly;
	m_filename = filename;
	parse();
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
	return m_ptrAssembly;
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
	m_VNormal.push_back(normal);
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
	m_VTexture.push_back(texture);
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
	m_VVertex.push_back(vertex);
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
	m_ptrAssembly->addChildAssembly(newAssembly);
	
	// get address of new GNRAssembly to store faces in
	m_ptrAssemblyActual = newAssembly;
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
	wxString strFace;
	wxString strVertex;
	wxString strNormal;
	wxString strTexture;
	
	// no normal no texture Face
	GNRVertex* ptrVertex;
	GNRVertex* ptrNormal;
	GNRVertex* ptrTexture;
	
	// vertex normals and texture vertices are optional
	GNRVertex* ptrNormalTemporary = new GNRVertex(255.0f, 0.0f, 0.0f);
	GNRVertex* ptrTextureTemporary = new GNRVertex(255.0f, 0.0f, 0.0f);
	
	// tokenize the current Line to get all face triplets
	wxStringTokenizer tok(str, wxT(" "));
	
	// ignore first token
	tok.GetNextToken();
	
	// analyze every triple
	while (tok.HasMoreTokens())
	{
		// temporary string
		strFace = tok.GetNextToken();
		
		// get int of vertex as string
		strVertex = strFace.BeforeFirst('/');
		
		// get string after first slash if available -> found vertex
		strFace = strFace.AfterFirst('/');
		
		// get int of texture as string
		strTexture = strFace.BeforeFirst('/');
		
		// get string after second slash if available -> found texture
		strFace = strFace.AfterFirst('/');
		
		// get int of normal as string
		strNormal = strFace.BeforeFirst('/');
		
		// strVertex -> long
		strVertex.ToLong(&tmp);
		
		// get address of vertex
		ptrVertex = &m_VVertex[tmp - 1];
		
		// strNormal -> long
		strNormal.ToLong(&tmp);
		
		// get address of normal
		ptrNormal = &m_VNormal[tmp - 1];
		
		// strTexture -> long
		strTexture.ToLong(&tmp);
		
		// get address of texture
		ptrTexture = &m_VTexture[tmp - 1];
		
		// case only vertex
		if (strNormal == wxT("") && strTexture == wxT(""))
		{
			// create GNRPoint3d
			GNRPoint3d point(ptrVertex, ptrTextureTemporary, ptrNormalTemporary);
			
			// add a new Point
			face.addGNRPoint3d(&point);
		}
		// case vertex and texture
		else if (strNormal == wxT(""))
		{
			// create GNRPoint3d
			GNRPoint3d point(ptrVertex, ptrTexture, ptrNormalTemporary);
			
			// add a new Point
			face.addGNRPoint3d(&point);
		}
		// case vertex and normal
		else if (strTexture == wxT(""))
		{
			// create GNRPoint3d
			GNRPoint3d point(ptrVertex, ptrTextureTemporary, ptrNormal);
			
			// add a new Point
			face.addGNRPoint3d(&point);
		}
		// case vertex, texture and normal
		else
		{
			// create GNRPoint3d
			GNRPoint3d  point(ptrVertex, ptrTexture, ptrNormal);
			
			// add a new Point
			face.addGNRPoint3d(&point);
		}
	}
	
	// add new Face to actual GNRAssembly
	m_ptrAssemblyActual->addFace(face);
}

void GNRObjectImport::splitVertexNormalTexture(wxString str)
{
	switch ((wxChar)str[1])
	{
		// found vertex
	case ' ':
		addVertex(str);
		break;
		// found normal
	case 'n':
		addNormal(str);
		break;
		// found texture
	case 't':
		addTexture(str);
		break;
	}
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
			splitVertexNormalTexture(curLine);
			break;
			// found face
		case 'f':
			createFace(curLine);
			break;
			// found new object
		case 'o':
			createAssembly(curLine);
			break;
			// found new group/object
		case 'g':
			createAssembly(curLine);
			break;
		default:
			break;
		}
		
		// get next line
		curLine = file.GetNextLine();
	}
	
#if defined(__ATHOS_DEBUG__)
	
	wxLogMessage(wxT("Hier fertig mit einlesen"));
	
#endif
}
