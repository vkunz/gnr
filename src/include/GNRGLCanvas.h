#ifndef _GNRGLCANVAS_H_
#define _GNRGLCANVAS_H_

#include <wx/glcanvas.h>
#include <wx/timer.h>

class GNRGLCanvas : public wxGLCanvas
{
private:
	// Timer to refresh the GL-Window
	wxTimer* m_timer;
	
	int m_mouse_x, m_mouse_y;
	
	void connectEvents();
	
	// Drawing the GL-Scene
	void draw();
	void prepareDraw();
	
	void selection();
	
	void OnLMouseDown(wxMouseEvent& event);
	void OnLMouseUp(wxMouseEvent& event);
	void OnTimer(wxTimerEvent& event);
	
protected:
	int m_window_x, m_window_y;
	
	virtual void initGL() = 0;
	
	virtual void setCamera() = 0;
	
	virtual void OnResize(wxSizeEvent& event) = 0;
	
public:
	// constructor
	GNRGLCanvas(wxWindow* parent,
	            wxWindowID id = wxID_ANY,
	            const wxPoint& pos = wxDefaultPosition,
	            const wxSize& size = wxDefaultSize,
	            long style = 0,
	            const wxString& name = wxT("GNRGLCanvas"));
	GNRGLCanvas(wxWindow* parent,
	            wxGLContext* sharedContext,
	            wxWindowID id = wxID_ANY,
	            const wxPoint& pos = wxDefaultPosition,
	            const wxSize& size = wxDefaultSize,
	            long style = 0,
	            const wxString& name = _("GNRGLCanvas"));
	            
	virtual ~GNRGLCanvas();
	
};

#endif // _GNRGLCANVAS_H_
