/**
 * Vertex
 * @name        Vertex.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <math.h>

#include "Vertex.h"

/**
 * constructor of Vertex
 */
Vertex::Vertex()
{
	m_x = 0.0;
	m_y = 0.0;
	m_z = 0.0;
}

/**
 * constructor of Vertex
 * @param[in]	x	float x-position
 * @param[in]	y	float y-position
 * @param[in]	z	float z-position
 */
Vertex::Vertex(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

/**
 * copyconstructor of Vertex
 * @param[in]	v	vertex (copyconstructor)
 */
Vertex::Vertex(const Vertex& v)
{
	m_x = v.m_x;
	m_y = v.m_y;
	m_z = v.m_z;
}

/**
 * destructor of Vertex
 */
Vertex::~Vertex()
{
	// do nothing
}

/**
 * get x of vertext
 * @return		float		x-position of vertext
 */
const float Vertex::getX() const
{
	return m_x;
}

/**
 * get y of vertext
 * @return		float		y-position of vertext
 */
const float Vertex::getY() const
{
	return m_y;
}

/**
 * get z of vertext
 * @return		float		z-position of vertext
 */
const float Vertex::getZ() const
{
	return m_z;
}

/**
 * set x of vertext
 * @param[in]		x		x-position of vertext
 */
void Vertex::setX(float x)
{
	m_x = x;
}

/**
 * set y of vertext
 * @param[in]		y		y-position of vertext
 */
void Vertex::setY(float y)
{
	m_y = y;
}

/**
 * set z of vertext
 * @param[in]		z		z-position of vertext
 */
void Vertex::setZ(float z)
{
	m_z = z;
}

/**
 * set x, y and z of vertex
 * @param[in]	x	float x-position
 * @param[in]	y	float y-position
 * @param[in]	z	float z-position
 */
void Vertex::setXYZ(const float x, const float y, const float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

/**
 * get delta x to second vertex
 * @param[in]	point		pointer to vertex with x
 * @return		float		distance in x
 */
float Vertex::deltaX(Vertex* point)
{
	return m_x - point->m_x;
}

/**
 * get delta y to second vertex
 * @param[in]	point		pointer to vertex with y
 * @return		float		distance in y
 */
float Vertex::deltaY(Vertex* point)
{
	return m_y - point->m_y;
}

/**
 * get delta z to second vertex
 * @param[in]	point		pointer to vertex with z
 * @return		float		distance in z
 */
float Vertex::deltaZ(Vertex* point)
{
	return m_z - point->m_z;
}

/**
 * operator +
 * @param[in]	p2			second vertex
 * @return		Vertex		sum of both vertexes
 */
Vertex  Vertex::operator  + (const Vertex& p2) const
{
	Vertex temp(*this);
	temp.m_x += p2.m_x;
	temp.m_y += p2.m_y;
	temp.m_z += p2.m_z;
	return temp;
}

/**
 * operator -
 * @param[in]	p2			second vertex
 * @return		Vertex		difference of both vertexes
 */
Vertex  Vertex::operator  - (const Vertex& p2) const
{
	Vertex temp(*this);
	temp.m_x -= p2.m_x;
	temp.m_y -= p2.m_y;
	temp.m_z -= p2.m_z;
	return temp;
}

/**
 * operator *
 * @param[in]	r			scale value
 * @return		Vertex		product of vertex and scale
 */
Vertex  Vertex::operator  * (const float r) const
{
	Vertex temp(*this);
	temp.m_x *= r;
	temp.m_y *= r;
	temp.m_z *= r;
	return temp;
}

/**
 * operator *
 * @param[in]	p2			second vertex
 * @return		Vertex		crossproduct of both vertexes
 */
Vertex Vertex::operator  * (const Vertex& p2) const
{
	Vertex temp;
	temp.m_x = m_y*p2.m_z - m_z*p2.m_y;
	temp.m_y = m_z*p2.m_x - m_x*p2.m_z;
	temp.m_z = m_x*p2.m_y - m_y*p2.m_x;
	return temp;
}

/**
 * operator % for scalar product
 * @param[in]	p2			second vertex
 * @return		Vertex		scalar product of both vertexes
 */
Vertex Vertex::operator ^(const Vertex& p2) const
{
	Vertex temp;
	temp.m_x = m_x * p2.m_x;
	temp.m_y = m_y * p2.m_y;
	temp.m_z = m_z * p2.m_z;
	return temp;
}

/**
 * operator -=
 * @param[in]	p2			second vertex
 * @return		Vertex		difference of both vertexes
 */
Vertex& Vertex::operator -= (const Vertex& p2)
{
	m_x -= p2.m_x;
	m_y -= p2.m_y;
	m_z -= p2.m_z;
	return *this;
}

/**
 * operator +=
 * @param[in]	p2			second vertex
 * @return		Vertex		sum of both vertexes
 */
Vertex& Vertex::operator += (const Vertex& p2)
{
	m_x += p2.m_x;
	m_y += p2.m_y;
	m_z += p2.m_z;
	
	return *this;
}

/**
 * operator =
 * @param[in]	p2			second vertex
 * @return		Vertex		same as vertex 2
 */
Vertex& Vertex::operator = (const Vertex& p2)
{
	m_x = p2.m_x;
	m_y = p2.m_y;
	m_z = p2.m_z;
	
	return *this;
}

/**
 * get length of vertext
 * @return		float			length of vertex
 */
float Vertex::length()
{
	return (float)(sqrt(m_x*m_x+m_y*m_y+m_z*m_z));
}

/**
 * normalize a vertex
 * @return		bool			if normalized, return true
 */
bool Vertex::normalize()
{
	float l = length();
	if (l == 0.0f)
	{
		return false;
	}
	m_x = m_x / l;
	m_y = m_y / l;
	m_z = m_z / l;
	return true;
}

/**
 * Rotates the current vector using phi, theta, rho
 * @param[in]   	alpha   		angle to turn arround x
 * @param[in]  	beta   		angle to turn arround y
 * @param[in]   	gamma   		angle to turn arround z
 */
void Vertex::rotate(float alpha, float beta, float gamma)
{
	// convert from deg to rad
	double alpha_rad = alpha * M_PI / 180.0;
	double beta_rad = beta * M_PI / 180.0;
	double gamma_rad = gamma * M_PI / 180.0;
	
	double sa = sin(alpha_rad);
	double sb = sin(beta_rad);
	double sg = sin(gamma_rad);
	double ca = cos(alpha_rad);
	double cb = cos(beta_rad);
	double cg = cos(gamma_rad);
	
	// calculate the new values
	float newx = m_x*ca*cb + m_y*(ca*sb*sg - sa*cg) + m_z*(ca*sb*cg + sa*sg);
	float newy = m_x*sa*cb + m_y*(sa*sb*sg + ca*cg) + m_z*(sa*sb*cg - ca*sg);
	float newz = -m_x*sb + m_y*(cb*sg) + m_z*(cb*cg);
	
	// write back the new values
	m_x = newx;
	m_y = newy;
	m_z = newz;
}

/**
 * Rotates the current vector using phi, theta, rho
 * @param[in]   	angles  		Vertex with values phi, theta, rho
 */
void Vertex::rotate(const Vertex& angles)
{
	// read out angles from vertex to use rotate3f
	float phi   = angles.getX();
	float theta = angles.getY();
	float rho   = angles.getZ();
	
	rotate(phi, theta, rho);
}

/**
 * get string from vertex
 * @return		wxString		text version of vertex
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
