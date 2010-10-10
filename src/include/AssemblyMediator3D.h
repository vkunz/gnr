/**
 * AssemblyMediator3D
 * @name        AssemblyMediator3D.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _ASSEMBLYMEDIATOR3D_H_
#define _ASSEMBLYMEDIATOR3D_H_

#include "AssemblyMediator.h"

class AssemblyMediator3D: public AssemblyMediator
{

private:

	void MoveXY(GLNotifyEvent& event);
	void MoveXZ(GLNotifyEvent& event);
	void RotateXY(GLNotifyEvent& event);
	void RotateY(GLNotifyEvent& event);
	void RotateXZ(GLNotifyEvent& event);

};

#endif // _ASSEMBLYMEDIATOR3D_H_
