/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * the glcanvas class implements the initialization, event-functions,
 * selection and drawing methods that have 2D and 3D in common
 *
 * @name        GNRGLCanvas.cpp
 * @date        2008-10-08
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <gl/glu.h>

#include "GNRGLCanvas.h"

#if defined(__WXDEBUG__)
#include <wx/log.h>
#endif

#define ZNEAR 0.1f
#define ZFAR 1000.0f

int const ID_TIMER = wxNewId();

/**
 * constructor of GNRGLCanvas
 * @param       wxWindow*       Parent-Window
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name
 * @access      public
 */
GNRGLCanvas::GNRGLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		: wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name)
{

	// Timer to refresh the GL-Window
	m_timer = new wxTimer(this, ID_TIMER);
	m_timer->Start(40);
	
	connectEvents();
}

/**
 * constructor of GNRGLCanvas
 * @param       wxWindow*       Parent-Window
 * @param       wxGLContext*    Used GLContext for common Context
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name
 * @access      public
 */
GNRGLCanvas::GNRGLCanvas(wxWindow* parent, wxGLContext* sharedContext, wxWindowID id, const wxPoint& pos, const wxSize& size,
                         long style, const wxString& name) : wxGLCanvas(parent, sharedContext, id, pos, size, style, name)
{

	// Timer to refresh the GL-Window
	m_timer = new wxTimer(this, ID_TIMER);
	m_timer->Start(40);
	
	connectEvents();
}

/**
 * Connecting the events needed for the Canvas
 * @access      private
 */
void GNRGLCanvas::connectEvents()
{
	// Connect-methods to connect different Events with functions
	Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseDown);
	Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseUp);
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&GNRGLCanvas::OnLeaveWindow);
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&GNRGLCanvas::OnResize);
	Connect(ID_TIMER, wxEVT_TIMER, (wxObjectEventFunction)&GNRGLCanvas::OnTimer);
}

/**
 * Runs every time the Timer fires an event and does the drawing of the GL-Scene
 * @param       wxTimerEvent&       Timer-Event
 * @access      private
 */
void GNRGLCanvas::OnTimer(wxTimerEvent& event)
{
	prepareDraw();
	setCamera();
	draw();
	glFlush();
	SwapBuffers();
}

/**
 * Clears the screen and does all the work that has to be done before drawing
 * @access      private
 */
void GNRGLCanvas::prepareDraw()
{
	// set current GL-Context as activ
	SetCurrent();
	
	// Clear the Window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Reset The Current Modelview Matrix
	glLoadIdentity();
}

/**
 * Does the real drawing
 * @access      private
 */
void GNRGLCanvas::draw()
{
	glTranslatef(0.0f, 0.0f, -6.0f);
	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,  0.0f,  0.0f);     /* Rot                           		*/
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der Front der Pyramide	*/
	glVertex3f(-1.0f, -1.0f,  1.0f);   /* linker Punkt der Front der Pyramide	*/
	glVertex3f(1.0f, -1.0f,  1.0f);    /* rechter Punkt der Fornt der Pyramide      */
	
	glColor3f(0.0f,  1.0f,  0.0f);     /* gruen                         		*/
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der rechten Seite der Pyramide  */
	glVertex3f(1.0f, -1.0f,  1.0f);    /* linker Punkt der rechten Seite der Pyramide  */
	glVertex3f(1.0f, -1.0f, -1.0f);    /* rechter Punkt der rechten Seite der Pyramide */
	
	glColor3f(0.0f,  0.0f,  1.0f);     /* blau		                           */
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der Rueckseite der Pyramide	*/
	glVertex3f(1.0f, -1.0f, -1.0f);    /* linker Punkt der Rueckseite der Pyramide  */
	glVertex3f(-1.0f, -1.0f, -1.0f);   /* rechter Punkt der Rueckseite der Pyaramide*/
	
	glColor3f(1.0f,  1.0f,  0.0f);     /* Gelb                           		 */
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der linken Seite der Pyramide */
	glVertex3f(-1.0f, -1.0f, -1.0f);   /* linker Punkt der linken Seite der Pyramide */
	glVertex3f(-1.0f, -1.0f,  1.0f);   /* rechter Punkt der linken Seite der Pyramide*/
	glEnd();
}

/**
 * Checks which GL-Object has been selected by the mouse in the GL-Scene
 * @param       int     Mouse-X-Coordinate
 * @param       int     Mouse-Y-Coordinate
 * @return      int     GL-Object-ID
 * @access      private
 */
int GNRGLCanvas::selection(int mouse_x, int mouse_y)
{
	SetCurrent();
	// Finding out which Object has been hit
	GLuint	buffer[512];										// Set Up A Selection Buffer
	GLint	hits;												// The Number Of Objects That We Selected
	
	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
	GLint	viewport[4];
	
	// This Sets The Array <viewport> To The Size And Location Of The Screen Relative To The Window
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(512, buffer);								// Tell OpenGL To Use Our Array For Selection
	
	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	glRenderMode(GL_SELECT);
	
	glInitNames();												// Initializes The Name Stack
	glPushName(0);												// Push 0 (At Least One Entry) Onto The Stack
	
	glMatrixMode(GL_PROJECTION);								// Selects The Projection Matrix
	glPushMatrix();												// Push The Projection Matrix
	glLoadIdentity();											// Resets The Matrix
	
	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	gluPickMatrix((GLdouble) mouse_x, (GLdouble)(viewport[3]-mouse_y), 1.0f, 1.0f, viewport);
	
	// Apply The Perspective Matrix
	setPerspective();
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	prepareDraw();
	setCamera();
	draw();												// Render The Targets To The Selection Buffer
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
#if defined(__WXDEBUG__)
		wxString msg;
		msg << _("Objekt ") << choose << _(" Hit");
		wxLogMessage(msg);
#endif
		return choose;
	}
}

/**
 * fetches the Left-Mouse-Pressed event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnLMouseDown(wxMouseEvent& event)
{
	selection(event.m_x, event.m_y);
	void GNRGLCanvas::OnLMouseDown(wxMouseEvent& event)
	{
		//GNRMouse::GetControl(event);
	}
	
	/**
	 * fetches the Left-Mouse-Up event
	 * @param       wxMouseEvent    Mouse-Event of current canvas
	 * @access      private
	 */
	void GNRGLCanvas::OnLMouseUp(wxMouseEvent& event)
	{
		//GNRMouse::DropControl(event);
	}
	
	/**
	 * fetches the Mouse-Move event
	 * @param       wxMouseEvent    Mouse-Event of current canvas
	 * @access      private
	 */
	void GNRGLCanvas::OnMouseMove(wxMouseEvent& event)
	{
	
	}
	
	/**
	 * fetches the Leave-Window event
	 * @param       wxMouseEvent    Mouse-Event of current canvas
	 * @access      private
	 */
	void GNRGLCanvas::OnLeaveWindow(wxMouseEvent& event)
	{
	
	}
	
	/**
	 * destructor of GNRGLCanvas
	 * @access      public
	 */
	GNRGLCanvas::~GNRGLCanvas() {}
	