/**
 * This class performes all the camera-movement in 2D
 * @note        [DONE]
 * @name        GLCameraMediator2D.cpp
 * @date        2008-10-25
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "GLCameraMediator2D.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * move the camera in XY dimension
 * @param[in]       WXUNUSED     unused event           event from GLNotify
 */
void GLCameraMediator2D::MoveXY(GLNotifyEvent& event)
{
	//calculate scale factor and distance moved in x and y direction
	float factor = m_GLCamera->getDistance()*0.5/(float)(window_h);
	float distX  = (float)(m_mouse_x - event.getMouseEvent().GetX())*factor;
	float distY  = (float)(event.getMouseEvent().GetY() - m_mouse_y)*factor;
	
	//move to new viewpoint
	Vertex viewPoint = old_viewPoint + (old_rightVector*distX);
	viewPoint = viewPoint + (old_upVector*distY);
	
	//set new camera viewpoint
	m_GLCamera->setViewPoint(viewPoint);
}

/**
 * move the camera in XY dimension, no other movement allowed
 * @param[in]       WXUNUSED     unused event           event from GLNotify
 */
void GLCameraMediator2D::MoveXZ(GLNotifyEvent& event)
{
	MoveXY(event);
}

/**
 * move the camera in XY dimension, no other movement allowed
 * @param[in]       WXUNUSED     unused event           event from GLNotify
 */
void GLCameraMediator2D::RotateXY(GLNotifyEvent& event)
{
	MoveXY(event);
}

/**
 * move the camera in XY dimension, no other movement allowed
 * @param[in]       WXUNUSED     unused event           event from GLNotify
 */
void GLCameraMediator2D::RotateXZ(GLNotifyEvent& event)
{
	MoveXY(event);
}

/**
 * Zoom In/Out the Scene
 * @param[in]       WXUNUSED     unused event           event from GLNotify
 */
void GLCameraMediator2D::ZoomIn(GLNotifyEvent& event)
{
	//get delta distance for zoom
	float distance = event.getMouseEvent().GetWheelRotation() / 200.0;
	
	//change distance of cam
	m_GLCamera->changeDistance(distance);
}
