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

// dtor
GNRPoint::~GNRPoint()
{
	// do nothing
}
