#ifndef _TESTCANVAS_H_
#define _TESTCANVAS_H_

#include <wx/glcanvas.h>
#include <wx/timer.h>

class TestCanvas : public wxGLCanvas
{
private:
	bool m_init;
	bool m_LMousePressed;
	int	m_mouse_x, m_mouse_y;		                        // The Current Position Of The Mouse
	GLdouble posx, posy;
	wxTimer* m_timer;
	
	
	void InitGL();
	void Selection();
	void getGLPos(int x, int y);
	
	void OnSize(wxSizeEvent & event);
	void OnTimer(wxTimerEvent& event);
	void OnLMouseDown(wxMouseEvent& event);
	void OnLMouseUp(wxMouseEvent& event);
	void OnMMouseDown(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	
	DECLARE_EVENT_TABLE();
	
protected:

public:

	// Ctor
	TestCanvas(wxWindow* parent,
	           wxWindowID id = wxID_ANY,
	           const wxPoint& pos = wxDefaultPosition,
	           const wxSize& size = wxDefaultSize, long style = 0,
	           const wxString& name = wxT("TestGLCanvas"));
	           
	void DrawGLScene();
};

#endif // _TESTCANVAS_H_
