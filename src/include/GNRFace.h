#ifndef _GNRFACE_H_
#define _GNRFACE_H_

#include <list>

#include "GNRVertex.h"

class GNRFace
{
public:
	// ctor
	GNRFace();
	
	// dtor
	virtual ~GNRFace();
	
	// functions
	void addVertex(int iPoint);
	wxString ToString();
	
protected:

private:

	// Pointer of a List of GNRPoints
	std::list<int> m_ListOfInteger;
};

#endif // _GNRFACE_H_
