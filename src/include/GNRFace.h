/**
 * GNRFace
 * @note        [DONE]
 * @name        GNRFace.h
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRFACE_H_
#define _GNRFACE_H_

#include "GNRVNT.h"

#include <list>
#include <vector>
#include <string>

using std::list;
using std::vector;
using std::string;


class GNRFace
{
public:

	GNRFace();
	GNRFace(const GNRFace& other);
	int size() const;
	void addVNT(GNRVNT& vnt);
	void setNormal();
	void draw() const;
	
private:

	list<GNRVNT> m_vnt;
	
};

#endif // _GNRFACE_H_
