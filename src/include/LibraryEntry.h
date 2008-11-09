#ifndef _GNRLIBRARYENTRY_H_
#define _GNRLIBRARYENTRY_H_

#include <wx/string.h>

class LibraryEntry
{
public:
	// ctor
	LibraryEntry();
	
	LibraryEntry(wxString name, wxString reference, unsigned int categoryId);
	
	// dtor
	virtual ~LibraryEntry();
	
	// functions
	// returns content as string
	wxString toString();
	
	// retunrs name
	wxString getName();
	
	// returns categoryId
	unsigned int getCategoryId();
	
	// returns reference
	wxString getReference();
	
	// set name
	void setName(wxString name);
	
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
