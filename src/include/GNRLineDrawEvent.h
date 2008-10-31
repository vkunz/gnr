#ifndef GNRLINEDRAWEVENT_H
#define GNRLINEDRAWEVENT_H

#include "GNRVertex.h"
#include <wx/event.h>

class GNRLineDrawEvent : public wxNotifyEvent
{
private:
	GNRVertex m_startPoint;
	GNRVertex m_endPoint;
public:
	GNRLineDrawEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	GNRLineDrawEvent(const GNRLineDrawEvent& event);
	virtual wxEvent* Clone() const;
	virtual ~GNRLineDrawEvent();
	
	void setStartPoint(GNRVertex& startPoint);
	void setEndPoint(GNRVertex& endPoint);
	
	GNRVertex getStartPoint();
	GNRVertex getEndPoint();
	
	DECLARE_DYNAMIC_CLASS(GNRNotifyEvent);
};

typedef void (wxEvtHandler::*GNRLineDrawEventFunction)(GNRLineDrawEvent&);

// GNRGLNotify events and macros for handling them
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GNR_LINE_DRAW, 804)
END_DECLARE_EVENT_TYPES()

#define EVT_GNR_LINE_DRAW(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GNR_LINE_DRAW, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (GNRLineDrawEventFunction) & fn, \
(wxObject *) NULL ),

#endif // GNRLINEDRAWEVENT_H
