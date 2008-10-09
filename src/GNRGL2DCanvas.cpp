#include <gl/glu.h>

#include "GNRGL2DCanvas.h"

#define ZNEAR 0.1f
#define ZFAR 1000.0f

GNRGL2DCanvas::GNRGL2DCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:GNRGLCanvas(parent, id, pos, size, style, name)
{

	initGL();
}

void GNRGL2DCanvas::initGL()
{
	// set current GL-Frame
	SetCurrent();
	
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	//glEnable(GL_TEXTURE_2D);   // textures
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GNRGL2DCanvas::OnResize(wxSizeEvent* event)
{
	// set current GL-Frame
	SetCurrent();
	
	//get canvas-size
	GetClientSize(&m_window_x, &m_window_y);
	
	glViewport(0, 0, m_window_x, m_window_y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-40, 40, 30, -30, ZNEAR, ZFAR);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GNRGL2DCanvas::setCamera()
{
	// set camera-position
	gluLookAt(0,15,0,0,1,0,0,0,1);
}
