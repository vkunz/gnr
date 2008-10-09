#include <gl/glu.h>

#include "GNRGL3DCanvas.h"

#define ZNEAR 0.1f
#define ZFAR 1000.0f

GNRGL3DCanvas::GNRGL3DCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:GNRGLCanvas(parent, id, pos, size, style, name)
{

	initGL();
}

GNRGL3DCanvas::GNRGL3DCanvas(wxWindow* parent, wxGLContext* sharedContext, wxWindowID id, const wxPoint& pos, const wxSize& size,
                             long style, const wxString& name) : GNRGLCanvas(parent, sharedContext, id, pos, size, style, name)
{
	initGL();
}

void GNRGL3DCanvas::initGL()
{
	// set current GL-Frame
	SetCurrent();
	
	glClearColor(0.5, 0.5, 0.5, 0.0);
	
	// alizing 3D models
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glEnable(GL_COLOR_MATERIAL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GNRGL3DCanvas::OnResize(wxSizeEvent* event)
{
	// set current GL-Frame
	SetCurrent();
	
	//get canvas-size
	GetClientSize(&m_window_x, &m_window_y);
	
	// set viewport with resolution
	glViewport(0, 0, m_window_x, m_window_y);
	
	// Load and Reset Modelview
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (float)m_window_x / (float)m_window_y, ZNEAR, ZFAR);
	
	// Load and Reset Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GNRGL3DCanvas::setCamera()
{
	// nothing do to
}
