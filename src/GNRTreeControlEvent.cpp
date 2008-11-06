#include "GNRTreeControlEvent.h"


DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_TREE_CONTROL)
IMPLEMENT_DYNAMIC_CLASS(GNRTreeControlEvent, wxNotifyEvent)


GNRTreeControlEvent::GNRTreeControlEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

GNRTreeControlEvent::GNRTreeControlEvent(const GNRTreeControlEvent& event): wxNotifyEvent(event) {}

wxEvent* GNRTreeControlEvent::Clone() const
{
	return new GNRTreeControlEvent(*this);
}

GNRTreeControlEvent::~GNRTreeControlEvent()
{
	//dtor
}
