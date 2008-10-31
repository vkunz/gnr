#ifndef __GNRASSEMBLY_OBJ_H__
#define __GNRASSEMBLY_OBJ_H__

/**
 * GNRAssemblyObj
 * @name                GNRAssemblyObj.h
 * @date                2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssembly.h"
#include "GNRFace.h"

class GNRAssemblyObj : public GNRAssembly
{
public:
	GNRAssemblyObj(const string& name);
	virtual ~GNRAssemblyObj();
	
	void addFace(const GNRFace& newface);
	void setNormals();
	
	void genDL();
	
private:
	list<GNRFace> m_face;
};

#endif

