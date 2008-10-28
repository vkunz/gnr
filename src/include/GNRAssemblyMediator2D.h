/**
 * GNRAssemblyMediator2D
 * @name        GNRAssemblyMediator2D.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRASSEMBLYMEDIATOR2D_H
#define GNRASSEMBLYMEDIATOR2D_H

#include "GNRAssemblyMediator.h"

class GNRAssemblyMediator2D: public GNRAssemblyMediator
{

private:

	void MoveXY(GNRGLNotifyEvent& event);
	void MoveXZ(GNRGLNotifyEvent& event);
	void RotateXY(GNRGLNotifyEvent& event);
	void RotateXZ(GNRGLNotifyEvent& event);
	
};

#endif // GNRAssemblyMediator2D_H
