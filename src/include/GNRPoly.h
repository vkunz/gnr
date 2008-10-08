#ifndef _GNRPOLY_H_
#define _GNRPOLY_H_

#include <list>

#include "GNRPoint.h"

class GNRPoly
{
public:
	// ctor
	GNRPoly();
	
	// dtor
	virtual ~GNRPoly();
	
	// functions
	void addVertex(int iPoint);
	wxString ToString();
	
protected:

private:

	// Pointer of a List of GNRPoints
	std::list<int> m_ListOfInteger;
};

#endif // _GNRPOLY_H_
