#ifndef _GNRTREELIBRARYITEMDATA_H_
#define _GNRTREELIBRARYITEMDATA_H_

#include <wx/treectrl.h>
#include <wx/string.h>

class TreeLibraryItemData : public wxTreeItemData
{
public:
	// ctor
	TreeLibraryItemData();
	
	// dtor
	virtual ~TreeLibraryItemData();
	
	void setCat(bool cat);
	bool getCat();
	
	void setCatId(unsigned int cat_id);
	unsigned int getCatId();
	
	void setParentId(unsigned int parent_id);
	unsigned int getParentId();
	
	void setName(wxString name);
	wxString getName();
	
	void setHash(wxString hash);
	wxString getHash();
	
protected:

private:
	// attributes
	bool m_category;
	unsigned int m_category_id;
	unsigned int m_parent_id;
	wxString m_name;
	wxString m_hash;
};

#endif // _GNRTREELIBRARYITEMDATA_H_
