#include "GNRTreeControlEvent.h"


DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_TREE_CONTROL)
IMPLEMENT_DYNAMIC_CLASS(GNRTreeControlEvent, wxNotifyEvent)


GNRTreeControlEvent::GNRTreeControlEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

GNRTreeControlEvent::GNRTreeControlEvent(const GNRTreeControlEvent& event): wxNotifyEvent(event) {}

wxEvent* GNRTreeControlEvent::Clone() const
{
	return new GNRTreeControlEvent(*this);
}

GNRTreeControlEvent::~GNRTreeControlEvent()
{
	//dtor
}

treeEventType GNRTreeControlEvent::getEventType()
{
	return m_eventType;
}

void GNRTreeControlEvent::setEventType(treeEventType type)
{
	m_eventType = type;
}

bool GNRTreeControlEvent::getCat()
{
	return m_cat;
}

void GNRTreeControlEvent::setCat(bool cat)
{
	m_cat = cat;
}

wxString GNRTreeControlEvent::getNewName()
{
	return m_newName;
}

void GNRTreeControlEvent::setNewName(wxString name)
{
	m_newName = name;
}

GNRAssembly* GNRTreeControlEvent::getAssembly()
{
	return m_assembly;
}

void GNRTreeControlEvent::setAssembly(GNRAssembly* assembly)
{
	m_assembly = assembly;
}
