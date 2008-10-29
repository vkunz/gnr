/**
 * TestCanvas
 * @name        TestCanvas.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/dcclient.h>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <GL/glu.h>

#include "TestCanvas.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

int const ID_TIMER = wxNewId();

BEGIN_EVENT_TABLE(TestCanvas, wxGLCanvas)
	// Only a void EVENT_TABLE is a good EVENT_TABLE
END_EVENT_TABLE()

TestCanvas::TestCanvas(wxWindow* parent,
                       wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style,
                       const wxString& name) : wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name)
{
	// glContex pointing nowhere
	// m_glContext = (wxGLContext*) NULL;
	
	m_gllist = 0;
	
	// initialize GLContext
	m_glContext = new wxGLContext(this, NULL);
	
	// OpenGL not initialized
	m_init = false;
	
	// Mouse-Pressed = false
	m_LMousePressed = false;
	m_MMousePressed = false;
	m_RMousePressed = false;
	
	// Timer to refresh the GL-Window
	m_timer = new wxTimer(this, ID_TIMER);
	
	// Timer-Intervall in ms
	m_timer->Start(20);
	
	// TEMP-Values just for testing
	posx = 0.0f;
	posy = 0.0f;
	posz = -6.0f;
	zcoord = 0;
	
	phix = 0.0f;
	phiy = 0.0f;
	
	zfar  = 1000.0f;
	znear = 1.0f;
	
	GetClientSize(&window_w, &window_h);
	
	// Connect-methods to connect different Events with functions
	Connect(ID_TIMER, wxEVT_TIMER, (wxObjectEventFunction)&TestCanvas::OnTimer);
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&TestCanvas::OnSize);
	Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&TestCanvas::OnLMouseDown);
	Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&TestCanvas::OnLMouseUp);
	Connect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&TestCanvas::OnRMouseDown);
	Connect(wxEVT_RIGHT_UP, (wxObjectEventFunction)&TestCanvas::OnRMouseUp);
	Connect(wxEVT_MIDDLE_DOWN, (wxObjectEventFunction)&TestCanvas::OnMMouseDown);
	Connect(wxEVT_MIDDLE_UP, (wxObjectEventFunction)&TestCanvas::OnMMouseUp);
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&TestCanvas::OnMouseMove);
}

/*TestCanvas::TestCanvas(wxWindow* parent,
                       const wxGLContext* shared,
                       wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style,
                       const wxString& name,
                       int *attribList,
                       const wxPalette& palette) : wxGLCanvas(parent, shared, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name, attribList, palette)
{
    // glContext pointing nowhere
    //m_glContext = (wxGLContext*) NULL;

    //
    m_gllist = 0;

    //m_glContext = new wxGLContext(this, shared);

    // OpenGL not initialized
    m_init = false;

    // Timer to refresh the GL-Window
    m_timer = new wxTimer(this, ID_TIMER);

    // Start timer with an interval of 5 ms
    m_timer->Start(5);

    //
	posx = 0.0f;

	//
	posy = 0.0f;

	// Connect-methods to connect different Events with functions
	Connect(ID_TIMER, wxEVT_TIMER, (wxObjectEventFunction)&TestCanvas::OnTimer);
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&TestCanvas::OnSize);
	Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&TestCanvas::OnLMouseDown);
	Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&TestCanvas::OnLMouseUp);
	Connect(wxEVT_MIDDLE_DOWN, (wxObjectEventFunction)&TestCanvas::OnMMouseDown);
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&TestCanvas::OnMouseMove);
}*/

TestCanvas::TestCanvas(wxWindow *parent,
                       const TestCanvas* other,
                       wxWindowID id, const wxPoint& pos,
                       const wxSize& size,
                       long style,
                       const wxString& name) : wxGLCanvas(parent, other->GetContext(), id, pos, size, style|wxFULL_REPAINT_ON_RESIZE ,name)
{
	m_gllist = other->m_gllist;
}


