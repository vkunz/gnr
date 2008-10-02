#include "TestCanvas.h"
#include <gl/glu.h>
#include <wx/dcclient.h>

#include <wx/msgdlg.h>
#include <wx/string.h>

int const ID_TIMER = wxNewId();

BEGIN_EVENT_TABLE(TestCanvas, wxGLCanvas)
	EVT_TIMER(ID_TIMER, TestCanvas::OnTimer)
	EVT_SIZE(TestCanvas::OnSize)
	EVT_LEFT_DOWN(TestCanvas::Selection)
END_EVENT_TABLE()

TestCanvas::TestCanvas(wxWindow *parent, wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size, long style,
                       const wxString& name) : wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name)
{
	//m_gldata.initialized = false;
	
	//m_gldata.beginx = 0.0f;
	//m_gldata.beginy = 0.0f;
	//m_gldata.zoom   = 45.0f;
	
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
		gluPerspective(45.0f, (GLfloat)w/h, 0.1f, 100.0f);  // Calculate The Aspect Ratio Of The Window
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
	glLoadName(1);
	glPushMatrix();					    				// Push The Modelview Matrix (for naming the Object)
	glBegin(GL_TRIANGLES);                              // Start Triangle
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top
	glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glVertex3f(1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle
	glPopMatrix();							       				// Pop The Modelview Matrix*/
	
	glTranslatef(-2.0f,0.0f,0.0f);  					// Move
	glLoadName(2);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f,-0.5f, 0.5f);
	glEnd();
	glPopMatrix();
	
	glTranslatef(4.0f,0.0f,0.0f);  			    		// Move
	glLoadName(3);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f,-0.5f, 0.5f);
	glEnd();
	glPopMatrix();
}

//! Drawing The Scene
void TestCanvas::OnTimer(wxTimerEvent& args)
{
	//wxPaintDC dc(this);
	SetCurrent();
	if (!m_init)
	{
		InitGL();
		m_init = true;
	}
	DrawGLScene();
	//glFlush();
	SwapBuffers();
}

void TestCanvas::Selection(wxMouseEvent &event)  											// This Is Where Selection Is Done
{
	GLuint	buffer[512];										// Set Up A Selection Buffer
	GLint	hits;												// The Number Of Objects That We Selected
	
	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
	GLint	viewport[4];
	
	//Store Mouse-Coordinates
	mouse_x = event.m_x;
	mouse_y = event.m_y;
	
	// This Sets The Array <viewport> To The Size And Location Of The Screen Relative To The Window
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(512, buffer);								// Tell OpenGL To Use Our Array For Selection
	
	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	(void) glRenderMode(GL_SELECT);
	
	glInitNames();												// Initializes The Name Stack
	glPushName(0);												// Push 0 (At Least One Entry) Onto The Stack
	
	glMatrixMode(GL_PROJECTION);								// Selects The Projection Matrix
	glPushMatrix();												// Push The Projection Matrix
	glLoadIdentity();											// Resets The Matrix
	
	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	gluPickMatrix((GLdouble) mouse_x, (GLdouble)(viewport[3]-mouse_y), 1.0f, 1.0f, viewport);
	
	// Apply The Perspective Matrix
	gluPerspective(45.0f, (GLfloat)(viewport[2]-viewport[0])/(GLfloat)(viewport[3]-viewport[1]), 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	DrawGLScene();												// Render The Targets To The Selection Buffer
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	hits=glRenderMode(GL_RENDER);								// Switch To Render Mode, Find Out How Many
	// Objects Were Drawn Where The Mouse Was
	if (hits > 0)												// If There Were More Than 0 Hits
	{
		int	choose = buffer[3];									// Make Our Selection The First Object
		int depth = buffer[1];									// Store How Far Away It Is
		
		for (int loop = 1; loop < hits; loop++)					// Loop Through All The Detected Hits
		{
			// If This Object Is Closer To Us Than The One We Have Selected
			if (buffer[loop*4+1] < GLuint(depth))
			{
				choose = buffer[loop*4+3];						// Select The Closer Object
				depth = buffer[loop*4+1];						// Store How Far Away It Is
			}
		}
		wxString str;
		str << _("Objekt ") << choose << _(" Hit");
		wxMessageBox(str, _("GL Selection"));
	}
}
