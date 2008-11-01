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

class GNRPrimitiveCreator
{
public:
	GNRPrimitiveCreator();
	virtual ~GNRPrimitiveCreator();
	GNRAssembly* createCuboid(const GNRVertex& position, const GNRVertex& angles, const GNRVertex& dimension);
protected:
private:
	GNRFace* createFace(GNRVertex& topLeft, GNRVertex& bottomLeft, GNRVertex& bottomRight, GNRVertex& topRight, GNRVertex& normal);
};

#endif // _GNRPRIMITIVECREATOR_H_
