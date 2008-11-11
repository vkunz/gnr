#ifndef _GNRLIBRARYENTRY_H_
#define _GNRLIBRARYENTRY_H_

#include <wx/string.h>

class LibraryEntry
{
public:

	LibraryEntry();
	
	LibraryEntry(wxString name, wxString reference, unsigned int cat_id);
	
	virtual ~LibraryEntry();
	
	// functions
	// returns content as string
	wxString toString();
	
	// retunrs name
	wxString getName();
	// set name
	void setName(wxString name);
	
	// returns cat_id
	unsigned int getCategoryId();
	// returns cat_id
	void setCategoryId(unsigned int cat_id);
	
	// returns reference
	wxString getReference();
	// returns reference
	void setReference(wxString reference);
	
	
protected:

private:
	// attributes
	// EntryName
	wxString m_name;
	
	// Reference to oax-file
	wxString m_reference;
	
	// reference to groupid
	unsigned int m_categoryId;
};

#endif // _GNRLIBRARYENTRY_H_
