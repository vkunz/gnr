/**
 * GNRVertex
 * @name        GNRVertex.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <math.h>

#include "GNRVertex.h"

// ctor
GNRVertex::GNRVertex()
{
	m_x = 0.0;
	m_y = 0.0;
	m_z = 0.0;
}

GNRVertex::GNRVertex(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

GNRVertex::GNRVertex(const GNRVertex& v)
{
	m_x = v.m_x;
	m_y = v.m_y;
	m_z = v.m_z;
}

// dtor
GNRVertex::~GNRVertex()
{
	// do nothing
}

const float GNRVertex::getX() const
{
	return m_x;
}

const float GNRVertex::getY() const
{
	return m_y;
}

const float GNRVertex::getZ() const
{
	return m_z;
}

void GNRVertex::setX(float x)
{
	m_x = x;
}

void GNRVertex::setY(float y)
{
	m_y = y;
}

void GNRVertex::setZ(float z)
{
	m_z = z;
}

void GNRVertex::setXYZ(const float x, const float y, const float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

float GNRVertex::deltaX(GNRVertex* point)
{
	return m_x - point->m_x;
}

float GNRVertex::deltaY(GNRVertex* point)
{
	return m_y - point->m_y;
}

float GNRVertex::deltaZ(GNRVertex* point)
{
	return m_z - point->m_z;
}

// operator overload
GNRVertex  GNRVertex::operator  + (const GNRVertex& p2) const
{
	GNRVertex temp(*this);
	temp.m_x += p2.m_x;
	temp.m_y += p2.m_y;
	temp.m_z += p2.m_z;
	return temp;
}

GNRVertex  GNRVertex::operator  - (const GNRVertex& p2) const
{
	GNRVertex temp(*this);
	temp.m_x -= p2.m_x;
	temp.m_y -= p2.m_y;
	temp.m_z -= p2.m_z;
	return temp;
}

GNRVertex  GNRVertex::operator  * (const float r) const
{
	GNRVertex temp(*this);
	temp.m_x *= r;
	temp.m_y *= r;
	temp.m_z *= r;
	return temp;
}

/**
 * Calculates the Cross-Product of two Vertexes
 * @access      public
 */
GNRVertex GNRVertex::operator  * (const GNRVertex& p2) const
{
	GNRVertex temp;
	temp.m_x = m_y*p2.m_z - m_z*p2.m_y;
	temp.m_y = m_z*p2.m_x - m_x*p2.m_z;
	temp.m_z = m_x*p2.m_y - m_y*p2.m_x;
	return temp;
}

/**
 * Calculates the Scalar-Product of two Vertexes
 * @access      public
 */
GNRVertex GNRVertex::operator  ^(const GNRVertex& p2) const
{
	GNRVertex temp;
	temp.m_x = m_x * p2.m_x;
	temp.m_y = m_y * p2.m_y;
	temp.m_z = m_z * p2.m_z;
	return temp;
}

GNRVertex& GNRVertex::operator -= (const GNRVertex& p2)
{
	m_x -= p2.m_x;
	m_y -= p2.m_y;
	m_z -= p2.m_z;
	return *this;
}

GNRVertex& GNRVertex::operator += (const GNRVertex& p2)
{
	m_x += p2.m_x;
	m_y += p2.m_y;
	m_z += p2.m_z;
	
	return *this;
}

GNRVertex& GNRVertex::operator = (const GNRVertex& p2)
{
	m_x = p2.m_x;
	m_y = p2.m_y;
	m_z = p2.m_z;
	
	return *this;
}

float GNRVertex::length()
{
	return (float)(sqrt(m_x*m_x+m_y*m_y+m_z*m_z));
}

bool GNRVertex::normalize()
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
 * @param   float   angle to turn arround x
 * @param   float   angle to turn arround y
 * @param   float   angle to turn arround z
 * @access      private
 */
void GNRVertex::rotate(float alpha, float beta, float gamma)
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
 * @param   GNRVertex*  Vertex with values phi, theta, rho
 * @access      private
 */
void GNRVertex::rotate(const GNRVertex& angles)
{
	// read out angles from vertex to use rotate3f
	float phi   = angles.getX();
	float theta = angles.getY();
	float rho   = angles.getZ();
	
	rotate(phi, theta, rho);
}

wxString GNRVertex::ToString()
{
	wxString tmp;
	
	tmp << wxT("x-Wert: ");
	tmp << this->m_x;
	tmp << wxT("\ty-Wert: ");
	tmp << this->m_y;
	tmp << wxT("\tz-Wert: ");
	tmp << this->m_z;
	
	return tmp;
}
