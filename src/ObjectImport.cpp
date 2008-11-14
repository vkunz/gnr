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

/**
 * generic constructor of ObjectImport initializes library
 */
ObjectImport::ObjectImport()
{
}

/**
 * constructor of ObjectImport by name
 * @param[in]       filename           filename of obj to import
 */
ObjectImport::ObjectImport(const wxString& filename)
{
	// set true -> file from filesystem
	m_from_FS = true;
	
	file.Assign(filename);
	
	//set act pointer to null
	m_act_part = NULL;
	
	// assign filepath
	m_path = file.GetPath();
	
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
	
	// parse
	parse(content);
}

/**
 * constructor of ObjectImport by stream and files map
 * @param[in]       inStream           wxInputStream pointer to input stream
 * @param[in]       mtl                map of material filenames and content
 */
ObjectImport::ObjectImport(wxInputStream* inStream, std::map<wxString, wxString>* mtl)
{
	// set false -> file from wxInputStream
	m_from_FS = false;
	
	//set act pointer to null
	m_act_part = NULL;
	
	// assign map-pointer
	m_mtl = mtl;
	
	// string to store filecontent
	wxString content;
	
	// create wxStringOutputStream to store filecontent into string
	wxStringOutputStream outStringStream(&content);
	
	// read inputstream and store data into outputstream
	inStream->Read(outStringStream);
	
	// read
	parse(content);
}

/**
 * destructor of ObjectImport
 */
ObjectImport::~ObjectImport()
{
}

/**
 * get list of files in file-list
 * @return       list<wxString>         list of filenames
 */
std::list<wxString> ObjectImport::getFileList()
{
	return m_listFiles;
}

/**
 * get the built assembly (root)
 * @return       Assembly*         get pointer to the built assembly
 */
Assembly* ObjectImport::getAssembly()
{
	return m_root;
}

/**
 * get offset
 * @return       float
 */
const Vertex& ObjectImport::offset() const
{
	return m_offset;
}

/**
 * get pointer to wrapper
 * @return       Assembly*         pointer to wrapper
 */
Assembly* ObjectImport::getWrapper()
{
	return m_wrapper;
}

/**
 * parse content and create assembly (IS_OBJECT) from
 * @param[in]       content         wxString content of file
 */
void ObjectImport::parse(const wxString& content)
{
	float maxf = std::numeric_limits<float>::max();
	m_min = Vertex(maxf, maxf, maxf);
	m_max = Vertex(-maxf, -maxf, -maxf);
	
	//build base wrapper assembly
	m_root = new Assembly(wxString(file.GetName()));
	m_root->setType(IS_OBJECT);
	
	//create root assembly for object
	m_wrapper = new Assembly(wxT("wrapper"));
	m_wrapper->setType(IS_WRAPPER);
	
	//appen root assembly for object
	m_root->addPart(m_wrapper);
	m_act_material = DEFAULT_IMPORT_COLOR;
	
	//add minimum one assembly, if no g or o occurs
	addAtomic("noname");
	
	// tokenize string
	wxStringTokenizer tok(content, wxT("\n"));
	
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
		case 'v':
		case 'V':
			// v or vn  ...
			getVs();
			break;
		case 'f':
		case 'F':
			// f ...
			getF();
			break;
		case 'g':
		case 'o':
		case 'G':
		case 'O':
			// o ...
			getO();
			break;
		case 'u':
		case 'U':
			// usemtl ...
			getU();
			break;
		case 'm':
		case 'M':
			// mtllib ...
			getM();
			break;
		default:
			break;
		}
	}
	
	m_offset = (m_max + m_min) * -0.5f;
	m_wrapper->position() = m_offset;
	
	//set real size and scale of object
	m_root->dimension() = m_max - m_min;
	m_root->scale().setAll(1.0f, 1.0f, 1.0f);
}

/**
 * get a vertex or a normal from the obj
 */
void ObjectImport::getVs()
{
	stringstream ss(m_buf);
	string tmp;
	
	ss >> tmp;
	m_buf.erase(0, 2);
	if (tmp == "v" || tmp == "V")
	{
		getV();
	}
	else if (tmp == "vn" || tmp == "VN")
	{
		getVN();
	}
}

/**
 * get a vertex
 */
void ObjectImport::getV()
{
	float x, y, z;
	stringstream ss(m_buf);
	ss >> x >> y >> z;
	
	minmax(x, y, z);
	
	m_wrapper->m_vertex.push_back(new Vertex(x, y, z));
}

/**
 * get a normal
 */
void ObjectImport::getVN()
{
	m_buf.erase(0, 1);
	stringstream ss(m_buf);
	
	float x, y, z;
	ss >> x >> y >> z;
	
	m_wrapper->m_normal.push_back(new Vertex(x, y, z, 0.0f));
}

/**
 * get an object in obj file
 */
void ObjectImport::getO()
{
	stringstream ss(m_buf);
	string tmp;
	
	ss >> tmp;
	if (tmp == "g" || tmp == "o" || tmp == "G" || tmp == "G")
	{
		tmp.erase();
		ss >> tmp;
		addAtomic(tmp);
	}
}

/**
 * add an atomic part to object
 * @param[in]      name        string name of part
 */
