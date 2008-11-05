#ifndef GNRHELPFRAME_H
#define GNRHELPFRAME_H

#include <wx/frame.h>
#include <wx/html/htmlwin.h>

class GNRHelpFrame: public wxFrame
{
public:

	GNRHelpFrame(wxWindow* parent, wxWindowID id);
	virtual ~GNRHelpFrame();
	
protected:

	static const long ID_HTMLWINDOW1;
	
private:
	wxHtmlWindow* m_window;
	
};

#endif
