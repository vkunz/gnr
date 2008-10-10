/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRFace
 * @name        GNRFace.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRPoint3d.h"
#include "GNRVertex.h"

GNRPoint3d::GNRPoint3d(GNRVertex* p_coord, GNRVertex* p_norm)
{
	m_coord = new GNRVertex(*p_coord);
	m_norm = new GNRVertex(*p_norm);
}

GNRPoint3d::GNRPoint3d(const GNRPoint3d& p3d)
{
	m_coord = new GNRVertex(*p3d.m_coord);
	m_norm = new GNRVertex(*p3d.m_norm);
}

const GNRVertex* GNRPoint3d::getCoord() const
{
	return m_coord;
}
const GNRVertex* GNRPoint3d::getNorm() const
{
	return m_norm;
}

