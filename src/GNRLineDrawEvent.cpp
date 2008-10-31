#include "GNRLineDrawEvent.h"


DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_LINE_DRAW)
IMPLEMENT_DYNAMIC_CLASS(GNRLineDrawEvent, wxNotifyEvent)


GNRLineDrawEvent::GNRLineDrawEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

GNRLineDrawEvent::GNRLineDrawEvent(const GNRLineDrawEvent& event): wxNotifyEvent(event) {}

wxEvent* GNRLineDrawEvent::Clone() const
{
	return new GNRLineDrawEvent(*this);
}

GNRLineDrawEvent::~GNRLineDrawEvent() {}

void GNRLineDrawEvent::setStartPoint(GNRVertex& startPoint)
{
	m_startPoint = startPoint;
}

void GNRLineDrawEvent::setEndPoint(GNRVertex& endPoint)
{
	m_endPoint = endPoint;
}

GNRVertex GNRLineDrawEvent::getStartPoint()
{
	return m_startPoint;
}

GNRVertex GNRLineDrawEvent::getEndPoint()
{
	return m_endPoint;
}
