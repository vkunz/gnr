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
#include "math.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * move the camera in XY dimension
 * @param GNRGLNotifyEvent event from GLNotify
 * @access private
 */
void GNRGLCameraMediator3D::MoveXY(GNRGLNotifyEvent& event)
{
	float distX = (float)(m_mouse_x - event.getMouseEvent().GetX())/(float)(window_w)*5.0;
	float distY = (float)(event.getMouseEvent().GetY() - m_mouse_y)/(float)(window_h)*5.0;
	
	GNRVertex viewPoint = old_viewPoint + (old_rightVector*distX);
	viewPoint = viewPoint + (old_upVector*distY);
	
	m_GLCamera->setViewPoint(viewPoint);
}

/**
 * move the camera in XZ dimension
 * @param GNRGLNotifyEvent event from GLNotify
 * @access private
 */
void GNRGLCameraMediator3D::MoveXZ(GNRGLNotifyEvent& event)
{
	float distX = (float)(m_mouse_x - event.getMouseEvent().GetX())/(float)(window_w)*5.0;
	float distZ = (float)(m_mouse_y - event.getMouseEvent().GetY())/(float)(window_h)*5.0;
	
	GNRVertex viewPoint = old_viewPoint + (old_rightVector*distX);
	viewPoint = viewPoint + (old_viewDir*-distZ);
	
	m_GLCamera->setViewPoint(viewPoint);
}

/**
 * rotate the camera in arround X+Y-axis
 * @param GNRGLNotifyEvent event from GLNotify
 * @access private
 */
void GNRGLCameraMediator3D::RotateXY(GNRGLNotifyEvent& event)
{
	float xangle = (float)(m_mouse_y - event.getMouseEvent().GetY())/(float)window_h*720.0f;
	float yangle = (float)(m_mouse_x - event.getMouseEvent().GetX())/(float)window_w*720.0f;
	
	//Rotate viewdir around the right vector:
	GNRVertex viewDir = old_viewDir*cos(xangle*M_PI/180.0) + old_upVector*sin(xangle*M_PI/180.0);
	viewDir.normalize();
	
	//now compute the new UpVector (by cross product)
	GNRVertex upVector = (viewDir * old_rightVector) *-1;
	
	//Rotate viewdir around the up vector at the viewPoint:
	viewDir = viewDir*cos(yangle*M_PI/180.0) - old_rightVector*sin(yangle*M_PI/180.0);
	viewDir.normalize();
	
	//now compute the new RightVector (by cross product)
	GNRVertex rightVector = viewDir * upVector;
	
	m_GLCamera->setRotatedX(old_rotatedX + xangle);
	m_GLCamera->setRotatedY(old_rotatedY + yangle);
	m_GLCamera->setViewDir(viewDir);
	m_GLCamera->setUpVector(upVector);
	m_GLCamera->setRightVector(rightVector);
}

/**
 * rotate the camera in arround X+Z-axis
 * @param GNRGLNotifyEvent event from GLNotify
 * @access private
 */
void GNRGLCameraMediator3D::RotateXZ(GNRGLNotifyEvent& event)
{
	float xangle = (float)(m_mouse_y - event.getMouseEvent().GetY())/(float)window_h*720.0f;
	float zangle = (float)(m_mouse_x - event.getMouseEvent().GetX())/(float)window_w*720.0f;
	
	//Rotate viewdir around the right vector:
	GNRVertex viewDir = old_viewDir*cos(xangle*M_PI/180.0) + old_upVector*sin(xangle*M_PI/180.0);
	viewDir.normalize();
	
	//now compute the new UpVector (by cross product)
	GNRVertex upVector = (viewDir * old_rightVector) *-1;
	
	//Rotate viewdir around the right vector:
	GNRVertex rightVector = old_rightVector*cos(zangle*M_PI/180.0) + upVector*sin(zangle*M_PI/180.0);
	rightVector.normalize();
	
	//now compute the new UpVector (by cross product)
	upVector = (viewDir * rightVector)*-1;
	
	
	m_GLCamera->setRotatedX(old_rotatedX + xangle);
	m_GLCamera->setRotatedZ(old_rotatedZ + zangle);
	m_GLCamera->setViewDir(viewDir);
	m_GLCamera->setUpVector(upVector);
	m_GLCamera->setRightVector(rightVector);
}

/**
 * Zoom In/Out the Scene
 * @param GNRGLNotifyEvent event from GLNotify
 * @access private
 */
void GNRGLCameraMediator3D::ZoomIn(GNRGLNotifyEvent& event)
{
	float distance = event.getMouseEvent().GetWheelRotation() / 600.0;
	
	m_GLCamera->changeDistance(distance);
}
