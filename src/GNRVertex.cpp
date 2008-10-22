/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRVertex
 * @name        GNRVertex.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
