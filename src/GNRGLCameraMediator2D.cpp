/**
 * GNRGLCameraMediator2D
 * @name        GNRGLCameraMediator2D.cpp
 * @date        2008-10-25
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRGLCameraMediator2D.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

void GNRGLCameraMediator2D::MoveXY(GNRGLNotifyEvent& event)
{
	float distance = m_GLCamera->getDistance();
	
	float distX = (float)(m_mouse_x - event.getMouseEvent().GetX())/(float)(window_w)*distance;
	float distY = (float)(event.getMouseEvent().GetY() - m_mouse_y)/(float)(window_h)*distance;
	
//	doSnapMove(distX);
//	doSnapMove(distY);

	GNRVertex viewPoint = old_viewPoint + (old_rightVector*distX);
	viewPoint = viewPoint + (old_upVector*distY);
	
	m_GLCamera->setViewPoint(viewPoint);
}

void GNRGLCameraMediator2D::MoveXZ(GNRGLNotifyEvent& event)
{
	MoveXY(event);
}

void GNRGLCameraMediator2D::RotateXY(GNRGLNotifyEvent& event)
{
	MoveXY(event);
}

void GNRGLCameraMediator2D::RotateXZ(GNRGLNotifyEvent& event)
{
	MoveXY(event);
}

void GNRGLCameraMediator2D::ZoomIn(GNRGLNotifyEvent& event)
{
	float distance = event.getMouseEvent().GetWheelRotation() / 200.0;
	
	m_GLCamera->changeDistance(distance);
}
