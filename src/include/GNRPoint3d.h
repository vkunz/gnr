#ifndef _GNRPOINT3D_H_
#define _GNRPOINT3D_H_

#include "GNRVertex.h"

class GNRPoint3d
{
private:
	// attributes
	GNRVertex* m_coord;
	GNRVertex* m_norm;
	GNRVertex* m_text;
protected:

public:
	// ctor
	GNRPoint3d(GNRVertex* p_coord, GNRVertex* p_norm, GNRVertex* p_text);
	GNRPoint3d(const GNRPoint3d& p3d);
	
	// getter
	const GNRVertex* getCoord() const;
	const GNRVertex* getNorm() const;
	const GNRVertex* getText() const;
	
	// functions
	wxString ToString();
};

#endif // _GNRPOINT3D_H_
