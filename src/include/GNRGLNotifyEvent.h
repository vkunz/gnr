#ifndef _GNRGLNOTIFYEVENT_H_
#define _GNRGLNOTIFYEVENT_H_

#include "wx/event.h"

class GNRGLNotifyEvent : public wxNotifyEvent
{
private:
	wxMouseEvent event;
	int selectedObj;
public:
	GNRGLNotifyEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	GNRGLNotifyEvent(const GNRGLNotifyEvent& event);
	virtual wxEvent* Clone() const;
	DECLARE_DYNAMIC_CLASS(GNRGLNotifyEvent);
};

typedef void (wxEvtHandler::*GNRGLNotifyEventFunction)(GNRGLNotifyEvent&);

// GNRGLNotify events and macros for handling them

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GL_NOTIFY, 802)
END_DECLARE_EVENT_TYPES()

#define EVT_GL_NOTIFY(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GL_NOTIFY, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (GNRGLNotifyEventFunction) & fn, \
(wxObject *) NULL ),

#endif // _GNRGLNOTIFYEVENT_H_