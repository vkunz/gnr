/**
 * GNRNotifyEvent
 * @name        GNRNotifyEvent.cpp
 * @date        2008-10-24
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRNotifyEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_NOTIFY)
IMPLEMENT_DYNAMIC_CLASS(GNRNotifyEvent, wxNotifyEvent)


GNRNotifyEvent::GNRNotifyEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

GNRNotifyEvent::GNRNotifyEvent(const GNRNotifyEvent& event): wxNotifyEvent(event) {}

wxEvent* GNRNotifyEvent::Clone() const
{
	return new GNRNotifyEvent(*this);
}

void GNRNotifyEvent::setGNREventType(int type)
{
	eventType = type;
}

int GNRNotifyEvent::getGNREventType()
{
	return eventType;
}

void GNRNotifyEvent::setSnapToGrid(int value)
{
	eventSnapToGrid = value;
}

int GNRNotifyEvent::getSnapToGrid()
{
	return eventSnapToGrid;
}

void GNRNotifyEvent::setSnapToAngle(int value)
{
	eventSnapToAngle = value;
}

int GNRNotifyEvent::getSnapToAngle()
{
	return eventSnapToAngle;
}

void GNRNotifyEvent::setFrameDataPointer(GNRFrameData* data)
{
	m_data = data;
}

GNRFrameData* GNRNotifyEvent::getFrameDataPointer()
{
	return m_data;
}

void GNRNotifyEvent::setAssemblyPtr(GNRAssembly* a)
{
	assembly = a;
}

GNRAssembly* GNRNotifyEvent::getAssemblyPtr()
{
	return assembly;
}

void GNRNotifyEvent::setFloat(float value)
{
	m_float = value;
}

float GNRNotifyEvent::getFloat()
{
	return m_float;
}
