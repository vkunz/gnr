#include "GNRCreatePrimitiveEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_CREATE_PRIMITIVE)
IMPLEMENT_DYNAMIC_CLASS(GNRCreatePrimitiveEvent, wxNotifyEvent)


GNRCreatePrimitiveEvent::GNRCreatePrimitiveEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

GNRCreatePrimitiveEvent::GNRCreatePrimitiveEvent(const GNRCreatePrimitiveEvent& event): wxNotifyEvent(event) {}

wxEvent* GNRCreatePrimitiveEvent::Clone() const
{
	return new GNRCreatePrimitiveEvent(*this);
}

GNRCreatePrimitiveEvent::~GNRCreatePrimitiveEvent() {}

void GNRCreatePrimitiveEvent::setPosition(GNRVertex pos)
{
	m_position = pos;
}

void GNRCreatePrimitiveEvent::setAngles(GNRVertex angles)
{
	m_angles = angles;
}

void GNRCreatePrimitiveEvent::setDimensions(GNRVertex dim)
{
	m_dimensions = dim;
}

void GNRCreatePrimitiveEvent::setPrimitiveType(primitivesType type)
{
	m_type = type;
}

GNRVertex GNRCreatePrimitiveEvent::getPosition()
{
	return m_position;
}

GNRVertex GNRCreatePrimitiveEvent::getAngles()
{
	return m_angles;
}

GNRVertex GNRCreatePrimitiveEvent::getDimensions()
{
	return m_dimensions;
}

primitivesType GNRCreatePrimitiveEvent::getPrimitiveType()
{
	return m_type;
}

