#include "TreeControlEvent.h"


DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_TREE_CONTROL)
IMPLEMENT_DYNAMIC_CLASS(TreeControlEvent, wxNotifyEvent)


/**
 * constructor of TreeControlEvent
 * @param[in]   commandType          wxEventType type of event
 * @param[in]   id                   int id of command
 */
TreeControlEvent::TreeControlEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

/**
 * copy constructor of TreeControlEvent
 * @param[in]   event               TreeControlEvent&
 */
TreeControlEvent::TreeControlEvent(const TreeControlEvent& event): wxNotifyEvent(event) {}

/**
 * clone an event
 * @return      wxEvent*        cloned event
 */
wxEvent* TreeControlEvent::Clone() const
{
	return new TreeControlEvent(*this);
}

/**
 * destructor of TreeControlEvent
 */
TreeControlEvent::~TreeControlEvent()
{
}

/**
 * get event type of event
 * @return      treeEventType       type of event
 */
treeEventType TreeControlEvent::getEventType()
{
	return m_eventType;
}

/**
 * set event type of event
 * @param[in]      type         treeEventType type of event
 */
void TreeControlEvent::setEventType(treeEventType type)
{
	m_eventType = type;
}

/**
 * get cat or not
 * @return      bool        cat or not
 */
bool TreeControlEvent::getCat()
{
	return m_cat;
}

/**
 * set cat or not
 * @param[in]      cat              bool, if cat or not
 */
void TreeControlEvent::setCat(bool cat)
{
	m_cat = cat;
}

/**
 * get new name
 * @return        wxString          new name
 */
wxString TreeControlEvent::getNewName()
{
	return m_newName;
}

/**
 * set new name
 * @param[in]        name          wxString new name
 */
void TreeControlEvent::setNewName(wxString name)
{
	m_newName = name;
}

/**
 * get assembly involved
 * @return        Assembly*          pointer to assembly
 */
Assembly* TreeControlEvent::getAssembly()
{
	return m_assembly;
}

/**
 * set assembly involved
 * @param[in]        assembly          Assembly* pointer to assembly
 */
void TreeControlEvent::setAssembly(Assembly* assembly)
{
	m_assembly = assembly;
}
