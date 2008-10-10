/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRFace
 * @name        GNRFace.h
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
