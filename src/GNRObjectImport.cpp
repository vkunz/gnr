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

#include "GNRObjectImport.h"
#include "GNRVNT.h"
#include "GNRFace.h"

#include <fstream>
#include <sstream>
#include <string>

using std::ifstream;
using std::stringstream;
using std::string;

GNRObjectImport::~GNRObjectImport()
{
}

GNRAssembly *GNRObjectImport::read(const string& fname)
{
	m_xmax = m_ymax = m_zmax = -3.4e38;
	m_xmin = m_ymin = m_zmin = 3.4e38;
	
	m_root = new GNRAssembly(fname);
	m_root->setIsRoot(true);
	m_act = m_root;
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
	
	float x_diff = (m_xmax - m_xmin), y_diff = (m_ymax - m_ymin), z_diff = (m_zmax - m_zmin);
	
	float max_diff = x_diff;
	if (max_diff < y_diff)
	{
		max_diff = y_diff;
	}
	if (max_diff < z_diff)
	{
		max_diff = z_diff;
	}
	
	float scale = 1.0 / max_diff;
	
	m_root->setX(-1.0*(m_xmax + m_xmin) / 2.0);
	m_root->setY(-1.0*(m_ymax + m_ymin) / 2.0);
	m_root->setZ(-1.0*(m_zmax + m_zmin) / 2.0);
	
	m_root->setScale(scale);
	
	return m_root;
}

void GNRObjectImport::getVs()
{
	char c = m_buf[1];
	m_buf = m_buf.substr(2, string::npos);
	if (c == ' ')
	{
		getV();
	}
	else if (c == 'n')
	{
		getVN();
	}
	else if (c == 't')
	{
		getVT();
	}
}

void GNRObjectImport::getO()
{
	string objname;
	stringstream ss(m_buf.substr(2, string::npos));
	ss >> objname;
	
	m_act = new GNRAssembly(objname);
	m_act->setParent(m_root);
	m_act->setIsRoot(false);
	m_root->addPart(m_act);
}

void GNRObjectImport::getV()
{
	float x, y, z;
	stringstream ss(m_buf);
	ss >> x >> y >> z;
	
	if (m_xmin > x)
	{
		m_xmin = x;
	}
	if (m_xmax < x)
	{
		m_xmax = x;
	}
	
	if (m_ymin > y)
	{
		m_ymin = y;
	}
	if (m_ymax < y)
	{
		m_ymax = y;
	}
	
	if (m_zmin > z)
	{
		m_zmin = z;
	}
	if (m_zmax < z)
	{
		m_zmax = z;
	}
	
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
					i++;
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
	m_act->addFace(face);
}

void GNRObjectImport::getU()
{
	stringstream ss(m_buf.substr(6, string::npos));
	ss >> m_matname;
}
