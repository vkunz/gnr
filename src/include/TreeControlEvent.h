/**
 * TreeControlEvent
 * @name        TreeControlEvent.h
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _TREECONTROLEVENT_H_
#define _TREECONTROLEVENT_H_

#include <wx/event.h>

#include "Enum.h"

class Assembly;
class TreeLibraryItemData;

class TreeControlEvent: public wxNotifyEvent
{
public:
	TreeControlEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	TreeControlEvent(const TreeControlEvent& event);
	virtual wxEvent* Clone() const;
	virtual ~TreeControlEvent();

	treeEventType getEventType();
	void setEventType(treeEventType type);

	bool getCat();
	void setCat(const bool& cat);

	unsigned int getCatId();
	void setCatId(const unsigned int& cat_id);

	unsigned int getParentId();
	void setParentId(const unsigned int& parent_id);

	wxString getNewName();
	void setNewName(const wxString& name);

	wxString getHash();
	void setHash(const wxString& hash);

	Assembly* getAssembly();
	void setAssembly(Assembly* assembly);

	TreeLibraryItemData* getTreeItemDst();
	void setTreeItemDst(TreeLibraryItemData* item);

	TreeLibraryItemData* getTreeItemSrc();
	void setTreeItemSrc(TreeLibraryItemData* item);

protected:
private:
	treeEventType m_eventType;

	bool m_cat;
	unsigned int m_cat_id;
	unsigned int m_parent_id;

	wxString m_hash;
	wxString m_newName;
	Assembly* m_assembly;

	TreeLibraryItemData* m_itemSrc;
	TreeLibraryItemData* m_itemDst;

	DECLARE_DYNAMIC_CLASS(TreeControlEvent);
};


typedef void (wxEvtHandler::*TreeControlEventFunction)(TreeControlEvent&);

// GLNotify events and macros for handling them
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_GNR_TREE_CONTROL, 806)
END_DECLARE_EVENT_TYPES()

#define EVT_GNR_TREE_CONTROL(id, fn) DECLARE_EVENT_TABLE_ENTRY( \
wxEVT_COMMAND_GNR_TREE_CONTROL, id, -1, (wxObjectEventFunction) \
(wxEventFunction) (TreeControlEventFunction) & fn, \
(wxObject *) NULL ),

#endif // _TREECONTROLEVENT_H_
