/**
 * defines the GNRPrimitiveCreator
 * @name        GNRPrimitiveCreator.h
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRPRIMITIVECREATOR_H_
#define _GNRPRIMITIVECREATOR_H_

#include "GNRAssembly.h"
#include "GNRVertex.h"
#include "GNRFace.h"
#include "GNRMaterialLibrary.h"

#include <string>

class GNRPrimitiveCreator
{
public:
	GNRPrimitiveCreator();
	virtual ~GNRPrimitiveCreator();
	void createCuboid(const GNRVertex& position, const GNRVertex& angles, const GNRVertex& dimension);
	void setMaterial(GNRAssembly* parent, const string& name);
	GNRAssembly* getPrimitive();
protected:
private:
	GNRAssembly* m_primitive;
	GNRFace* createFace(GNRVertex& topLeft, GNRVertex& bottomLeft, GNRVertex& bottomRight, GNRVertex& topRight, GNRVertex& normal);
	GNRMaterialLibrary m_matlib;
};

#endif // _GNRPRIMITIVECREATOR_H_
