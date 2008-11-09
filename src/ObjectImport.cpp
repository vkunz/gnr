/**
 * obj file importer for reading and parsing obj-files
 * @name        ObjectImport.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/string.h>
#include <wx/sstream.h>
#include <wx/tokenzr.h>
#include <wx/txtstrm.h>

#include "MaterialLibrary.h"
#include "ObjectImport.h"
#include "GlobalDefine.h"
#include "VNT.h"
#include "Enum.h"
#include "Face.h"

#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

using std::ifstream;
using std::stringstream;
using std::string;

extern MaterialLibrary mtllib;

// ctor
ObjectImport::ObjectImport()
{
	MaterialLibrary m_matlib = MaterialLibrary();
}

ObjectImport::ObjectImport(wxString filename)
{
	// set true -> file from filesystem
	m_AsString = true;
	
	//set act pointer to null
	m_act = NULL;
	
	// asign filepath
	m_path = filename;
	
	// add filename to m_listFiles
	m_listFiles.push_back(filename);
	
	// create wxFFileInputStream to get filecontent
	wxFFileInputStream inFile(filename);
	
	// string to store filecontent
	wxString content;
	
	// create wxStringOutputStream to store filecontent into string
	wxStringOutputStream outStream(&content);
	
	// read inputstream and store data into outputstream
	inFile.Read(outStream);
	
	// read
	read(content);
}

ObjectImport::ObjectImport(wxInputStream* inStream, std::map<wxString, wxString>* mtl)
{
	// set false -> file from wxInputStream
	m_AsString = false;
	
	//set act pointer to null
	m_act = NULL;
	
	// asign map-pointer
	m_mtl = mtl;
	
	// string to store filecontent
	wxString content;
	
	// create wxStringOutputStream to store filecontent into string
	wxStringOutputStream outStringStream(&content);
	
	// read inputstream and store data into outputstream
	inStream->Read(outStringStream);
	
	// read
	read(content);
}

// dtor
ObjectImport::~ObjectImport()
{
}

void ObjectImport::LoadMtl()
{

}

void ObjectImport::ParseMtl(wxString& mtl)
{

}

std::list<wxString> ObjectImport::getFileList()
{
	return m_listFiles;
}

Assembly* ObjectImport::getAssembly()
{
	return m_root;
}

float ObjectImport::getOffsetX()
{
	return m_offsetX;
}

float ObjectImport::getOffsetY()
{
	return m_offsetY;
}

float ObjectImport::getOffsetZ()
{
	return m_offsetZ;
}

Assembly* ObjectImport::getWrapper()
{
	return m_wrapper;
}

void ObjectImport::read(wxString& content)
{
	m_xmin = m_ymin = m_zmin = std::numeric_limits<float>::max();
	m_xmax = m_ymax = m_zmax = -m_xmin;
	
	//build base wrapper assembly
	m_root = new Assembly(wxString(m_path.AfterLast('\\').BeforeFirst('.')));
	m_root->setType(IS_OBJECT);
	
	//create root assembly for object
	m_wrapper = new Assembly(wxT("wrapper"));
	m_wrapper->setType(IS_WRAPPER);
	
	//appen root assembly for object
	m_root->addPart(m_wrapper);
	m_matname = DEFAULT_IMPORT_COLOR;
	
	//add minimum one assembly, if no g or o occurs
	addAtomic("noname");
	
	// tokenize string
	wxStringTokenizer tok(content, wxT("\n"));
	
	// 1st pass, gather v, vt and vn
	while (tok.HasMoreTokens())
	{
		m_buf = string(tok.GetNextToken().mb_str());
		if (m_buf.size() < 2)
		{
			continue;
		}
		
		switch (m_buf[0])
		{
		case 'v':
			getVs();
			break;
		default:
			break;
		}
	}
	
	// 2nd pass, gather f, o, g and all the rest
	tok.SetString(content, wxT("\n"));
	while (tok.HasMoreTokens())
	{
		m_buf = string(tok.GetNextToken().mb_str());
		if (m_buf.size() < 2)
		{
			continue;
		}
		
		switch (m_buf[0])
		{
		case 'f':
			getF();
			break;
		case 'g':
			getO();
			break;
		case 'o':
			getO();
			break;
		case 'u':
			getU();
		default:
			break;
		}
	}
	
	//scale factor 1.0 instead of scale, if glScalef before glTranslatef in assembly->draw
	
	// calc x, y, z offsets
	m_offsetX = (-1.0*(m_xmax + m_xmin)/2.0);
	m_offsetY = (-1.0*(m_ymax + m_ymin)/2.0);
	m_offsetZ = (-1.0*(m_zmax + m_zmin)/2.0);
	
	m_wrapper->setX(-1.0*(m_xmax + m_xmin)/2.0);
	m_wrapper->setY(-1.0*(m_ymax + m_ymin)/2.0);
	m_wrapper->setZ(-1.0*(m_zmax + m_zmin)/2.0);
	
	// set normals
	m_wrapper->setNormals();
	
	//set real size and scale of object
	m_root->setSize((m_xmax - m_xmin),(m_ymax - m_ymin),(m_zmax - m_zmin));
	m_root->setScale(1.0,1.0,1.0);
}

void ObjectImport::getVs()
{
	char c = m_buf[1];
	m_buf = m_buf.substr(2, string::npos);
	switch (c)
	{
	case ' ':
		getV();
		break;
	case 'n':
		getVN();
		break;
	case 't':
		getVT();
		break;
	default:
		break;
	}
}

void ObjectImport::getO()
{
	string objname;
	stringstream ss(m_buf.substr(2, string::npos));
	ss >> objname;
	addAtomic(objname);
}

void ObjectImport::addAtomic(string name)
{
	m_act = new Assembly(IS_ATOMIC,wxT("part"));
	m_act->setName(name);
	m_wrapper->addPart(m_act);
	m_wrapper->setChildMaterial(m_act, m_matlib.getMaterial(m_matname));
}

void ObjectImport::minmax(float& min, float& max, float value)
{
	if (max < value)
	{
		max = value;
	}
	
	if (min > value)
	{
		min = value;
	}
}

void ObjectImport::getV()
{
	float x, y, z;
	stringstream ss(m_buf);
	ss >> x >> y >> z;
	
	minmax(m_xmin, m_xmax, x);
	minmax(m_ymin, m_ymax, y);
	minmax(m_zmin, m_zmax, z);
	
	Vertex tmp(x, y, z);
	m_vertex.push_back(tmp);
}

void ObjectImport::getVN()
{
	float x, y, z;
	stringstream ss(m_buf);
	ss >> x >> y >> z;
	
	Vertex tmp(x, y, z);
	m_normal.push_back(tmp);
}

void ObjectImport::getVT()
{
	float x, y;
	stringstream ss(m_buf);
	ss >> x >> y;
	TCoord tmp(x, y);
	m_tcoord.push_back(tmp);
}

void ObjectImport::getF()
{
	Face face;
	
	stringstream ss(m_buf.substr(2, string::npos));
	string token;
	while (ss >> token)
	{
		stringstream tmp(token);
		int v[3] = {0, 0, 0};
		
		int i = 0;
		while (!tmp.eof())
		{
			tmp >> v[i];
			if (tmp.fail() && !(tmp.bad() || tmp.eof()))
			{
				tmp.clear();
				char c;
				tmp >> c;
				if (c == '/' && i < 3)
				{
					i++;
				}
			}
		}
		v[0]--;
		v[1]--;
		v[2]--;
		
		Vertex *pv = NULL, *pn = NULL;
		TCoord *pt = NULL;
		if (v[0] != -1)
		{
			pv = new Vertex(m_vertex[v[0]]);
		}
		if (v[1] != -1)
		{
			pt = new TCoord(m_tcoord[v[1]]);
		}
		if (v[2] != -1)
		{
			pn = new Vertex(m_normal[v[2]]);
		}
		VNT vnt(pv, pn ,pt);
		face.addVNT(vnt);
	}
	
	if (face.size() >= 3)
	{
		m_act->addFace(face);
	}
}

void ObjectImport::getU()
{
	stringstream ss(m_buf.substr(6, string::npos));
	ss >> m_matname;
	m_wrapper->setChildMaterial(m_act, m_matlib.getMaterial(m_matname));
}
