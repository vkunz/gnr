#ifndef _GNRNOTIFYEVENT_H_
#define _GNRNOTIFYEVENT_H_

#include "wx/event.h"

enum eventType {GLRefresh, XMLOpen, OBJImport, ToolbarChange};

class GNRNotifyEvent : public wxNotifyEvent
{
private:
	int eventType;
public:
	GNRNotifyEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	GNRNotifyEvent(const GNRNotifyEvent& event);
	virtual wxEvent* Clone() const;
	void setGNREventType(int type);
	int getGNREventType();
	DECLARE_DYNAMIC_CLASS(GNRNotifyEvent);
};

typedef void (wxEvtHandler::*GNRNotifyEventFunction)(GNRNotifyEvent&);

// GNRGLNotify events and macros for handling them
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GNR_NOTIFY, 803)
END_DECLARE_EVENT_TYPES()

#define EVT_GNR_NOTIFY(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GNR_NOTIFY, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (GNRNotifyEventFunction) & fn, \
(wxObject *) NULL ),


#endif // _GNRNOTIFYEVENT_H_
