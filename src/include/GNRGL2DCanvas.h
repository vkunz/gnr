#ifndef _GNRGL2DCANVAS_H_
#define _GNRGL2DCANVAS_H_

#include "GNRGLCanvas.h"

class GNRGL2DCanvas : public GNRGLCanvas
{
private:
	void initGL();
	void setCamera();
	
	void OnResize(wxSizeEvent& event);
	
public:
	GNRGL2DCanvas(wxWindow* parent,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = wxT("GNRGL2DCanvas"));
	GNRGL2DCanvas(wxWindow* parent,
	              wxGLContext* sharedContext,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = _("GNRGL2DCanvas"));
	              
	~GNRGL2DCanvas() {}
	
};

#endif // _GNRGL2DCANVAS_H_
