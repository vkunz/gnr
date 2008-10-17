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
