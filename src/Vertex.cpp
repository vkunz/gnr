/**
 * Vertex
 * @name		Vertex.cpp
 * @date		2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <limits>
#include <iomanip>
#include <GL/gl.h>

#include "Vertex.h"

/**
 * constructor of Vertex
 */
Vertex::Vertex():
		m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(1.0f)
{
}

/**
 * constructor of Vertex
 * @param[in]		x	float x-position
 * @param[in]		y	float y-position
 * @param[in]		z	float z-position
 * @param[in]		w	float w-position
 */
Vertex::Vertex(float x, float y, float z, float w):
		m_x(x), m_y(y), m_z(z), m_w(w)
{
}

/**
 * copy-constructor of Vertex
 * @param[in]		v	vertex (copy-constructor)
 */
Vertex::Vertex(const Vertex& v):
		m_x(v.m_x), m_y(v.m_y), m_z(v.m_z)
{
	// we do not copy the w-coordinate by default
}

/**
 * destructor of Vertex
 */
Vertex::~Vertex()
{
	// do nothing
}

/**
 * get x of vertex
 * @return		float x-coordinate of vertex
 */
float Vertex::getX() const
{
	return m_x;
}

/**
 * get y of vertex
 * @return		float y-position of vertex
 */
float Vertex::getY() const
{
	return m_y;
}

/**
 * get z of vertex
 * @return		float z-position of vertex
 */
float Vertex::getZ() const
{
	return m_z;
}

/**
 * get w of vertex
 * @return		float w-position of vertex
 */
float Vertex::getW() const
{
	return m_w;
}

/**
 * get x, y and z of vertex
 * @param[out]		x 	float x-position of vertex
 * @param[out]		y 	float y-position of vertex
 * @param[out]		z 	float z-position of vertex
 */
void Vertex::getAll(float& x, float& y, float& z) const
{
	x = m_x;
	y = m_y;
	z = m_z;
}

/**
 * get x, y, z and w of vertex
 * @param[out]		x	float x-position of vertex
 * @param[out]		y 	float y-position of vertex
 * @param[out]		z 	float z-position of vertex
 * @param[out]		w 	float w-position of vertex
 */
void Vertex::getAll(float& x, float& y, float& z, float& w) const
{
	x = m_x;
	y = m_y;
	z = m_z;
	w = m_w;
}

/**
 * set x of vertex
 * @param[in]		x	float x-position of vertex
 */
void Vertex::setX(float x)
{
	m_x = x;
}

/**
 * set y of vertex
 * @param[in]		y	float y-position of vertex
 */
void Vertex::setY(float y)
{
	m_y = y;
}

/**
 * set z of vertex
 * @param[in]		z	float z-position of vertex
 */
void Vertex::setZ(float z)
{
	m_z = z;
}

/**
 * set w of vertex
 * @param[in]		w	float w-position of vertex
 */
void Vertex::setW(float w)
{
	m_w = w;
}

/**
 * set x and y of vertex
 * @param[in]		x	float x-position of vertex
 * @param[in]		y	float y-position of vertex
 */
void Vertex::setXY(float x, float y)
{
	m_x = x;
	m_y = y;
}

/**
 * set x and z of vertex
 * @param[in]		x	float x-position of vertex
 * @param[in]		y	float z-position of vertex
 */
void Vertex::setXZ(float x, float z)
{
	m_x = x;
	m_z = z;
}


/**
 * set x, y and z of vertex
 * @param[in]		x	float x-position
 * @param[in]		y	float y-position
 * @param[in]		z	float z-position
 */
