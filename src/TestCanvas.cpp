#include "TestCanvas.h"
#include <gl/glu.h>
#include <wx/msgdlg.h>
#include "wx/dcclient.h"

int const ID_TIMER = wxNewId();

BEGIN_EVENT_TABLE(TestCanvas, wxGLCanvas)
	EVT_TIMER(ID_TIMER, TestCanvas::OnTimer)
	EVT_SIZE(TestCanvas::OnSize)
END_EVENT_TABLE()

TestCanvas::TestCanvas(wxWindow *parent, wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size, long style,
                       const wxString& name) : wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name)
{
	m_gldata.initialized = false;
	
	m_gldata.beginx = 0.0f;
	m_gldata.beginy = 0.0f;
	m_gldata.zoom   = 45.0f;
	
	m_init = false;     //OpenGL not initialized
	
	m_timer = new wxTimer(this, ID_TIMER);  //Timer to refresh the GL-Window
	m_timer->Start(2000);                   //Timer-Intervall in ms
}

//!Ininitalize the OpenGL-Window
void TestCanvas::InitGL()
{
	SetCurrent();
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void TestCanvas::OnSize(wxSizeEvent & event)
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
		gluPerspective(45.0f, (GLfloat)w/h, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

//!Painting the Objects to the GL-Window
void TestCanvas::DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Scene
	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	glTranslatef(0.0f,0.0f,-6.0f);  					// Move
	glColor3f(1.0, 0.0, 0.0);                           // Set Color
	glBegin(GL_TRIANGLES);                              // Start Triangle
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top
	glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glVertex3f(1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle
	
	glTranslatef(-2.0f,0.0f,0.0f);  					// Move
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f,-0.5f, 0.5f);
	glEnd();
	
	glTranslatef(4.0f,0.0f,0.0f);  			    		// Move
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f,-0.5f, 0.5f);
	glEnd();
}

//! Drawing The Scene
void TestCanvas::OnTimer(wxTimerEvent& args)
{
	wxPaintDC dc(this);
	SetCurrent();
	if (!m_init)
	{
		InitGL();
		m_init = true;
	}
	DrawGLScene();
	glFlush();
	SwapBuffers();
}
