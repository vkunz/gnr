#ifndef _GNRPOLY_H_
#define _GNRPOLY_H_

#include <wx/list.h>

#include "GNRPoint.h"

class GNRPoly
{
public:
	// ctor
	GNRPoly();
	
	// dtor
	virtual ~GNRPoly();
	
	// functions
	void AddPoint(float x, float y, float z);
	
protected:

private:

	// Pointer of a List of GNRPoints
	wxList<GNRPoint>* m_ptrListPoly;
};

#endif // _GNRPOLY_H_
