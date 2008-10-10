#ifndef _GNRPOINT3D_H_
#define _GNRPOINT3D_H_

#include "GNRVertex.h"

class GNRPoint3d
{
private:
	GNRVertex* m_coord;
	GNRVertex* m_norm;
	
protected:

public:
	// ctor
	GNRPoint3d(GNRVertex* p_coord, GNRVertex* norm);
	GNRPoint3d(const GNRPoint3d& p3d);
	
	// getter
	const GNRVertex* getCoord() const;
	const GNRVertex* getNorm() const;
};

#endif // _GNRPOINT3D_H_
