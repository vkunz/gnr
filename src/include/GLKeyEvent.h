/**
 * GLKeyEvent
 * @name        GLKeyEvent.h
 * @date        2008-11-12
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGLKEYEVENT_H_
#define _GNRGLKEYEVENT_H_

#include <wx/event.h>

#include "Enum.h"

class GLKeyEvent : public wxNotifyEvent
{
private:
	wxChar m_key;
	canvasType m_canvasID;
	
public:
	GLKeyEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	GLKeyEvent(const GLKeyEvent& event);
	virtual wxEvent* Clone() const;
	void setCanvasID(canvasType id);
	void setKey(wxChar key);
	
	canvasType getCanvasID();
	wxChar getKey();
	
	DECLARE_DYNAMIC_CLASS(GLKeyEvent);
};

typedef void (wxEvtHandler::*GLKeyEventFunction)(GLKeyEvent&);

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GL_KEY, 807)
END_DECLARE_EVENT_TYPES()

#define EVT_GL_KEY(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GL_KEY, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (GLKeyEventFunction) & fn, \
(wxObject *) NULL ),

#endif // _GNRGLKEYEVENT_H_
