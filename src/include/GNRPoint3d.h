#ifndef _GNRPOINT3D_H_
#define _GNRPOINT3D_H_

class GNRPoint3d
{
private:
	GNRVertex* m_coord;
	GNRVertex* m_norm;
	
public:
	GNRPoint3d(GNRVertex *p_coord, GNRVertex *p_norm);
	GNRPoint3d(const GNRPoint3d& p3d) {
		m_coord = new GNRVertex(p3d.m_coord);
		m_norm = new GNRVertex(p3d.m_norm);
	}

	const Vertex* getCoord() const { return m_coord; }
	const Vertex* getNorm() const { return m_norm; }
};

#endif // _GNRPOINT3D_H_
