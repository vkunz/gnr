#ifndef _GNRASSEMBLYPART_H_
#define _GNRASSEMBLYPART_H_

#include <wx/string.h>

class GNRAssemblyPart
{
public:
	// ctor
	GNRAssemblyPart();
	
	// dtor
	virtual ~GNRAssemblyPart();
	
protected:

private:
	// attributes
	
	// AssemblyPart title
	wxString m_title;
};

#endif // _GNRASSEMBLYPART_H_
