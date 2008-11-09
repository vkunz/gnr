/**
 * AssemblyMediator2D
 * @name        AssemblyMediator2D.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef ASSEMBLYMEDIATOR2D_H
#define ASSEMBLYMEDIATOR2D_H

#include "AssemblyMediator.h"

class AssemblyMediator2D: public AssemblyMediator
{

private:

	void MoveXY(GLNotifyEvent& event);
	void MoveXZ(GLNotifyEvent& event);
	void RotateXY(GLNotifyEvent& event);
	void RotateY(GLNotifyEvent& event);
	void RotateXZ(GLNotifyEvent& event);
	
};

#endif // AssemblyMediator2D_H
