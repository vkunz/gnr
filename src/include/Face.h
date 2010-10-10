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

#ifndef __FACE_H__
#define __FACE_H__

#include <list>
#include <map>
#include <iostream>
#include <string>

class Matrix4D;
class Vertex;

class Face
{
public:
	typedef std::pair<const Vertex*, const Vertex*> m_type;

	Face(bool share_norm);
	virtual ~Face();

	// insert the vertex with its normal at the end of the vertex-list
	void push_back(const Vertex* v, const Vertex* n);
	// insert the vertex with its normal at the front of the vertex-list
	// some primitives do require it to ensure CCW winding
	void push_front(const Vertex* v, const Vertex* n);
	// draw the face
	void draw() const;

	const std::string& material() const;
	std::string& material();

	std::string toString(const Matrix4D& tsr, std::map<const Vertex*, int>& vmap, std::map<const Vertex*, int>& nmap, int& vc, int &nc) const;

private:
	// pair (Vertex, Normal)
	std::list<m_type> m_data;
	bool m_share_norm;
	std::string m_matname;
};

#endif
