#ifndef _GNRLIBRARYENTRY_H_
#define _GNRLIBRARYENTRY_H_

#include <wx/string.h>

class GNRLibraryEntry
{
public:
	// ctor
	GNRLibraryEntry();
	
	GNRLibraryEntry(wxString name, wxString reference, unsigned int categoryId);
	
	// dtor
	virtual ~GNRLibraryEntry();
	
	// functions
	// returns content as string
	wxString toString();
	
	// returns categoryId
	unsigned int getCategoryId();
	
	// retunrs name
	wxString getName();
	
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