// Ininitalize the OpenGL-Window
void TestCanvas::InitGL()
{
	// Set current OpenGL Frame
	SetCurrent();
	
	// Enable Smooth Shading
	glShadeModel(GL_SMOOTH);
	
	//set color for cleaning frame buffer
	glClearColor(0.5, 0.5, 0.5, 0.0);
	
	// Depth Buffer Setup
	glClearDepth(1.0f);
	
	// Enables Depth Testing
	glEnable(GL_DEPTH_TEST);
	
	// The type of depth Testing to do
	glDepthFunc(GL_LEQUAL);
	
	// Really nice perspective calculations
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void TestCanvas::OnSize(wxSizeEvent & event)
{
	GetClientSize(&window_w, &window_h);
	
	if (GetContext())
	{
		// Set current OpenGL Frame
		SetCurrent();
		
		//
		glViewport(0, 0, (GLint) window_w, (GLint) window_h);
		
		// Load and Reset Projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		// Calculate The Aspect Ratio Of The Window
		gluPerspective(45.0f, (GLfloat)window_w/window_h, znear, zfar);
		
		// Load and Reset Modelview
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

//!Painting the Objects to the GL-Window
void TestCanvas::DrawGLScene()
{
	// Clear The Scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Reset The Current Modelview Matrix
	glLoadIdentity();
	
	// Move
	glTranslatef(posx,posy,posz);
	glRotatef(phix,1.0f,0.0f,0.0f);
	glRotatef(phiy,0.0f,1.0f,0.0f);
	
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(firstPoint.getX(),firstPoint.getY());
	glVertex2f(secPoint.getX(),secPoint.getY());
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,  0.0f,  0.0f);     /* Rot                           		*/
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der Front der Pyramide	*/
	glColor3f(0.0f,  1.0f,  0.0f);     /* gruen                         		*/
	glVertex3f(-1.0f, -1.0f,  1.0f);   /* linker Punkt der Front der Pyramide	*/
	glColor3f(0.0f,  0.0f,  1.0f);     /* blau		                        */
	glVertex3f(1.0f, -1.0f,  1.0f);    /* rechter Punkt der Fornt der Pyramide      */
	
	glColor3f(1.0f,  0.0f,  0.0f);     /* Rot                           		   */
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der rechten Seite der Pyramide  */
	glColor3f(0.0f,  0.0f,  1.0f);     /* balau		                           */
	glVertex3f(1.0f, -1.0f,  1.0f);    /* linker Punkt der rechten Seite der Pyramide  */
	glColor3f(0.0f,  1.0f,  0.0f);     /* gruen                         		   */
	glVertex3f(1.0f, -1.0f, -1.0f);    /* rechter Punkt der rechten Seite der Pyramide */
	
	glColor3f(1.0f,  0.0f,  0.0f);     /* Rot                           		*/
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der Rueckseite der Pyramide	*/
	glColor3f(0.0f,  1.0f,  0.0f);     /* gruen                         		*/
	glVertex3f(1.0f, -1.0f, -1.0f);    /* linker Punkt der Rueckseite der Pyramide  */
	glColor3f(0.0f,  0.0f,  1.0f);     /* blau                                      */
	glVertex3f(-1.0f, -1.0f, -1.0f);   /* rechter Punkt der Rueckseite der Pyaramide*/
	
	glColor3f(1.0f,  0.0f,  0.0f);     /* Rot                           		 */
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der linken Seite der Pyramide */
	glColor3f(0.0f,  0.0f,  1.0f);     /* blau	                                 */
	glVertex3f(-1.0f, -1.0f, -1.0f);   /* linker Punkt der linken Seite der Pyramide */
	glColor3f(0.0f,  1.0f,  0.0f);     /* gruen                         		 */
	glVertex3f(-1.0f, -1.0f,  1.0f);   /* rechter Punkt der linken Seite der Pyramide*/
	glEnd();
}

// Drawing The Scene
void TestCanvas::OnTimer(wxTimerEvent& event)
{
	//wxPaintDC dc(this);
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

// Finding out which Object has been hit
void TestCanvas::Selection()  											// This Is Where Selection Is Done
{
	GLuint	buffer[512];										// Set Up A Selection Buffer
	GLint	hits;												// The Number Of Objects That We Selected
	
	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
	GLint	viewport[4];
	
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
	gluPickMatrix((GLdouble) m_mouse_x, (GLdouble)(viewport[3]-m_mouse_y), 1.0f, 1.0f, viewport);
	
	// Apply The Perspective Matrix
	gluPerspective(45.0f, (GLfloat)(viewport[2]-viewport[0])/(GLfloat)(viewport[3]-viewport[1]), znear, zfar);
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	DrawGLScene();												// Render The Targets To The Selection Buffer
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	hits=glRenderMode(GL_RENDER);								// Switch To Render Mode, Find Out How Many
	// Objects Were Drawn Where The Mouse Was
	if (hits > 0)  											// If There Were More Than 0 Hits
	{
		int	choose = buffer[3];									// Make Our Selection The First Object
		int depth = buffer[1];									// Store How Far Away It Is
		
		for (int loop = 1; loop < hits; loop++)  				// Loop Through All The Detected Hits
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

void TestCanvas::OnLMouseDown(wxMouseEvent& event)
{
	m_mouse_x = event.m_x;
	m_mouse_y = event.m_y;
	
	m_LMousePressed = true;
}

void TestCanvas::OnLMouseUp(wxMouseEvent& event)
{
	m_LMousePressed = false;
}

void TestCanvas::OnMMouseDown(wxMouseEvent& event)
{
	phiy_old = phiy;
	phix_old = phix;
	m_mouse_x = event.m_x;
	m_mouse_y = event.m_y;
	
	m_MMousePressed = true;
}

void TestCanvas::OnMMouseUp(wxMouseEvent& event)
{
	m_MMousePressed = false;
}

void TestCanvas::OnRMouseDown(wxMouseEvent& event)
{
	m_mouse_x = event.m_x;
	m_mouse_y = event.m_y;
	
	m_RMousePressed = true;
}

void TestCanvas::OnRMouseUp(wxMouseEvent& event)
{
	m_RMousePressed = false;
}

void TestCanvas::OnMouseMove(wxMouseEvent& event)
{
	if (m_LMousePressed)
	{
		posz -= (float)(m_mouse_y - event.m_y)/10.0;
		posx -= (float)(m_mouse_x - event.m_x)/360.0*fabs(posz);
		
		m_mouse_x = event.m_x;
		m_mouse_y = event.m_y;
	}
	else if (m_MMousePressed)
	{
		phiy  = phiy_old + 720.0*((float)(m_mouse_x - event.m_x)/(float)window_w);
		phix  = phix_old + 720.0*((float)(m_mouse_y - event.m_y)/(float)window_h);
	}
	else if (m_RMousePressed)
	{
		posy -= (float)(event.m_y - m_mouse_y)/300.0*fabs(posz);
		posx -= (float)(m_mouse_x - event.m_x)/300.0*fabs(posz);
		
		m_mouse_x = event.m_x;
		m_mouse_y = event.m_y;
	}
}

// Convert Mouse-Coordinates to GL-Coordinates
GNRVertex TestCanvas::getGLPos(int x, int y)
{
	glPushMatrix();
	glLoadIdentity();
	GLdouble modelview[16], projection[16];
	GLint viewport[4];
	float z;
	double xpos, ypos, zpos;
	
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);       //get the modelview matrix
	glGetDoublev(GL_PROJECTION_MATRIX, projection);     //get the projection matrix
	glGetIntegerv(GL_VIEWPORT, viewport);               //get the viewport
	
	//Read the window z co-ordinate (the z value on that point in unit cube)
	glReadPixels((int)x, (int)(viewport[3]-y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	
	//Unproject the window co-ordinates to find the world co-ordinates.
	gluUnProject((double)x, (double)(viewport[3]-y), (double)z, modelview, projection, viewport, &xpos, &ypos, &zpos);
	
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("2D x=") << x << _("\ty=") << y << _("\tz=") << z;
	msg << _("\t|\t3D x=") << xpos << _("\ty=") << ypos << _("\tz=") << zpos;
	//wxLogMessage(msg);
#endif
	
	glPopMatrix();
	GNRVertex glPoint(xpos, ypos, zpos);
	return glPoint;
}
