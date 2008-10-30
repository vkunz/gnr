/**
 * GNRAssemblyMediator3D
 * @name        GNRAssemblyMediator3D.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRASSEMBLYMEDIATOR3D_H
#define GNRASSEMBLYMEDIATOR3D_H

#include "GNRAssemblyMediator.h"

class GNRAssemblyMediator3D: public GNRAssemblyMediator
{

private:

	void MoveXY(GNRGLNotifyEvent& event);
	void MoveXZ(GNRGLNotifyEvent& event);
	void RotateXY(GNRGLNotifyEvent& event);
	void RotateY(GNRGLNotifyEvent& event);
	void RotateXZ(GNRGLNotifyEvent& event);
	
};

#endif // GNRAssemblyMediator3D_H
