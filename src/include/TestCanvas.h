#ifndef _TESTCANVAS_H_
#define _TESTCANVAS_H_

#include <wx/glcanvas.h>
#include <wx/timer.h>

/*struct GLData {
	bool initialized;           // have OpenGL been initialized?
	float beginx, beginy;       // position of mouse
	float quat[4];              // orientation of object
	float zoom;                 // field of view in degrees
};*/

class TestCanvas : public wxGLCanvas
{
private:
	//GLData m_gldata;
	wxTimer* m_timer;
	bool m_init;
	bool m_LMousePressed;
	int	m_mouse_x, m_mouse_y;		                        // The Current Position Of The Mouse
	
	GLdouble posx, posy;
	
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
	TestCanvas(wxWindow* parent, wxWindowID id = wxID_ANY,
	           const wxPoint& pos = wxDefaultPosition,
	           const wxSize& size = wxDefaultSize, long style = 0,
	           const wxString& name = wxT("TestGLCanvas"));
	void DrawGLScene();
	
};


#endif // _TESTCANVAS_H_
