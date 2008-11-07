#ifndef _GNRTREELIBRARYITEMDATA_H_
#define _GNRTREELIBRARYITEMDATA_H_

#include <wx/treectrl.h>
#include <wx/string.h>

class GNRTreeLibraryItemData : public wxTreeItemData
{
public:
	// ctor
	GNRTreeLibraryItemData();
	
	// dtor
	virtual ~GNRTreeLibraryItemData();
	
	void setCat(bool cat);
	bool getCat();
	
	void setName(wxString name);
	wxString getName();
	
protected:

private:
	// attributes
	bool m_category;
	wxString m_name;
};

#endif // _GNRTREELIBRARYITEMDATA_H_
