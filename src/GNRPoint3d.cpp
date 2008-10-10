#include "GNRPoint3d.h"

GNRPoint3d::GNRPoint3d(GNRVertex* p_coord, GNRVertex* norm)
{
	m_coord = new Vertex(p_coord);
	m_norm = new Vertex(p_norm);
}

const GNRVertex* GNRPoint3d::getCoord() const
{
	return m_coord;
}
const GNRVertex* GNRPoint3d::getNorm() const
{
	return m_norm;
}

