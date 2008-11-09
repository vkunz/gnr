/**
 * GLNotifyEvent
 * @name        GLNotifyEvent.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGLNOTIFYEVENT_H_
#define _GNRGLNOTIFYEVENT_H_

#include <wx/event.h>

#include "Enum.h"
#include "Vertex.h"

class GLNotifyEvent : public wxNotifyEvent
{
private:
	wxMouseEvent event;
	int selectedObj;
	bool eventBoolean;
	canvasType canvasID;
	int win_x, win_y;
	Vertex cam_position;
	float world_min_x, world_min_y, world_min_z;
	float world_max_x, world_max_y, world_max_z;
	float cam_rotated_x, cam_rotated_y, cam_rotated_z;
public:
	GLNotifyEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	GLNotifyEvent(const GLNotifyEvent& event);
	virtual wxEvent* Clone() const;
	void setCanvasID(canvasType id);
	void setSelectedObj(int obj);
	void setMouseEvent(wxMouseEvent event);
	void setWindowSize(int x, int y);
	void setWorldSize(Vertex* glcoords);
	canvasType getCanvasID();
	int getSelectedObj();
	wxMouseEvent getMouseEvent();
	int getWinX();
	int getWinY();
	float getWorldXmin();
	float getWorldYmin();
	float getWorldZmin();
	float getWorldXmax();
	float getWorldYmax();
	float getWorldZmax();
	void setCamRotatedX(const float angle);
	float getCamRotatedX();
	void setCamRotatedY(const float angle);
	float getCamRotatedY();
	void setCamRotatedZ(const float angle);
	float getCamRotatedZ();
	void setCamPosition(const Vertex& position);
	Vertex& getCamPosition();
	DECLARE_DYNAMIC_CLASS(GLNotifyEvent);
};

typedef void (wxEvtHandler::*GLNotifyEventFunction)(GLNotifyEvent&);

// GLNotify events and macros for handling them

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GL_NOTIFY, 802)
END_DECLARE_EVENT_TYPES()

#define EVT_GL_NOTIFY(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GL_NOTIFY, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (GLNotifyEventFunction) & fn, \
(wxObject *) NULL ),

#endif // _GNRGLNOTIFYEVENT_H_
