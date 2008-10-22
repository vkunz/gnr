#include "GNRNotifyEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_NOTIFY)
IMPLEMENT_DYNAMIC_CLASS(GNRNotifyEvent, wxNotifyEvent)


GNRNotifyEvent::GNRNotifyEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

GNRNotifyEvent::GNRNotifyEvent(const GNRNotifyEvent& event): wxNotifyEvent(event) {}

wxEvent* GNRNotifyEvent::Clone() const
{
	return new GNRNotifyEvent(*this);
}

void GNRNotifyEvent::setGNREventType(int type)
{
	eventType = type;
}

int GNRNotifyEvent::getGNREventType()
{
	return eventType;
}
