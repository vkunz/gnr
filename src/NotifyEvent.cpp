/**
 * NotifyEvent
 * @name        NotifyEvent.cpp
 * @date        2008-10-24
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "NotifyEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_NOTIFY)
IMPLEMENT_DYNAMIC_CLASS(NotifyEvent, wxNotifyEvent)


NotifyEvent::NotifyEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

NotifyEvent::NotifyEvent(const NotifyEvent& event): wxNotifyEvent(event) {}

wxEvent* NotifyEvent::Clone() const
{
	return new NotifyEvent(*this);
}

void NotifyEvent::setGNREventType(int type)
{
	eventType = type;
}

bool NotifyEvent::getBoolean()
{
	return eventBoolean;
}

void NotifyEvent::setBoolean(bool status)
{
	eventBoolean = status;
}

int NotifyEvent::getGNREventType()
{
	return eventType;
}

void NotifyEvent::setSnapToGrid(int value)
{
	eventSnapToGrid = value;
}

int NotifyEvent::getSnapToGrid()
{
	return eventSnapToGrid;
}

void NotifyEvent::setSnapToAngle(int value)
{
	eventSnapToAngle = value;
}

int NotifyEvent::getSnapToAngle()
{
	return eventSnapToAngle;
}

void NotifyEvent::setAssemblyDataPointer(AssemblyData* data)
{
	m_data = data;
}

AssemblyData* NotifyEvent::getAssemblyDataPointer()
{
	return m_data;
}

void NotifyEvent::setAssemblyPtr(Assembly* a)
{
	assembly = a;
}

Assembly* NotifyEvent::getAssemblyPtr()
{
	return assembly;
}

void NotifyEvent::setFloat(float value)
{
	m_float = value;
}

float NotifyEvent::getFloat()
{
	return m_float;
}
