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
	// initialize to zero
	m_x = m_y = m_z = 0.0f;
}

GNRVertex::GNRVertex(float x, float y, float z)
{
	this->m_x = x;
	this->m_y = y;
	this->m_z = z;
}

float GNRVertex::getX()
{
	return this->m_x;
}

float GNRVertex::getY()
{
	return this->m_y;
}

float GNRVertex::getZ()
{
	return this->m_z;
}

void GNRVertex::setX(float x)
{
	this->m_x = x;
}

void GNRVertex::setY(float y)
{
	this->m_y = y;
}

void GNRVertex::setZ(float z)
{
	this->m_z = z;
}

float GNRVertex::deltaX(GNRVertex* point)
{
	return (float)(this->m_x - point->m_x);
}

float GNRVertex::deltaY(GNRVertex* point)
{
	return (float)(this->m_y - point->m_y);
}

float GNRVertex::deltaZ(GNRVertex* point)
{
	return (float)(this->m_z - point->m_z);
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

// dtor
GNRVertex::~GNRVertex()
{
	// do nothing
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
