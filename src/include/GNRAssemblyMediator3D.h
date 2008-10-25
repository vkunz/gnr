#ifndef GNRASSEMBLYMEDIATOR3D_H
#define GNRASSEMBLYMEDIATOR3D_H

#include "GNRAssembly.h"
#include "GNRAssemblyMediator.h"

class GNRAssemblyMediator3D: public GNRAssemblyMediator
{
public:

	GNRAssemblyMediator3D() {};
	virtual ~GNRAssemblyMediator3D() {};
	
protected:

private:

	void MoveXY(GNRGLNotifyEvent& event);
	void MoveXZ(GNRGLNotifyEvent& event);
	void RotateXY(GNRGLNotifyEvent& event);
	void RotateXZ(GNRGLNotifyEvent& event);
	
};

#endif // GNRAssemblyMediator3D_H
