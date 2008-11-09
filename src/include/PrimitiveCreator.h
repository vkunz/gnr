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

#include <string>

class PrimitiveCreator
{
public:
	PrimitiveCreator();
	virtual ~PrimitiveCreator();
	void createCuboid(const Vertex& position, const Vertex& angles, const Vertex& dimension);
	void setMaterial(Assembly* parent, const string& name);
	Assembly* getPrimitive();
protected:
private:
	Assembly* m_primitive;
	Face* createFace(Vertex& topLeft, Vertex& bottomLeft, Vertex& bottomRight, Vertex& topRight, Vertex& normal);
	MaterialLibrary m_matlib;
};

#endif // _GNRPRIMITIVECREATOR_H_
