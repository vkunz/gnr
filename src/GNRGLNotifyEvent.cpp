/**
 * GNRGLNotifyEvent
 * @name        GNRGLNotifyEvent.cpp
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRGLNotifyEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GL_NOTIFY)
IMPLEMENT_DYNAMIC_CLASS(GNRGLNotifyEvent, wxNotifyEvent)


GNRGLNotifyEvent::GNRGLNotifyEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id)
{
	selectedObj = 0;
}

GNRGLNotifyEvent::GNRGLNotifyEvent(const GNRGLNotifyEvent& event): wxNotifyEvent(event) {}

wxEvent* GNRGLNotifyEvent::Clone() const
{
	return new GNRGLNotifyEvent(*this);
}

void GNRGLNotifyEvent::setCanvasID(canvasType id)
{
	canvasID = id;
}

canvasType GNRGLNotifyEvent::getCanvasID()
{
	return canvasID;
}

void GNRGLNotifyEvent::setSelectedObj(int obj)
{
	selectedObj = obj;
}

int GNRGLNotifyEvent::getSelectedObj()
{
	return selectedObj;
}

wxMouseEvent GNRGLNotifyEvent::getMouseEvent()
{
	return event;
}

void GNRGLNotifyEvent::setMouseEvent(wxMouseEvent event)
{
	this->event = event;
}

void GNRGLNotifyEvent::setWindowSize(int x, int y)
{
	win_x = x;
	win_y = y;
}

int GNRGLNotifyEvent::getWinX()
{
	return win_x;
}

int GNRGLNotifyEvent::getWinY()
{
	return win_y;
}

void GNRGLNotifyEvent::setWorldSize(GNRVertex* glcoords)
{
	world_min_x = glcoords[0].getX();
	world_max_x = glcoords[1].getX();
	world_min_y = glcoords[0].getY();
	world_max_y = glcoords[1].getY();
	world_min_z = glcoords[0].getZ();
	world_max_z = glcoords[1].getZ();
}

float GNRGLNotifyEvent::getWorldXmax()
{
	return world_max_x;
}

float GNRGLNotifyEvent::getWorldYmax()
{
	return world_max_y;
}

float GNRGLNotifyEvent::getWorldZmax()
{
	return world_max_z;
}

float GNRGLNotifyEvent::getWorldXmin()
{
	return world_min_x;
}

float GNRGLNotifyEvent::getWorldYmin()
{
	return world_min_y;
}

float GNRGLNotifyEvent::getWorldZmin()
{
	return world_min_z;
}

void GNRGLNotifyEvent::setCamRotatedX(const float angle)
{
	cam_rotated_x = angle;
}

float GNRGLNotifyEvent::getCamRotatedX()
{
	return cam_rotated_x;
}

void GNRGLNotifyEvent::setCamRotatedY(const float angle)
{
	cam_rotated_y = angle;
}

float GNRGLNotifyEvent::getCamRotatedY()
{
	return cam_rotated_y;
}

void GNRGLNotifyEvent::setCamRotatedZ(const float angle)
{
	cam_rotated_z = angle;
}

float GNRGLNotifyEvent::getCamRotatedZ()
{
	return cam_rotated_z;
}

void GNRGLNotifyEvent::setCamPosition(const GNRVertex& position)
{
	cam_position = position;
}

GNRVertex& GNRGLNotifyEvent::getCamPosition()
{
	return cam_position;
}
