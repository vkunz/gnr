/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRGLCameraMediator3D
 * @name        GNRGLCameraMediator3D.cpp
 * @date        2008-10-25
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRGLCameraMediator3D.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

void GNRGLCameraMediator3D::MoveXY(GNRGLNotifyEvent& event)
{
	// Moving the whole scene (by using the camera-class)
	m_GLCamera->moveUpward((float)(m_mouse_y - event.getMouseEvent().GetY())/-20.0f);
	m_GLCamera->strafeRight((float)(m_mouse_x - event.getMouseEvent().GetX())/20.0f);
}

void GNRGLCameraMediator3D::MoveXZ(GNRGLNotifyEvent& event)
{
	// Moving the whole scene (by using the camera-class)
	m_GLCamera->moveForward((float)(m_mouse_y - event.getMouseEvent().GetY())/15.0f);
	m_GLCamera->strafeRight((float)(m_mouse_x - event.getMouseEvent().GetX())/20.0f);
}

void GNRGLCameraMediator3D::RotateXY(GNRGLNotifyEvent& event)
{
	// rotate the whole scene (by using the camera-class)
	m_GLCamera->rotateX((float)(m_mouse_y - event.getMouseEvent().GetY())/-3.0f);
	m_GLCamera->rotateY((float)(m_mouse_x - event.getMouseEvent().GetX())/-3.0f);
}

void GNRGLCameraMediator3D::RotateXZ(GNRGLNotifyEvent& event)
{
	// rotate the whole scene (by using the camera-class)
	m_GLCamera->rotateX((float)(m_mouse_y - event.getMouseEvent().GetY())/-3.0f);
	m_GLCamera->rotateZ((float)(m_mouse_x - event.getMouseEvent().GetX())/-3.0f);
}
