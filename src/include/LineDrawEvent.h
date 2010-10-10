/**
 * LineDrawEvent
 * @name        LineDrawEvent.h
 * @date        2008-10-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _LINEDRAWEVENT_H_
#define _LINEDRAWEVENT_H_

#include <wx/event.h>

#include "Vertex.h"

class LineDrawEvent : public wxNotifyEvent
{
private:
	Vertex m_startPoint;
	Vertex m_endPoint;
public:
	LineDrawEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	LineDrawEvent(const LineDrawEvent& event);
	virtual wxEvent* Clone() const;
	virtual ~LineDrawEvent();

	void setStartPoint(Vertex& startPoint);
	void setEndPoint(Vertex& endPoint);

	Vertex getStartPoint();
	Vertex getEndPoint();

	DECLARE_DYNAMIC_CLASS(NotifyEvent);
};

typedef void (wxEvtHandler::*LineDrawEventFunction)(LineDrawEvent&);

// GLNotify events and macros for handling them
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GNR_LINE_DRAW, 804)
END_DECLARE_EVENT_TYPES()

#define EVT_GNR_LINE_DRAW(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GNR_LINE_DRAW, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (LineDrawEventFunction) & fn, \
(wxObject *) NULL ),

#endif // _LINEDRAWEVENT_H_
