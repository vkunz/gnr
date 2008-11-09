/**
 * GLNotifyEvent
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


GLNotifyEvent::GLNotifyEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id)
{
	selectedObj = 0;
}

GLNotifyEvent::GLNotifyEvent(const GLNotifyEvent& event): wxNotifyEvent(event) {}

wxEvent* GLNotifyEvent::Clone() const
{
	return new GLNotifyEvent(*this);
}

void GLNotifyEvent::setCanvasID(canvasType id)
{
	canvasID = id;
}

canvasType GLNotifyEvent::getCanvasID()
{
	return canvasID;
}

void GLNotifyEvent::setSelectedObj(int obj)
{
	selectedObj = obj;
}

int GLNotifyEvent::getSelectedObj()
{
	return selectedObj;
}

wxMouseEvent GLNotifyEvent::getMouseEvent()
{
	return event;
}

void GLNotifyEvent::setMouseEvent(wxMouseEvent event)
{
	this->event = event;
}

void GLNotifyEvent::setWindowSize(int x, int y)
{
	win_x = x;
	win_y = y;
}

int GLNotifyEvent::getWinX()
{
	return win_x;
}

int GLNotifyEvent::getWinY()
{
	return win_y;
}

void GLNotifyEvent::setWorldSize(Vertex* glcoords)
{
	world_min_x = glcoords[0].getX();
	world_max_x = glcoords[1].getX();
	world_min_y = glcoords[0].getY();
	world_max_y = glcoords[1].getY();
	world_min_z = glcoords[0].getZ();
	world_max_z = glcoords[1].getZ();
}

float GLNotifyEvent::getWorldXmax()
{
	return world_max_x;
}

float GLNotifyEvent::getWorldYmax()
{
	return world_max_y;
}

float GLNotifyEvent::getWorldZmax()
{
	return world_max_z;
}

float GLNotifyEvent::getWorldXmin()
{
	return world_min_x;
}

float GLNotifyEvent::getWorldYmin()
{
	return world_min_y;
}

float GLNotifyEvent::getWorldZmin()
{
	return world_min_z;
}

void GLNotifyEvent::setCamRotatedX(const float angle)
{
	cam_rotated_x = angle;
}

float GLNotifyEvent::getCamRotatedX()
{
	return cam_rotated_x;
}

void GLNotifyEvent::setCamRotatedY(const float angle)
{
	cam_rotated_y = angle;
}

float GLNotifyEvent::getCamRotatedY()
{
	return cam_rotated_y;
}

void GLNotifyEvent::setCamRotatedZ(const float angle)
{
	cam_rotated_z = angle;
}

float GLNotifyEvent::getCamRotatedZ()
{
	return cam_rotated_z;
}

void GLNotifyEvent::setCamPosition(const Vertex& position)
{
	cam_position = position;
}

Vertex& GLNotifyEvent::getCamPosition()
{
	return cam_position;
}
