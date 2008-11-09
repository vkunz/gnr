/**
 * GLNotifyEvent
 * @note        [DONE]
 * @name        GLNotifyEvent.cpp
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GLNotifyEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GL_NOTIFY)
IMPLEMENT_DYNAMIC_CLASS(GLNotifyEvent, wxNotifyEvent)

/**
 * constructor of GLNotifyEvent
 * @param[in]       commandType     type of event
 * @param[in]       id              id of event
 */
GLNotifyEvent::GLNotifyEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id)
{
	selectedObj = 0;
}

/**
 * copy constructor of GLNotifyEvent
 * @param[in]       event           object to be copied
 */
GLNotifyEvent::GLNotifyEvent(const GLNotifyEvent& event): wxNotifyEvent(event) {}

/**
 * clones the current object
 * @return      wxEvent*        base-class-pointer
 */
wxEvent* GLNotifyEvent::Clone() const
{
	return new GLNotifyEvent(*this);
}

/**
 * sets the canvas which generated the event
 * @param[in]       id          id of current canvas
 */
void GLNotifyEvent::setCanvasID(canvasType id)
{
	canvasID = id;
}

/**
 * returns the canvas-id
 * @return      canvasType      id of the canvas
canvasType GLNotifyEvent::getCanvasID()
{
	return canvasID;
}

/**
 * sets the object, found by selection
 * @param[in]       obj         id of found object
 */
void GLNotifyEvent::setSelectedObj(int obj)
{
	selectedObj = obj;
}

/**
 * returns id of object, found by selection
 * @return          int         id of found object
 */
int GLNotifyEvent::getSelectedObj()
{
	return selectedObj;
}

/**
 * returns the mouse event stored in GLNotifyEvent
 * @return      wxMouseEvent        mouse event of the canvas
 */
wxMouseEvent GLNotifyEvent::getMouseEvent()
{
	return event;
}

/**
 * stores mouse event of the canvas
 * @param[in]       event       mouse event
 */
void GLNotifyEvent::setMouseEvent(wxMouseEvent event)
{
	this->event = event;
}

/**
 * stores the window size of the current canvas (in pixels)
 * @param[in]       x       x-dimension
 * @param[in]       y       y-dimension
 */
void GLNotifyEvent::setWindowSize(int x, int y)
{
	win_x = x;
	win_y = y;
}

/**
 * returns window size in x orientation
 * @return      int         x-size
 */
int GLNotifyEvent::getWinX()
{
	return win_x;
}

/**
 * returns window size in y orientation
 * @return      int         y-size
 */
int GLNotifyEvent::getWinY()
{
	return win_y;
}

/**
 * stores gl-dimensions of current canvas
 * @param[in]       glcoords        array of vertex with dimensions
 */
void GLNotifyEvent::setWorldSize(Vertex* glcoords)
{
	world_min_x = glcoords[0].getX();
	world_max_x = glcoords[1].getX();
	world_min_y = glcoords[0].getY();
	world_max_y = glcoords[1].getY();
	world_min_z = glcoords[0].getZ();
	world_max_z = glcoords[1].getZ();
}

/**
 * returns max world-x size
 * @return      float       max world-x
 */
float GLNotifyEvent::getWorldXmax()
{
	return world_max_x;
}

/**
 * returns max world-y size
 * @return      float       max world-y
 */
float GLNotifyEvent::getWorldYmax()
{
	return world_max_y;
}

/**
 * returns max world-z size
 * @return      float       max world-z
 */
float GLNotifyEvent::getWorldZmax()
{
	return world_max_z;
}

/**
 * returns min world-x size
 * @return      float       min world-x
 */
float GLNotifyEvent::getWorldXmin()
{
	return world_min_x;
}

/**
 * returns min world-y size
 * @return      float       min world-y
 */
float GLNotifyEvent::getWorldYmin()
{
	return world_min_y;
}

/**
 * returns min world-z size
 * @return      float       min world-z
 */
float GLNotifyEvent::getWorldZmin()
{
	return world_min_z;
}

/**
 * sets camera-rotation arround x-axis
 * @param[in]       angle       phi-rotation
 */
void GLNotifyEvent::setCamRotatedX(const float angle)
{
	cam_rotated_x = angle;
}

/**
 * returns camera rotation arround x-axis
 * @return      float           phi-rotation
 */
float GLNotifyEvent::getCamRotatedX()
{
	return cam_rotated_x;
}

/**
 * sets camera-rotation arround y-axis
 * @param[in]       angle       theta-rotation
 */
void GLNotifyEvent::setCamRotatedY(const float angle)
{
	cam_rotated_y = angle;
}

/**
 * returns camera rotation arround y-axis
 * @return      float           theta-rotation
 */
float GLNotifyEvent::getCamRotatedY()
{
	return cam_rotated_y;
}

/**
 * sets camera-rotation arround z-axis
 * @param[in]       angle       rho-rotation
 */
void GLNotifyEvent::setCamRotatedZ(const float angle)
{
	cam_rotated_z = angle;
}

/**
 * returns camera rotation arround z-axis
 * @return      float           rho-rotation
 */
float GLNotifyEvent::getCamRotatedZ()
{
	return cam_rotated_z;
}

/**
 * sets camera-position
 * @param[in]       position       vertex with camera-position
 */
void GLNotifyEvent::setCamPosition(const Vertex& position)
{
	cam_position = position;
}

/**
 * returns camera-position
 * @return      Vertex&         vertex with camera-position
 */
Vertex& GLNotifyEvent::getCamPosition()
{
	return cam_position;
}
