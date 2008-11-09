#ifndef HELPFRAME_H
#define HELPFRAME_H

#include <wx/frame.h>
#include <wx/html/htmlwin.h>

class HelpFrame: public wxFrame
{
public:

	HelpFrame(wxWindow* parent, wxWindowID id);
	virtual ~HelpFrame();
	
protected:

private:

};

#endif
