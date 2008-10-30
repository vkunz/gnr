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