void ObjectImport::addAtomic(const string& name)
{
	m_act_part = new Assembly(IS_ATOMIC, wxT("part"));
	m_act_part->setName(name);
	m_wrapper->addPart(m_act_part);
	m_act_part->m_matname = m_act_material;
//	m_wrapper->setChildMaterial(m_act, m_matlib.getMaterial(m_matname));
}

/**
 * update min- and max- ranges
 * @param[in]       x		float new x to compare
 * @param[in]       y		float new y to compare
 * @param[in]       z		float new z to compare
 */
void ObjectImport::minmax(float x, float y, float z)
{
	if (x > m_max.getX())
	{
		m_max.setX(x);
	}
	if (x < m_min.getX())
	{
		m_min.setX(x);
	}
	
	if (y > m_max.getY())
	{
		m_max.setY(y);
	}
	if (y < m_min.getY())
	{
		m_min.setY(y);
	}
	
	if (z > m_max.getZ())
	{
		m_max.setZ(z);
	}
	if (z < m_min.getZ())
	{
		m_min.setZ(z);
	}
}

/**
 * get a face
 */
void ObjectImport::getF()
{
	stringstream ss(m_buf);
	string tmp;
	
	ss >> tmp;
	if (tmp == "f" || tmp == "F")
	{
		Face* face = getFace(ss);
		if (face != NULL)
		{
			face->material() = m_act_material;
			m_act_part->m_face.push_back(face);
		}
	}
}

/**
 * get a use material from obj file
 */
void ObjectImport::getU()
{
	stringstream ss(m_buf);
	string tmp;
	
	ss >> tmp;
	if (tmp == "usemtl" || tmp == "USEMTL")
	{
		ss >> m_act_material;
		m_act_part->m_matname = m_act_material;
	}
}
/**
 * get the name of the materiallib
 */
void ObjectImport::getM()
{
	stringstream ss(m_buf);
	string tmp;
	
	ss >> tmp;
	if (tmp == "mtllib" || tmp == "MTLLIB")
	{
		ss >> tmp;
		wxString tmp_buf(wxString(tmp.c_str(),wxConvUTF8));
		
		if (m_from_FS)
		{
			MaterialLibrary::getInstance()->import(tmp);
			m_path << wxFileName::GetPathSeparator() << tmp_buf;
			
			if (wxFileExists(m_path))
			{
				m_listFiles.push_back(m_path);
			}
		}
		else
		{
			std::map<wxString, wxString>::const_iterator it =  m_mtl->find(tmp_buf);
			if (it != m_mtl->end())
			{
				string tmp2(it->second.mb_str());
				MaterialLibrary::getInstance()->import(tmp2);
			}
			else
			{
				// named mtl not found
			}
		}
	}
}

/**
 * create a face from a stream
 * @param[in]		is	inputstream
 * @return		Face*	pointer to the new face
 */
Face* ObjectImport::getFace(istream& is)
{
	Face *face = NULL;
	
	bool normals_given = true;
	
	vector<pair<int, int> > vn;
	
	string token;
	while (is >> token)
	{
		stringstream tmp(token);
		
		int v[3] = {0, 0, 0};
		int i = 0;
		while (!tmp.eof() && i < 3)
		{
			// try to get the next int
			tmp >> v[i];
			// if failed, check if it was a '/'
			if (tmp.fail() && !(tmp.bad() || tmp.eof()))
			{
				// unset fail-bit
				tmp.clear();
				char c;
				tmp >> c;
				if (c == '/' && i < 3)
				{
					++i;
				}
			}
		}
		v[0]--;
		v[1]--;
		v[2]--;
		
		if (v[2] == -1)
		{
			normals_given = false;
		}
		vn.push_back(pair<int, int>(v[0], v[2]));
	}
	
	if (vn.size() > 2)
	{
		bool shared_normal = !normals_given;
		if (normals_given)
		{
			int normal_id = vn.begin()->second;
			if (normal_id == -1)
			{
				shared_normal = false;
			}
			for (vector<pair<int, int> >::iterator it = vn.begin()+1; it != vn.end() && shared_normal; ++it)
			{
				if (normal_id != it->second)
				{
					shared_normal = false;
				}
			}
		}
		
		face = new Face(shared_normal);
		
		if (!normals_given)
		{
			Vertex* norm = new Vertex;
			// its a normal => 0.0f
			norm->setW(0.0f);
			
			Vertex v0 = *m_wrapper->m_vertex[vn[0].first];
			Vertex v1 = *m_wrapper->m_vertex[vn[1].first];
			Vertex v2 = *m_wrapper->m_vertex[vn[2].first];
			
			*norm = ((v1-v0)*(v2-v1)).normalize();
			m_wrapper->m_normal.push_back(norm);
			
			for (unsigned i = 0; i < vn.size(); ++i)
			{
				const pair<int, int>& ref = vn[i];
				face->push_back(m_wrapper->m_vertex[ref.first], norm);
			}
		}
		else
		{
			for (unsigned i = 0; i < vn.size(); ++i)
			{
				const pair<int, int>& ref = vn[i];
				if (!shared_normal)
				{
					face->push_back(m_wrapper->m_vertex[ref.first], m_wrapper->m_normal[ref.second]);
				}
				else
				{
					face->push_back(m_wrapper->m_vertex[ref.first], m_wrapper->m_normal[vn[0].second]);
				}
			}
		}
	}
	
	return face;
}

