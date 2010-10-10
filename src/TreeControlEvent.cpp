/**
 * TreeControlEvent
 * @name        TreeControlEvent.cpp
 * @date        2008-11-08
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
void TreeControlEvent::setCat(const bool& cat)
{
	m_cat = cat;
}

/**
 * get cat id
 * @return      unsigned int        cat or not
 */
unsigned int TreeControlEvent::getCatId()
{
	return m_cat_id;
}

/**
 * set cat id
 * @param[in]      cat_id              unsigned int cat id
 */
void TreeControlEvent::setCatId(const unsigned int& cat_id)
{
	m_cat_id = cat_id;
}

/**
 * get parent id
 * @return      unsigned int        cat or not
 */
unsigned int TreeControlEvent::getParentId()
{
	return m_parent_id;
}

/**
 * set parent id
 * @param[in]      parent_id              unsigned int parent id
 */
void TreeControlEvent::setParentId(const unsigned int& parent_id)
{
	m_parent_id = parent_id;
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
void TreeControlEvent::setNewName(const wxString& name)
{
	m_newName = name;
}

/**
 * get hash
 * @return        wxString          hash
 */
wxString TreeControlEvent::getHash()
{
	return m_hash;
}

/**
 * set hash
 * @param[in]        name          wxString hash
 */
void TreeControlEvent::setHash(const wxString& hash)
{
	m_hash = hash;
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

/**
 * get TreeLibraryItemData source
 * @return        TreeLibraryItemData*          source of drag
 */
TreeLibraryItemData* TreeControlEvent::getTreeItemSrc()
{
	return m_itemSrc;
}

/**
 * set TreeLibraryItemData source
 * @param[in]        item          TreeLibraryItemData source
 */
void TreeControlEvent::setTreeItemSrc(TreeLibraryItemData* item)
{
	m_itemSrc = item;
}

/**
 * get TreeLibraryItemData destination
 * @return        TreeLibraryItemData*          destination of drag
 */
TreeLibraryItemData* TreeControlEvent::getTreeItemDst()
{
	return m_itemDst;
}

/**
 * set TreeLibraryItemData destination
 * @param[in]        item          wxTreeItemId source
 */
void TreeControlEvent::setTreeItemDst(TreeLibraryItemData* item)
{
	m_itemDst = item;
}
