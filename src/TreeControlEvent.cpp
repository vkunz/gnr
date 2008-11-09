#include "TreeControlEvent.h"


DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_TREE_CONTROL)
IMPLEMENT_DYNAMIC_CLASS(TreeControlEvent, wxNotifyEvent)


TreeControlEvent::TreeControlEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

TreeControlEvent::TreeControlEvent(const TreeControlEvent& event): wxNotifyEvent(event) {}

wxEvent* TreeControlEvent::Clone() const
{
	return new TreeControlEvent(*this);
}

TreeControlEvent::~TreeControlEvent()
{
	//dtor
}

treeEventType TreeControlEvent::getEventType()
{
	return m_eventType;
}

void TreeControlEvent::setEventType(treeEventType type)
{
	m_eventType = type;
}

bool TreeControlEvent::getCat()
{
	return m_cat;
}

void TreeControlEvent::setCat(bool cat)
{
	m_cat = cat;
}

wxString TreeControlEvent::getNewName()
{
	return m_newName;
}

void TreeControlEvent::setNewName(wxString name)
{
	m_newName = name;
}

Assembly* TreeControlEvent::getAssembly()
{
	return m_assembly;
}

void TreeControlEvent::setAssembly(Assembly* assembly)
{
	m_assembly = assembly;
}
