/**
 * declares the CreatePrimiveEvent-Class
 * @name        CreatePrimitiveEvent.h
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _CREATEPRIMITIVEEVENT_H_
#define _CREATEPRIMITIVEEVENT_H_

#include <wx/event.h>
#include <wx/string.h>

#include "Color.h"
#include "Enum.h"
#include "Vertex.h"

class CreatePrimitiveEvent : public wxNotifyEvent
{
private:
	primitiveType m_type;
	Vertex m_position;
	Vertex m_angles;
	Vertex m_dimensions;
	Color m_color;
	wxString m_name;

public:
	CreatePrimitiveEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	CreatePrimitiveEvent(const CreatePrimitiveEvent& event);
	virtual wxEvent* Clone() const;
	virtual ~CreatePrimitiveEvent();

	void setPrimitiveType(primitiveType type);

	void setPosition(Vertex pos);
	void setAngles(Vertex angles);
	void setDimensions(Vertex dim);
	void setColor(const Color& color);
	void setName(wxString name);

	primitiveType getPrimitiveType();

	Vertex getPosition();
	Vertex getAngles();
	Vertex getDimensions();
	const Color& getColor();
	wxString getName();

	DECLARE_DYNAMIC_CLASS(CreatePrimitiveEvent);
};

typedef void (wxEvtHandler::*CreatePrimitiveEventFunction)(CreatePrimitiveEvent&);

// GLNotify events and macros for handling them
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GNR_CREATE_PRIMITIVE, 805)
END_DECLARE_EVENT_TYPES()

#define EVT_GNR_CREATE_PRIMITIVE(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GNR_CREATE_PRIMITIVE, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (CreatePrimitiveEventFunction) & fn, \
(wxObject *) NULL ),

#endif // _CREATEPRIMITIVEEVENT_H_
