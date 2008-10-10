#ifndef _GNRPOINT3D_H_
#define _GNRPOINT3D_H_

class GNRPoint3d
{
private:
	GNRVertex* m_coord;
	GNRVertex* m_norm;
	
public:
	GNRPoint3d(GNRVertex* p_coord, GNRVertex* norm);
	
	const Vertex* getCoord() const
	{
		return m_coord;
	}
	const Vertex* getNorm() const
	{
		return m_norm;
	}
};

#endif // _GNRPOINT3D_H_