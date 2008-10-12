#include "GNRGLMouseEvent.h"

DEFINE_EVENT_TYPE(EVT_GL_MOUSE_EVENT)

GNRGLMouseEvent::GNRGLMouseEvent(wxEventType eventType, int id) : wxNotifyEvent(eventType, id) {}

GNRGLMouseEvent::GNRGLMouseEvent(const GNRGLMouseEvent& copy): wxNotifyEvent(copy) {}

GNRGLMouseEvent::~GNRGLMouseEvent() {}

wxEvent* GNRGLMouseEvent::Clone()
{
	return new GNRGLMouseEvent(*this);
}

/*DEFINE_EVENT_TYPE( wxCUSTOM_EVENT );
IMPLEMENT_DYNAMIC_CLASS( GNRGLMouseEvent, wxEvent )

GNRGLMouseEvent::GNRGLMouseEvent() {}

GNRGLMouseEvent::GNRGLMouseEvent(wxMouseEvent event) : wxMouseEvent(event) {}

GNRGLMouseEvent::GNRGLMouseEvent( const GNRGLMouseEvent &event )
{
	// not really needed in this sample, but it's boring to have it empty
	this->m_eventType = event.m_eventType;
}
*/
