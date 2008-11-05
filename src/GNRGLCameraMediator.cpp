/**
 * GNRGLCameraMediator
 * @note        [DONE]
 * @name        GNRGLCameraMediator.cpp
 * @date        2008-10-25
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRGLCameraMediator.h"

/**
 * set camera pointer
 * @param   GNRGLCamera     pointer to cam
 * @access  private
 */
void GNRGLCameraMediator::setGLCamera(GNRGLCamera* camera)
{
	m_GLCamera = camera;
}

/**
 * init all needed values for camera translation
 * @param   GNRGLNotifyEvent      event from gl canvas
 * @access  private
 */
void GNRGLCameraMediator::initialize(GNRGLNotifyEvent& event)
{
	//do initialize stuff here
	m_mouse_x = event.getMouseEvent().GetX();
	m_mouse_y = event.getMouseEvent().GetY();
	
	//store cam data
	old_viewPoint   = m_GLCamera->getViewPoint();
	old_viewDir     = m_GLCamera->getViewDir();
	old_rightVector = m_GLCamera->getRightVector();
	old_upVector    = m_GLCamera->getUpVector();
	old_rotatedX    = m_GLCamera->getRotatedX();
	old_rotatedY    = m_GLCamera->getRotatedY();
	old_rotatedZ    = m_GLCamera->getRotatedZ();
	m_distance      = m_GLCamera->getDistance();
	
	//window size (2D screen)
	window_w = event.getWinX();
	window_h = event.getWinY();
}

/**
 * do translation to selected camera
 * @param   GNRGLNotifyEvent      event from gl canvas
 * @access  private
 */
int GNRGLCameraMediator::translate(GNRGLNotifyEvent& event)
{
	//do specific translations on wheel event only
	if (event.getMouseEvent().GetWheelRotation())
	{
		ZoomIn(event);
		return 0;
	}
	
	//call translation dependend methods
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

/**
 * no finalize needed here, only assembly for undo and redo
 * @access  private
 */
void GNRGLCameraMediator::finalize()
{
}
