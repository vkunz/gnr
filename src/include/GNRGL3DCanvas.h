#ifndef _GNRGL3DCANVAS_H_
#define _GNRGL3DCANVAS_H_

#include "GNRGLCanvas.h"

class GNRGL3DCanvas : public GNRGLCanvas
{
private:
	void initGL();
	void setCamera();
	
	void OnResize(wxSizeEvent* event);
	
public:
	GNRGL3DCanvas(wxWindow* parent,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = wxT("GNRGL3DCanvas"));
	~GNRGL3DCanvas() {}
	
};

#endif // _GNRGL3DCANVAS_H_
