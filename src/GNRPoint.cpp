#include "GNRPoint.h"

// ctor
GNRPoint::GNRPoint()
{
	// initialize to zero
	m_x = m_y = m_z = 0.0f;
}

GNRPoint::GNRPoint(float x, float y, float z)
{
	this->m_x = x;
	this->m_y = y;
	this->m_z = z;
}

float GNRPoint::getX()
{
	return this->m_x;
}

float GNRPoint::getY()
{
	return this->m_y;
}

float GNRPoint::getZ()
{
	return this->m_z;
}

void GNRPoint::setX(float x)
{
	this->m_x = x;
}

void GNRPoint::setY(float y)
{
	this->m_y = y;
}

void GNRPoint::setZ(float z)
{
	this->m_z = z;
}

float GNRPoint::deltaX(GNRPoint* point)
{
	return (float)(this->m_x - point->m_x);
}

float GNRPoint::deltaY(GNRPoint* point)
{
	return (float)(this->m_y - point->m_y);
}

float GNRPoint::deltaZ(GNRPoint* point)
{
	return (float)(this->m_z - point->m_z);
}

// operator overload
GNRPoint  GNRPoint::operator  + (const GNRPoint& p2) const
{
	GNRPoint temp(*this);
	temp.m_x += p2.m_x;
	temp.m_y += p2.m_y;
	temp.m_z += p2.m_z;
	return temp;
}

GNRPoint  GNRPoint::operator  - (const GNRPoint& p2) const
{
	GNRPoint temp(*this);
	temp.m_x -= p2.m_x;
	temp.m_y -= p2.m_y;
	temp.m_z -= p2.m_z;
	return temp;
}

GNRPoint& GNRPoint::operator -= (const GNRPoint& p2)
{
	m_x -= p2.m_x;
	m_y -= p2.m_y;
	m_z -= p2.m_z;
	
	return *this;
}

GNRPoint& GNRPoint::operator += (const GNRPoint& p2)
{
	m_x += p2.m_x;
	m_y += p2.m_y;
	m_z += p2.m_z;
	
	return *this;
}

GNRPoint& GNRPoint::operator = (const GNRPoint& p2)
{
	m_x = p2.m_x;
	m_y = p2.m_y;
	m_z = p2.m_z;
	
	return *this;
}

// dtor
GNRPoint::~GNRPoint()
{
	// do nothing
}

wxString GNRPoint::ToString()
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
