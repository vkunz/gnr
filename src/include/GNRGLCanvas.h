#ifndef _GNRGLCANVAS_H_
#define _GNRGLCANVAS_H_

#include <wx/glcanvas.h>
#include <wx/timer.h>

class GNRGLCanvas : public wxGLCanvas
{
private:
	// Timer to refresh the GL-Window
	wxTimer* m_timer;
	
	// Drawing the GL-Scene
	void draw();
	void prepareDraw();
	
	void OnTimer(wxTimerEvent* event);
	
protected:
	int m_window_x, m_window_y;
	
	// Main initialisation of the GL-Engine
	virtual void initGL() = 0;
	
	virtual void setCamera() = 0;
	
	// Event-Functions
	virtual void OnResize(wxSizeEvent* event) = 0;
	
public:
	// constructor
	GNRGLCanvas(wxWindow* parent,
	            wxWindowID id = wxID_ANY,
	            const wxPoint& pos = wxDefaultPosition,
	            const wxSize& size = wxDefaultSize,
	            long style = 0,
	            const wxString& name = wxT("GNRGLCanvas"));
	            
	virtual ~GNRGLCanvas();
	
};

#endif // _GNRGLCANVAS_H_
