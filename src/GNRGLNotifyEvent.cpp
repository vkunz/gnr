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

void GNRGLNotifyEvent::setCanvasID(int id)
{
	canvasID = id;
}

int GNRGLNotifyEvent::getCanvasID()
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

void GNRGLNotifyEvent::setWorldSize(float x, float y)
{
	world_x = x;
	world_y = y;
}

float GNRGLNotifyEvent::getWorldX()
{
	return world_x;
}

float GNRGLNotifyEvent::getWorldY()
{
	return world_y;
}
