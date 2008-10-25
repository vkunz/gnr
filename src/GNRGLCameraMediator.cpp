/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRGLCameraMediator
 * @name        GNRGLCameraMediator.cpp
 * @date        2008-10-25
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRGLCameraMediator.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif


void GNRGLCameraMediator::setGLCamera(GNRGLCamera* camera)
{
	m_GLCamera = camera;
}

void GNRGLCameraMediator::initialize(GNRGLNotifyEvent& event)
{
	//do initialize stuff here
	m_mouse_x = event.getMouseEvent().GetX();
	m_mouse_y = event.getMouseEvent().GetY();
}

int GNRGLCameraMediator::translate(GNRGLNotifyEvent& event)
{
	//do specific translations
	switch (m_Translation)
	{
	case MOVEXZ:
		MoveXZ(event);
		break;
	case MOVEXY:
		MoveXY(event);
		break;
	case ROTATEXY:
		RotateXY(event);
		break;
	case ROTATEXZ:
		RotateXZ(event);
		break;
	default:
		MoveXZ(event);
		break;
	}
	
	return 0;
}
