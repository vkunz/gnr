#ifndef _VERTEX_H_
#define _VERTEX_H_
/**
 * Vertex
 * @name        Vertex.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <cmath>

#include <wx/string.h>

#include <iostream>
using std::ostream;

class Vertex
{
public:
	// ctors
	Vertex();
	Vertex(float x, float y, float z, float w = 1.0f);
	Vertex(const Vertex& v);

	// dtor
	virtual ~Vertex();

	// default operator = with a shallow copy would suffice, but... :)
	Vertex& operator = (const Vertex& v);
	Vertex& operator += (const Vertex& v);
	Vertex& operator -= (const Vertex& v);

	Vertex operator + (const Vertex& v) const;
	Vertex operator - (const Vertex& v) const;
	// scalar * Vertex
	Vertex  operator * (const float r) const;
	// cross product
	Vertex operator * (const Vertex& v) const;
	// dot product
	float operator ^(const Vertex& v) const;

	// getter
	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;
	void getAll(float& x, float& y, float& z) const;
	void getAll(float& x, float& y, float& z, float& w) const;

	// setter
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setW(float w);
	void setAll(float x, float y, float z);
	void setAll(float x, float y, float z, float w);

	// do we need them?
//	float deltaX(const Vertex* point);
//	float deltaY(const Vertex* point);
//	float deltaZ(const Vertex* point);

	// length of the vector
	float length() const;
	// scale the vector to have the length 1.0
	bool normalize();
	// rotate the vector respective the
	// X-Axis with an angle a,
	// Y-Axis with an angle b,
	// Z-Axis with an angle g
	void rotate(float a, float b, float g);
	// do the same with angles stored in another vertex
	void rotate(const Vertex& angles);

	// put the OpenGL-Vertex
	void draw_v() const;
	// put the OpenGL-Normal
	void draw_n() const;

	// return attributes
	wxString ToString();
	// output operator <<
	friend ostream& operator<< (ostream& out, const Vertex &v);

	const static float DEG2RAD = M_PI / 180.0f;

private:
	// x-, y-, z- and w-coordinate (homogeneous 4D coordinates)
	// w is 1.0 for vertex and 0.0 for normals
	float m_x, m_y, m_z, m_w;
};

#endif
