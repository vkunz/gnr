#include "GNRGLNotifyEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GL_NOTIFY)
IMPLEMENT_DYNAMIC_CLASS(GNRGLNotifyEvent, wxNotifyEvent)


GNRGLNotifyEvent::GNRGLNotifyEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

GNRGLNotifyEvent::GNRGLNotifyEvent(const GNRGLNotifyEvent& event): wxNotifyEvent(event) {}

wxEvent* GNRGLNotifyEvent::Clone() const
{
	return new GNRGLNotifyEvent(*this);
}
