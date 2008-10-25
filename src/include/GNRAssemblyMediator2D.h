#ifndef GNRASSEMBLYMEDIATOR2D_H
#define GNRASSEMBLYMEDIATOR2D_H

#include "GNRAssembly.h"
#include "GNRAssemblyMediator.h"

class GNRAssemblyMediator2D: public GNRAssemblyMediator
{
public:

	GNRAssemblyMediator2D() {};
	virtual ~GNRAssemblyMediator2D() {};
	
protected:

private:

	void MoveXY(GNRGLNotifyEvent& event);
	void MoveXZ(GNRGLNotifyEvent& event);
	void RotateXY(GNRGLNotifyEvent& event);
	void RotateXZ(GNRGLNotifyEvent& event);
	
};

#endif // GNRAssemblyMediator2D_H
