/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRAssembly
 * @name        GNRAssembly.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <list>

#include "GNRAssembly.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

// ctor
GNRAssembly::GNRAssembly()
{
}

// dtor
GNRAssembly::~GNRAssembly()
{
}

float GNRAssembly::getX() const
{
	return m_xOffset;
}

float GNRAssembly::getY() const
{
	return m_yOffset;
}

float GNRAssembly::getZ() const
{
	return m_zOffset;
}

void GNRAssembly::setX(const float x)
{
	m_xOffset = x;
}

void GNRAssembly::setY(const float y)
{
	m_yOffset = y;
}

void GNRAssembly::setZ(const float z)
{
	m_zOffset = z;
}

float GNRAssembly::getPhi() const
{
	return m_phi;
}

float GNRAssembly::getRho() const
{
	return m_rho;
}

float GNRAssembly::getTheta() const
{
	return m_theta;
}

void GNRAssembly::setPhi(const float phi)
{
	m_phi = phi;
}

void GNRAssembly::setRho(const float rho)
{
	m_phi = rho;
}

void GNRAssembly::setTheta(const float theta)
{
	m_phi = theta;
}

void GNRAssembly::setAssemblyTitle(const std::string str)
{
	m_AssemblyTitle = str;
}

void GNRAssembly::draw() const
{
	// draw the children
	for (std::list<GNRAssembly*>::const_iterator it = m_parts.begin(); it != m_parts.end(); ++it)
	{
		(*it)->draw();
	}
	
	// draw myself
	for (std::list<GNRFace>::const_iterator it = m_faces.begin(); it != m_faces.end(); ++it)
	{
		it->draw();
	}
}

void GNRAssembly::addFace(const GNRFace newface)
{
	m_faces.push_back(newface);
}

void GNRAssembly::addChildAssembly(GNRAssembly* assembly)
{
	m_parts.push_back(assembly);
}
