#ifndef _GNRLIBRARYGROUP_H_
#define _GNRLIBRARYGROUP_H_

#include <wx/string.h>

class GNRLibraryCategory
{
public:
	// ctor
	GNRLibraryCategory();
	
	GNRLibraryCategory(wxString name, unsigned int categoryId, unsigned int parentId);
	
	// dtor
	virtual ~GNRLibraryCategory();
	
	// functions
	// returns name
	wxString getName();
	
	// returns categoryid
	unsigned int getCategoryId();
	
	// returns parentId
	unsigned int getParentId();
	
	// set name
	void setName(wxString name);
	
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
