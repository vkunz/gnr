#ifndef _TESTCANVAS_H_
#define _TESTCANVAS_H_

#include <wx/glcanvas.h>
#include <wx/timer.h>

class TestCanvas : public wxGLCanvas
{
private:
	// attributes
	// stores value, if OGL ist initialized
	bool m_init;
	bool m_LMousePressed, m_MouseMoved;
	// stores value, if left mouse button is pressed
	
	// The Current Position Of The Mouse
	int	m_mouse_x, m_mouse_y;
	
	//
	GLdouble posx, posy, posz;
	
	// Timer to refresh the GL-Window
	wxTimer* m_timer;
	
	// share display list
	GLuint m_gllist;
	
	// handle to the GLContext
	wxGLContext* m_glContext;
	
	// functions
	// initialize the OGL-state-machine
	void InitGL();
	
	// track which object is selected
	void Selection();
	
	//
	void getGLPos(int x, int y);
	void beginDraw();
	void endDraw();
	// execute on size-event
	void OnSize(wxSizeEvent & event);
	
	// execute on timer-event
	void OnTimer(wxTimerEvent& event);
	
	// execute on left-mouse pressed event
	void OnLMouseDown(wxMouseEvent& event);
	
	// execute on left-mouse released event
	void OnLMouseUp(wxMouseEvent& event);
	
	// execute on right-mouse pressed event
	void OnMMouseDown(wxMouseEvent& event);
	
	// execute on right-mouse released event
	void OnMouseMove(wxMouseEvent& event);
	
	DECLARE_EVENT_TABLE();
	
protected:

public:

	// Ctor
	TestCanvas(wxWindow* parent,
	           wxWindowID id = wxID_ANY,
	           const wxPoint& pos = wxDefaultPosition,
	           const wxSize& size = wxDefaultSize,
	           long style = 0,
	           const wxString& name = wxT("TestGLCanvas"));
	           
	// Ctor with shared OpenGL state machine
	/*TestCanvas(wxWindow* parent,
	           const wxGLContext* shared,
	           wxWindowID id = wxID_ANY,
	           const wxPoint& pos = wxDefaultPosition,
	           const wxSize& size = wxDefaultSize,
	           long style = 0,
	           const wxString& name = wxT("TestGLCanvas"),
	           int* attribList = 0,
	           const wxPalette& palette = wxNullPalette);*/
	
	// Ctor
	TestCanvas(wxWindow *parent,
	           const TestCanvas *other,
	           wxWindowID id = wxID_ANY,
	           const wxPoint& pos = wxDefaultPosition,
	           const wxSize& size = wxDefaultSize,
	           long style = 0,
	           const wxString& name = wxT("TestGLCanvas"));
	           
	void DrawGLScene();
};

#endif // _TESTCANVAS_H_
