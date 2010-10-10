/**
 * NotifyEvent
 * @name        NotifyEvent.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _NOTIFYEVENT_H_
#define _NOTIFYEVENT_H_

#include <wx/event.h>

class Assembly;
class AssemblyData;

class NotifyEvent : public wxNotifyEvent
{
private:

	int eventType;
	int eventSnapToGrid;
	int eventSnapToAngle;
	Assembly* assembly;
	AssemblyData* m_data;
	float m_float;
	bool eventBoolean;

public:

	NotifyEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	NotifyEvent(const NotifyEvent& event);
	virtual wxEvent* Clone() const;

	void setGNREventType(int type);
	int getGNREventType();

	void setAssemblyPtr(Assembly* a);
	Assembly* getAssemblyPtr();

	void setSnapToGrid(int value);
	int getSnapToGrid();

	void setSnapToAngle(int value);
	int getSnapToAngle();

	void setBoolean(bool status);
	bool getBoolean();

	void setAssemblyDataPointer(AssemblyData* data);
	AssemblyData* getAssemblyDataPointer();

	void setFloat(float value);
	float getFloat();

	DECLARE_DYNAMIC_CLASS(NotifyEvent);
};

typedef void (wxEvtHandler::*NotifyEventFunction)(NotifyEvent&);

// GLNotify events and macros for handling them
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GNR_NOTIFY, 803)
END_DECLARE_EVENT_TYPES()

#define EVT_GNR_NOTIFY(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GNR_NOTIFY, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (NotifyEventFunction) & fn, \
(wxObject *) NULL ),


#endif // _NOTIFYEVENT_H_
