/**
 * This class performes all the camera-movement in 3D
 * @note        [DONE]
 * @name        GLCameraMediator3D.cpp
 * @date        2008-10-25
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "GLCameraMediator3D.h"

/**
 * move the camera in XY dimension
 * @param[in]       event           event from GLNotify
 */
void GLCameraMediator3D::MoveXY(GLNotifyEvent& event)
{
	//set real world up vector
	Vertex up(0.0,1.0,0.0);
	
	//remember distance of cam for speed up
	float distance = m_GLCamera->getDistance();
	
	//calculate translation scale on 2D screen
	float distX = (float)(m_mouse_x - event.getMouseEvent().GetX())/(float)(window_w)*distance;
	float distY = (float)(event.getMouseEvent().GetY() - m_mouse_y)/(float)(window_h)*distance;
	
	//move viewpoint by right vector and up vector with scale
	Vertex viewPoint = old_viewPoint + (old_rightVector*distX);
	viewPoint = viewPoint + (up*distY);
	
	//set new camera viewpoint
	m_GLCamera->setViewPoint(viewPoint);
}

/**
 * move the camera in XZ dimension
 * @param[in]       event           event from GLNotify
 */
void GLCameraMediator3D::MoveXZ(GLNotifyEvent& event)
{
	//store vector to viewdir
	Vertex front = old_viewDir;
	
	//remember distance of cam for speed up
	float distance = m_GLCamera->getDistance();
	
	//calculate translation scale on 2D screen
	float distX = (float)(m_mouse_x - event.getMouseEvent().GetX())/(float)(window_w)*distance;
	float distZ = (float)(m_mouse_y - event.getMouseEvent().GetY())/(float)(window_h)*distance;
	
	//set y-direction to zero
	front.setY(0.0);
	
	//move viewpoint by right vector and front vector with scale
	Vertex viewPoint = old_viewPoint + (old_rightVector*distX);
	viewPoint = viewPoint + (front*-distZ);
	
	//set new camera viewpoint
	m_GLCamera->setViewPoint(viewPoint);
}

/**
 * rotate the camera around X+Y-axis
 * @param[in]       event       event from GLNotify
 */
void GLCameraMediator3D::RotateXY(GLNotifyEvent& event)
{
	//calculate rotation from 2D screen movement
	float xangle = (float)(event.getMouseEvent().GetY() - m_mouse_y)/(float)window_h*180.0f;
	float yangle = (float)(m_mouse_x - event.getMouseEvent().GetX())/(float)window_w*360.0f;
	
	//rotate around the right-Vector
	Vertex viewDir = old_viewDir*cos(xangle*M_PI/180.0) + old_upVector*sin(xangle*M_PI/180.0);
	
	//stop moving, you'll loose your room
	if (viewDir.getY() > 0)
	{
		viewDir.setY(0.0);
	}
	viewDir.normalize();
	
	//calculate new up vector and set y-axis to one
	Vertex upVector = old_rightVector * viewDir;
	upVector.setY(1.0);
	
	//rotate vectors by mouse move in x-axiy
	Vertex rightVector(old_rightVector);
	upVector.rotate(0, yangle, 0);
	viewDir.rotate(0, yangle, 0);
	rightVector.rotate(0, yangle, 0);
	
	//normalize vectors
	rightVector.normalize();
	upVector.normalize();
	viewDir.normalize();
	
	//set new camera position and rotation
	m_GLCamera->setRotatedX(old_rotatedX + xangle);
	m_GLCamera->setRotatedY(old_rotatedY + yangle);
	m_GLCamera->setRightVector(rightVector);
	m_GLCamera->setUpVector(upVector);
	m_GLCamera->setViewDir(viewDir);
}

/**
 * rotate the camera in arround X+Z-axis
 * @param[in]       event       event from GLNotify
 */
void GLCameraMediator3D::RotateXZ(GLNotifyEvent& event)
{
	//calculate rotation from 2D screen movement
	float xangle = (float)(event.getMouseEvent().GetY() - m_mouse_y)/(float)window_h*180.0f;
	float zangle = (float)(m_mouse_x - event.getMouseEvent().GetX())/(float)window_w*360.0f;
	
	//Rotate viewdir around the right vector:
	Vertex viewDir = old_viewDir*cos(xangle*M_PI/180.0) + old_upVector*sin(xangle*M_PI/180.0);
	
	//stop moving, you'll loose your room
	if (viewDir.getY() > 0)
	{
		viewDir.setY(0.0);
	}
	viewDir.normalize();
	
	//now compute the new UpVector (by cross product)
	Vertex upVector = (viewDir * old_rightVector) *-1;
	
	//Rotate viewdir around the right vector:
	Vertex rightVector = old_rightVector*cos(zangle*M_PI/180.0) + upVector*sin(zangle*M_PI/180.0);
	rightVector.normalize();
	
	//now compute the new UpVector (by cross product)
	upVector = (viewDir * rightVector)*-1;
	upVector.normalize();
	
	//set new camera position and rotation
	m_GLCamera->setRotatedX(old_rotatedX + xangle);
	m_GLCamera->setRotatedZ(old_rotatedZ + zangle);
	m_GLCamera->setViewDir(viewDir);
	m_GLCamera->setUpVector(upVector);
	m_GLCamera->setRightVector(rightVector);
}

/**
 * Zoom In/Out the Scene
 * @param[in]       event       event from GLNotify
 */
void GLCameraMediator3D::ZoomIn(GLNotifyEvent& event)
{
	//get delta distance for zoom
	float distance = event.getMouseEvent().GetWheelRotation() / 200.0;
	
	//change distance of cam
	m_GLCamera->changeDistance(distance);
}
