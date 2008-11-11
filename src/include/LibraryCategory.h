#ifndef _GNRLIBRARYGROUP_H_
#define _GNRLIBRARYGROUP_H_

#include <wx/string.h>

class LibraryCategory
{
public:
	// ctor
	LibraryCategory();
	
	LibraryCategory(wxString name, unsigned int cat_id, unsigned int parent_id);
	
	// dtor
	virtual ~LibraryCategory();
	
	// functions
	// returns name
	wxString getName();
	
	// set name
	void setName(wxString name);
	
	// returns categoryid
	unsigned int getCatId();
	
	// set categoryid
	void setCatId(unsigned int cat_id);
	
	// returns parentId
	unsigned int getParentId();
	
	// set parentId
	void setParentId(unsigned int parent_id);
	
	// functions
	// returns content as string
	wxString toString();
	
protected:

private:
	// attributes
	// group Name
	wxString m_name;
	
	// id of this group
	unsigned int m_categoryId;
	
	// parent id of this group
	unsigned int m_parentId;
};

#endif // _GNRLIBRARYGROUP_H_
