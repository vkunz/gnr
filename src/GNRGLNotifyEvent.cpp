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
}

float GNRGLNotifyEvent::getWorldXmax()
{
	return world_max_x;
}

float GNRGLNotifyEvent::getWorldYmax()
{
	return world_max_y;
}

float GNRGLNotifyEvent::getWorldXmin()
{
	return world_min_x;
}

float GNRGLNotifyEvent::getWorldYmin()
{
	return world_min_y;
}
