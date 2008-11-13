#ifndef __FACE_H__
#define __FACE_H__

/**
 * Face
 * @note        [DONE]
 * @name        Face.h
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "Vertex.h"
#include "Matrix4D.h"

#include <list>
#include <map>
#include <iostream>
#include <string>

using std::list;
using std::map;
using std::pair;
using std::ostream;
using std::string;

class Face
{
public:
	typedef pair<const Vertex*, const Vertex*> m_type;
	
	Face(bool share_norm);
	virtual ~Face();
	
	// insert the vertex with its normal at the end of the vertex-list
	void push_back(const Vertex* v, const Vertex* n);
	// insert the vertex with its normal at the front of the vertex-list
	// some primitives do require it to ensure CCW winding
	void push_front(const Vertex* v, const Vertex* n);
	// draw the face
	void draw() const;
	
	const string& material() const;
	string& material();
	
	string toString(const Matrix4D& tsr, map<const Vertex*, int>& vmap, map<const Vertex*, int>& nmap, int& vc, int &nc) const;
	
private:
	// pair (Vertex, Normal)
	list<m_type> m_data;
	bool m_share_norm;
	string m_matname;
};

#endif
