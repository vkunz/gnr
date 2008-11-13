/**
 * Face
 * @note        [DONE]
 * @name        Face.h
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRFACE_H_
#define _GNRFACE_H_

#include "VNT.h"

#include <list>
#include <vector>
#include <string>

using std::list;
using std::vector;
using std::string;


class Face
{
public:

	Face();
	Face(const Face& other);
	int size() const;
	void addVNT(VNT& vnt);
	void setNormal();
	void draw() const;
	
private:

	list<VNT> m_vnt;
	
};

#endif // _GNRFACE_H_
