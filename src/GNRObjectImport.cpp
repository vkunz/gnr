/**
 * obj file importer for reading and parsing obj-files
 * @name        GNRObjectImport.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRObjectImport.h"
#include "GNRVNT.h"
#include "GNREnum.h"
#include "GNRFace.h"

#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#include "wx/wx.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

using std::ifstream;
using std::stringstream;
using std::string;

GNRObjectImport::~GNRObjectImport()
{
}

GNRAssembly *GNRObjectImport::read(const string& fname)
{
	m_xmin = m_ymin = m_zmin = std::numeric_limits<float>::max();
	m_xmax = m_ymax = m_zmax = -m_xmin;
	
	//build base wrapper assembly
	m_root = new GNRAssembly(fname);
	m_root->setType(IS_OBJECT);
	
	//create root assembly for object
	m_wrapper = new GNRAssembly("wrapper");
	m_wrapper->setType(IS_WRAPPER);
	
	//appen root assembly for object
	m_root->addPart(m_wrapper);
	m_matname = "white";
	
	// 1st pass, gather v, vt and vn
	ifstream ifs(fname.c_str());
	while (ifs.good())
	{
		getline(ifs, m_buf);
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
	ifs.clear();
	
	// 2nd pass, gather f, o, g and all the rest
	ifs.seekg(0, ifstream::beg);
	while (ifs.good())
	{
		getline(ifs, m_buf);
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
		case 'o':
			getO();
			break;
		case 'u':
			getU();
		default:
			break;
		}
	}
	ifs.close();
	
	//scale factor 1.0 instead of scale, if glScalef before glTranslatef in assembly->draw
	m_wrapper->setX(-1.0*(m_xmax + m_xmin)/2.0);
	m_wrapper->setY(-1.0*(m_ymax + m_ymin)/2.0);
	m_wrapper->setZ(-1.0*(m_zmax + m_zmin)/2.0);
	m_wrapper->setNormals();
	
	//set real size and scale of object
	m_root->setSize((m_xmax - m_xmin),(m_ymax - m_ymin),(m_zmax - m_zmin));
	m_root->setScale(1.0,1.0,1.0);
	m_root->putOnGround();
	
	m_root->debugInfo();
	
	return m_root;
}

void GNRObjectImport::getVs()
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

void GNRObjectImport::getO()
{
	string objname;
	stringstream ss(m_buf.substr(2, string::npos));
	ss >> objname;
	
	m_act = new GNRAssembly(m_wrapper,objname);
	m_act->setType(IS_ATOMIC);
	m_wrapper->addPart(m_act);
}

void GNRObjectImport::minmax(float& min,float& max,float value)
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

void GNRObjectImport::getV()
{
	float x, y, z;
	stringstream ss(m_buf);
	ss >> x >> y >> z;
	
	minmax(m_xmin, m_xmax, x);
	minmax(m_ymin, m_ymax, y);
	minmax(m_zmin, m_zmax, z);
	
	GNRVertex tmp(x, y, z);
	m_vertex.push_back(tmp);
}

void GNRObjectImport::getVN()
{
	float x, y, z;
	stringstream ss(m_buf);
	ss >> x >> y >> z;
	
	GNRVertex tmp(x, y, z);
	m_normal.push_back(tmp);
}


void GNRObjectImport::getVT()
{
	float x, y;
	stringstream ss(m_buf);
	ss >> x >> y;
	GNRTCoord tmp(x, y);
	m_tcoord.push_back(tmp);
}

void GNRObjectImport::getF()
{
	GNRFace face(m_matname);
	
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
		
		GNRVertex *pv = NULL, *pn = NULL;
		GNRTCoord *pt = NULL;
		if (v[0] != -1)
		{
			pv = new GNRVertex(m_vertex[v[0]]);
		}
		if (v[1] != -1)
		{
			pt = new GNRTCoord(m_tcoord[v[1]]);
		}
		if (v[2] != -1)
		{
			pn = new GNRVertex(m_normal[v[2]]);
		}
		GNRVNT vnt(pv, pn ,pt);
		face.addVNT(vnt);
	}
	if (face.size() >= 3)
		m_act->addFace(face);
}

void GNRObjectImport::getU()
{
	stringstream ss(m_buf.substr(6, string::npos));
	ss >> m_matname;
}
