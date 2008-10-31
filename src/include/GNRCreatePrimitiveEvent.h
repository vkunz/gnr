#ifndef GNRCREATEPRIMITIVEEVENT_H
#define GNRCREATEPRIMITIVEEVENT_H

#include <wx/event.h>
#include "GNREnum.h"
#include "GNRVertex.h"

class GNRCreatePrimitiveEvent : public wxNotifyEvent
{
private:
	primitivesType m_type;
	GNRVertex m_position;
	GNRVertex m_angles;
	GNRVertex m_dimensions;
	
public:
	GNRCreatePrimitiveEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	GNRCreatePrimitiveEvent(const GNRCreatePrimitiveEvent& event);
	virtual wxEvent* Clone() const;
	virtual ~GNRCreatePrimitiveEvent();
	
	void setPrimitiveType(primitivesType type);
	
	void setPosition(GNRVertex pos);
	void setAngles(GNRVertex angles);
	void setDimensions(GNRVertex dim);
	
	primitivesType getPrimitiveType();
	
	GNRVertex getPosition();
	GNRVertex getAngles();
	GNRVertex getDimensions();
	
	DECLARE_DYNAMIC_CLASS(GNRCreatePrimitiveEvent);
};

typedef void (wxEvtHandler::*GNRCreatePrimitiveEventFunction)(GNRCreatePrimitiveEvent&);

// GNRGLNotify events and macros for handling them
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GNR_CREATE_PRIMITIVE, 805)
END_DECLARE_EVENT_TYPES()

#define EVT_GNR_CREATE_PRIMITIVE(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GNR_CREATE_PRIMITIVE, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (GNRCreatePrimitiveEventFunction) & fn, \
(wxObject *) NULL ),

#endif // GNRCREATEPRIMITIVEEVENT_H