void Vertex::setAll(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

/**
 * set x, y, z and w of vertex
 * @param[in]		x	float x-position
 * @param[in]		y	float y-position
 * @param[in]		z	float z-position
 * @param[in]		w	float w-position
 */
void Vertex::setAll(float x, float y, float z, float w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}

// * get delta x to second vertex
// * @param[in]	point		pointer to vertex with x
// * @return		float		distance in x
//
//float Vertex::deltaX(Vertex* point)
//{
//	return m_x - point->m_x;
//}


// * get delta y to second vertex
// * @param[in]	point		pointer to vertex with y
// * @return		float		distance in y
//float Vertex::deltaY(Vertex* point)
//{
//	return m_y - point->m_y;
//}


// * get delta z to second vertex
// * @param[in]	point		pointer to vertex with z
// * @return		float		distance in z
//float Vertex::deltaZ(Vertex* point)
//{
//	return m_z - point->m_z;
//}

/**
 * operator +
 * @param[in]		v		second vertex
 * @return		Vertex		sum of both vertices
 */
Vertex Vertex::operator + (const Vertex& v) const
{
	Vertex temp(*this);
	temp += v;
	return temp;
}

/**
 * operator -
 * @param[in]		v		second vertex
 * @return		Vertex		difference of both vertices
 */
Vertex Vertex::operator - (const Vertex& v) const
{
	Vertex temp(*this);
	temp -= v;
	return temp;
}

/**
 * operator *
 * @param[in]		r		scale value
 * @return		Vertex		with factor r scaled vertex
 */
Vertex Vertex::operator * (float r) const
{
	Vertex temp(*this);
	temp.m_x *= r;
	temp.m_y *= r;
	temp.m_z *= r;

	return temp;
}

/**
 * operator *
 * @param[in]		v		second vertex
 * @return		Vertex		crossproduct of vertices *this and v
 */
Vertex Vertex::operator * (const Vertex& v) const
{
	Vertex tmp
	(
	    m_y * v.m_z  -  m_z * v.m_y,
	    m_z * v.m_x  -  m_x * v.m_z,
	    m_x * v.m_y  -  m_y * v.m_x
	);

	return tmp;
}

/**
 * operator ^ for dot product
 * @param[in]		v		second vertex
 * @return		float		dot product of both vertices
 */
float Vertex::operator ^(const Vertex& v) const
{
	return m_x * v.m_x  +  m_y * v.m_y  + m_z * v.m_z;
}

/**
 * operator -=
 * @param[in]		v		second vertex
 * @return		Vertex&		difference of both vertices
 */
Vertex& Vertex::operator -= (const Vertex& v)
{
	m_x -= v.m_x;
	m_y -= v.m_y;
	m_z -= v.m_z;
	return *this;
}

/**
 * operator +=
 * @param[in]		v		second vertex
 * @return		Vertex&		sum of both vertices
 */
Vertex& Vertex::operator += (const Vertex& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;

	return *this;
}

/**
 * operator =
 * @param[in]		v		second vertex
 * @return		Vertex&		same as vertex 2
 */
Vertex& Vertex::operator = (const Vertex& v)
{
	m_x = v.m_x;
	m_y = v.m_y;
	m_z = v.m_z;
	m_w = v.m_w;

	return *this;
}

/**
 * get length of vertex
 * @return		float	length of vertex
 */
float Vertex::length() const
{
	return sqrt(m_x * m_x  +  m_y * m_y  +  m_z * m_z);
}

/**
 * normalize a vertex
 * @return		Vertex& 	Vertex with the same direction, scaled to the norm 1.0
 */
Vertex& Vertex::normalize()
{
	float len = length();

	if (fabs(len) > 2.0f * std::numeric_limits<float>::epsilon())
	{
		m_x = m_x / len;
		m_y = m_y / len;
		m_z = m_z / len;
	}
	return *this;
}

/**
 * Rotates the current vector using phi, theta, rho
 * @param[in]		float	angle to turn arround x
 * @param[in]		float	angle to turn arround y
 * @param[in]		float	angle to turn arround z
 */
void Vertex::rotate(float alpha, float beta, float gamma)
{
	// convert from deg to rad
	double
	alpha_rad = alpha * DEG2RAD,
	            beta_rad = beta * DEG2RAD,
	                       gamma_rad = gamma * DEG2RAD;

	double
	sa = sin(alpha_rad), ca = cos(alpha_rad),
	                          sb = sin(beta_rad),  cb = cos(beta_rad),
	                                                    sg = sin(gamma_rad), cg = cos(gamma_rad);

	// calculate the new values
	float
	newx = m_x * ca * cb + m_y * (ca * sb * sg  -  sa * cg)  +  m_z * (ca * sb * cg  +  sa * sg),
	       newy =   m_x * sa * cb + m_y * (sa * sb * sg  +  ca * cg)  +  m_z * (sa * sb * cg - ca * sg),
	                newz =  -m_x * sb  +  m_y * cb * sg  +  m_z * cb * cg;

	// write back the new values
	m_x = newx;
	m_y = newy;
	m_z = newz;
}

/**
 * Rotates the current vector using phi, theta, rho
 * @param[in]		Vertex		vertex with values phi, theta, rho
 */
void Vertex::rotate(const Vertex& angles)
{
	rotate(angles.getX(), angles.getY(), angles.getZ());
}

/**
 * get string from vertex
 * @return		wxString	text version of vertex
 */
wxString Vertex::ToString()
{
	wxString tmp;

	tmp << wxT("x: ");
	tmp << this->m_x;
	tmp << wxT("\ty: ");
	tmp << this->m_y;
	tmp << wxT("\tz: ");
	tmp << this->m_z;

	return tmp;
}

/**
 * draw the vertex
 */
void Vertex::draw_v() const
{
	glVertex3f(m_x, m_y, m_z);
}

/**
 * draw the normal
 */
void Vertex::draw_n() const
{
	glNormal3f(m_x, m_y, m_z);
}

/**
 * dump the vertex into the output stream
 * @return		ostream		text dump of vertex
 */
std::ostream& operator<<(std::ostream& out, const Vertex& v)
{
	out << std::setprecision(8) << std::fixed << v.m_x << " " << v.m_y << " " << v.m_z;
	return out;
}

