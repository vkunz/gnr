/**
 * defines the PrimitiveCreator
 * @name        PrimitiveCreator.h
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRPRIMITIVECREATOR_H_
#define _GNRPRIMITIVECREATOR_H_

#include "Assembly.h"
#include "Vertex.h"
#include "Face.h"
#include "MaterialLibrary.h"
#include "GlobalDefine.h"

#include <string>

class PrimitiveCreator
{
public:
	PrimitiveCreator();
	virtual ~PrimitiveCreator();
	void createCuboid(const Vertex& position, const Vertex& angles, const Vertex& dimension,const string& matname = DEFAULT_IMPORT_COLOR);
	Assembly* getPrimitive();
protected:
private:
	Assembly* m_primitive;
};

#endif // _GNRPRIMITIVECREATOR_H_
