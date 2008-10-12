#ifndef _GNRGLMOUSEEVENT_H_
#define _GNRGLMOUSEEVENT_H_

#include <wx/event.h>

class GNRGLMouseEvent : public wxNotifyEvent
{
	int status;
	int field;
public:
	GNRGLMouseEvent(wxEventType eventType = wxEVT_NULL, int id = 0);
	GNRGLMouseEvent(const GNRGLMouseEvent& copy);
	virtual ~GNRGLMouseEvent();
	wxEvent* Clone();
};

// wxWidgets den neuen Event mitteilen
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(EVT_GL_MOUSE_EVENT, -1)
END_DECLARE_EVENT_TYPES()

// ein Typedef auf die entsprechenden EventHandler
typedef void(wxEvtHandler::*GNRGLMouseEventFunction)(GNRGLMouseEvent&);

#define EVT_PLOT(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( EVT_GL_MOUSE_EVENT, id, -1, \
    (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) (wxNotifyEventFunction) \
    wxStaticCastEvent( GNRGLMouseEventFunction, & fn ), (wxObject *) NULL ),

/*
// dieses #define sorgt dafür das man den Event über den Makro EventTable einbinden kann
#define EVT_GL_MOUSE_EVENT_MACRO(id, fn) DECLARE_EVENT_TABLE_ENTRY(               \
        EVT_GL_MOUSE_EVENT, id, -1, (wxObjectEventFunction)               \
        (wxEventFunction)(GNRGLMouseEventFunction) & fn,                             \
        (wxObject*) NULL),*/

// dieses #define sorgt dafür das man den Event auch über Connect verbinden kann
#define GNRGLMouseEventFunction(func)                                                 \
        (wxObjectEventFunction)                                                \
        (wxEventFunction)wxStaticCastEvent(GNRGLMouseEventFunction, &func)

/*
// code defining event

class GNRGLMouseEvent: public wxNotifyEvent
{
public:
    GNRGLMouseEvent( wxEventType commandType = wxEVT_NULL, int id = 0 );

    // required for sending with wxPostEvent()
    wxEvent* Clone();
};

DECLARE_EVENT_TYPE( GNR_GL_MouseEvent, -1 )

typedef void (wxEvtHandler::*wxPlotEventFunction)(wxPlotEvent&);

#define EVT_PLOT(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_PLOT_ACTION, id, -1, \
    (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) (wxNotifyEventFunction) \
    wxStaticCastEvent( wxPlotEventFunction, & fn ), (wxObject *) NULL ),


// code implementing the event type and the event class

DEFINE_EVENT_TYPE( wxEVT_PLOT_ACTION )

wxPlotEvent::wxPlotEvent( ...


// user code intercepting the event

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_PLOT  (ID_MY_WINDOW,  MyFrame::OnPlot)
END_EVENT_TABLE()

void MyFrame::OnPlot( wxPlotEvent &event )
{
    wxPlotCurve *curve = event.GetCurve();
}


// user code sending the event

void MyWindow::SendEvent()
{
    wxPlotEvent event( wxEVT_PLOT_ACTION, GetId() );
    event.SetEventObject( this );
    event.SetCurve( m_curve );
    GetEventHandler()->ProcessEvent( event );
}
*/

/*
// wxWidgets den neuen Event mitteilen
DECLARE_EVENT_TYPE(wxCUSTOM_EVENT, 7777)

#define EVT_CUSTOM_EVENT(fn)                                             \
	DECLARE_EVENT_TABLE_ENTRY( wxCUSTOM_EVENT, wxID_ANY, wxID_ANY,   \
	(wxObjectEventFunction)(wxEventFunction)&fn, (wxObject*) NULL ),


class GNRGLMouseEvent : public wxMouseEvent {
public:
	GNRGLMouseEvent();
	GNRGLMouseEvent(wxMouseEvent event);
	GNRGLMouseEvent( const GNRGLMouseEvent &event );

	virtual wxEvent *Clone() const
		{ return new GNRGLMouseEvent(*this); };

	DECLARE_DYNAMIC_CLASS(GNRGLMouseEvent)
};
*/
#endif // _GNRGLMOUSEEVENT_H_
