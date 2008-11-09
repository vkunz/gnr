#ifndef _GNRTREECONTROLEVENT_H_
#define _GNRTREECONTROLEVENT_H_

#include <wx/event.h>
#include "Assembly.h"
#include "Enum.h"


class TreeControlEvent: public wxNotifyEvent
{
public:
	TreeControlEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	TreeControlEvent(const TreeControlEvent& event);
	virtual wxEvent* Clone() const;
	virtual ~TreeControlEvent();
	
	treeEventType getEventType();
	void setEventType(treeEventType type);
	
	bool getCat();
	void setCat(bool cat);
	
	wxString getNewName();
	void setNewName(wxString name);
	
	Assembly* getAssembly();
	void setAssembly(Assembly* assembly);
	
protected:
private:
	treeEventType m_eventType;
	bool m_cat;
	wxString m_newName;
	Assembly* m_assembly;
	
	DECLARE_DYNAMIC_CLASS(TreeControlEvent);
};


typedef void (wxEvtHandler::*TreeControlEventFunction)(TreeControlEvent&);

// GLNotify events and macros for handling them
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GNR_TREE_CONTROL, 806)
END_DECLARE_EVENT_TYPES()

#define EVT_GNR_TREE_CONTROL(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GNR_TREE_CONTROL, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (TreeControlEventFunction) & fn, \
(wxObject *) NULL ),

#endif // _GNRTREECONTROLEVENT_H_
