#ifndef _GNRTREECONTROLEVENT_H_
#define _GNRTREECONTROLEVENT_H_

#include <wx/event.h>
#include "GNREnum.h"

class GNRTreeControlEvent: public wxNotifyEvent
{
public:
	GNRTreeControlEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	GNRTreeControlEvent(const GNRTreeControlEvent& event);
	virtual wxEvent* Clone() const;
	virtual ~GNRTreeControlEvent();
	
	treeEventType getEventType();
	void setEventType(treeEventType type);
	
	bool getCat();
	void setCat(bool cat);
	
	wxString getNewName();
	void setNewName(wxString name);
	
protected:
private:
	treeEventType m_eventType;
	bool m_cat;
	wxString m_newName;
	DECLARE_DYNAMIC_CLASS(GNRTreeControlEvent);
};


typedef void (wxEvtHandler::*GNRTreeControlEventFunction)(GNRTreeControlEvent&);

// GNRGLNotify events and macros for handling them
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GNR_TREE_CONTROL, 806)
END_DECLARE_EVENT_TYPES()

#define EVT_GNR_TREE_CONTROL(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GNR_TREE_CONTROL, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (GNRTreeControlEventFunction) & fn, \
(wxObject *) NULL ),

#endif // _GNRTREECONTROLEVENT_H_
