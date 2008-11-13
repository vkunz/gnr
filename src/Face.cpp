/**
 * Face
 * @note        [TODO]
 * @name        Face.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "Face.h"

#include <GL/gl.h>

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::stringstream;

Face::Face(bool share_norm):
		m_share_norm(share_norm)
{
}

Face::~Face()
{
}

void Face::push_back(const Vertex* const v, const Vertex* const n)
{
	m_data.push_back(m_type(v, n));
}

void Face::push_front(const Vertex* const v, const Vertex* const n)
{
	m_data.push_front(m_type(v, n));
}


void Face::draw() const
{
	// choose the primitive type
	switch (m_data.size())
	{
	case 0:
	case 1:
		glBegin(GL_POINTS);
		break;
	case 2:
		glBegin(GL_LINES);
		break;
	case 3:
		glBegin(GL_TRIANGLES);
		break;
	case 4:
		glBegin(GL_QUADS);
		break;
	default:
		glBegin(GL_POLYGON);
	}
	// draw the whole stuff
	{
		if (m_share_norm)
		{
			(m_data.begin()->second)->draw_n();
		}
		
		for (list<m_type>::const_iterator it = m_data.begin(); it != m_data.end(); ++it)
		{
			if (!m_share_norm)
			{
				(it->second)->draw_n();
			}
			(it->first)->draw_v();
		}
	}
	glEnd();
}

const string& Face::material() const
{
	return m_matname;
}

string& Face::material()
{
	return m_matname;
}

string Face::toString(const Matrix4D& tsr, map<const Vertex*, int>& vmap, map<const Vertex*, int>& nmap, int& vc, int &nc) const
{
	stringstream ss;
	ss << "#face " << this << endl;
	if (m_data.size() > 0)
	{
		// set normal-ids and vertex-ids
		for (list<m_type>::const_iterator it = m_data.begin(); it != m_data.end(); ++it)
		{
			const Vertex* const& vert = it->first;
			const Vertex* const& norm = it->second;
			if (nmap.end() == nmap.find(norm))
			{
				// the normal wasn't used till now
				ss << "vn " << (tsr * *norm).normalize() << endl;
				nmap[norm] = nc++;
			}
			if (vmap.end() == vmap.find(vert))
			{
				// the vertex wasn't used till now
				ss << "v " << tsr * (*vert) << endl;
				vmap[vert] = vc++;
			}
		}
		
		// face has all the ids it needs, print it out
		ss << "f";
		for (list<m_type>::const_iterator it = m_data.begin(); it != m_data.end(); ++it)
		{
			const Vertex* const& vert = it->first;
			const Vertex* const& norm = it->second;
			ss << " " << vmap[vert] << "//" << nmap[norm];
		}
		ss << endl;
	}
	
	return ss.str();
}

