#include "TestCanvas.h"
//#include <gl/glu.h>
#include <wx/msgdlg.h>
#include "wx/dcclient.h"


TestCanvas::TestCanvas(wxWindow *parent, wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size, long style,
                       const wxString& name) : wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name)
{
	m_gldata.initialized = false;
	
	m_gldata.beginx = 0.0f;
	m_gldata.beginy = 0.0f;
	m_gldata.zoom   = 45.0f;
	
	wxPaintDC dc(this);
	this->InitGL();
	this->ResetProjectionMode();
	//this->DrawGLScene();
	
}

void TestCanvas::InitGL()
{
	SetCurrent();
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}

void TestCanvas::ResetProjectionMode()
{
	int w, h;
	GetClientSize(&w, &h);
#ifndef __WXMOTIF__
	if (GetContext())
#endif
	{
		SetCurrent();
		glViewport(0, 0, (GLint) w, (GLint) h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)w/h, 1.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

void TestCanvas::DrawGLScene()
{
	SetCurrent();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top
	glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glVertex3f(1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle


	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f,-0.5f, 0.5f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle


	SwapBuffers();
}
