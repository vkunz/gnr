#include <wx/list.h>

#include "GNRPoly.h"

// ctor
GNRPoly::GNRPoly()
{
	m_ptrListPoly = new wxList<GNRPoint>;
}

// dtor
GNRPoly::~GNRPoly()
{
	// do nothing
}

void GNRPoly::AddPoint(float x, float y, float z)
{

}
