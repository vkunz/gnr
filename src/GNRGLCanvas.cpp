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

#ifdef _WIN32
#include <gl/glu.h>
#endif

#include "GNRGLCanvas.h"
#include "GNRGLNotifyEvent.h"

#if defined(__ATHOS_DEBUG__)
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
	initGL();
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
	initGL();
	connectEvents();
}

/**
 * Connecting the events needed for the Canvas
 * @access      private
 */
void GNRGLCanvas::connectEvents()
{
	// Connect-methods to connect different Events with functions
	Connect(wxEVT_MIDDLE_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnMMouseDown);
	Connect(wxEVT_MIDDLE_UP, (wxObjectEventFunction)&GNRGLCanvas::OnMMouseUp);
	Connect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnRMouseDown);
	Connect(wxEVT_RIGHT_UP, (wxObjectEventFunction)&GNRGLCanvas::OnRMouseUp);
	Connect(wxEVT_LEFT_DCLICK, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseDblClick);
	Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseDown);
	Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseUp);
	Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&GNRGLCanvas::OnLeaveWindow);
	Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&GNRGLCanvas::OnEnterWindow);
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&GNRGLCanvas::OnResize);
}

/**
 * does the initialization for the 3D canvas
 * @access      protected
 */
void GNRGLCanvas::initGL()
{
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("GNRGLCanvas::initGL()");
	wxLogMessage(msg);
#endif
	
	// Create light components
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };
//      GLuint	texture;
//
//      glBindTexture(GL_TEXTURE_2D, texture);
//      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
//      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image_size_x, image_size_y, GL_RGB, GL_UNSIGNED_BYTE, image_data);
//
//	    SetCurrent();
//	    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	// set current GL-Frame
	SetCurrent();
	
	glClearColor(0.5, 0.5, 0.5, 0.0);
	
	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	
	// enable lightning
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glShadeModel(GL_SMOOTH);
	
	glClearDepth(1.0f);
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

/**
 * flush the buffer to screen
 * @access      public
 */
void GNRGLCanvas::glFlush()
{
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
	
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClearDepth(1.0f);	// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glEnable(GL_COLOR_MATERIAL);
	
	int topleft_x = 0;
	int topleft_y = 0;
	int bottomrigth_x;
	int bottomrigth_y;
	GetClientSize(&bottomrigth_x, &bottomrigth_y);
	
	glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float ratio_w_h = (float)(bottomrigth_x-topleft_x)/(float)(bottomrigth_y-topleft_y);
	gluPerspective(45 /*view angle*/, ratio_w_h, 0.1 /*clip close*/, 200 /*clip far*/);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	// Set Up A Selection Buffer
	GLuint	buffer[512];
	// The Number Of Objects That We Selected
	GLint	hits;
	
	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
	GLint	viewport[4];
	
	// This Sets The Array <viewport> To The Size And Location Of The Screen Relative To The Window
	glGetIntegerv(GL_VIEWPORT, viewport);
	// Tell OpenGL To Use Our Array For Selection
	glSelectBuffer(512, buffer);
	
	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	glRenderMode(GL_SELECT);
	
	// Initializes The Name Stack
	glInitNames();
	// Push 0 (At Least One Entry) Onto The Stack
	glPushName(0);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		glLoadIdentity();
		
		// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
		gluPickMatrix((GLdouble) mouse_x, (GLdouble)(viewport[3]-mouse_y), 5.0f, 5.0f, viewport);
		
		// Apply The Perspective Matrix
		setPerspective();
		glMatrixMode(GL_MODELVIEW);
		
		// Reset The Modelview Matrix
		glLoadIdentity();
		
		prepareDraw();
		setCamera();
		//draw();
		
		// Select The Projection Matrix
		glMatrixMode(GL_PROJECTION);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	// Switch To Render Mode, Find Out How Many Objects Were Drawn Where The Mouse Was
	hits=glRenderMode(GL_RENDER);
	
	if (hits > 0)
	{
		// Make Our Selection The First Object
		int	choose = buffer[3];
		// Store How Far Away It Is
		int depth = buffer[1];
		
		// Loop Through All The Detected Hits
		for (int loop = 1; loop < hits; loop++)
		{
			// If This Object Is Closer To Us Than The One We Have Selected
			if (buffer[loop*4+1] < GLuint(depth))
			{
				// Select The Closer Object
				choose = buffer[loop*4+3];
				// Store How Far Away It Is
				depth = buffer[loop*4+1];
			}
		}
#if defined(__ATHOS_DEBUG__)
		wxString msg;
		msg << _("Objekt ") << choose << _(" Hit");
		wxLogMessage(msg);
#endif
		return choose;
	}
// TODO THORSTEN?!
	return 0;
}

/**
 * fetches the Middle-Mouse-Pressed event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnMMouseDown(wxMouseEvent& event)
{
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnMMouseDown x=") << event.m_x << _(" y=") << event.m_y;
	wxLogMessage(msg);
#endif
	selection(event.m_x, event.m_y);
	//GNRMouse::getControl(event);
}

/**
 * fetches the Middle-Mouse-Up event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnMMouseUp(wxMouseEvent& event)
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	//GNRMouse::dropControl(event);
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnMMouseUp x=") << event.m_x << _(" y=") << event.m_y;
	wxLogMessage(msg);
#endif
}

/**
 * fetches the Left-Mouse-Pressed event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnLMouseDown(wxMouseEvent& event)
{
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	//selection(event.m_x, event.m_y); BUGGY ON LINUX!!!
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	//wxFontSelectorCtrlEvent myevent(wxEVT_COMMAND_FONT_SELECTION_CHANGED, 2457);
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnLMouseDown x=") << event.m_x << _(" y=") << event.m_y;
	wxLogMessage(msg);
#endif
}

/**
 * fetches the Left-Mouse-Up event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnLMouseUp(wxMouseEvent& event)
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	//GNRMouse::dropControl(event);
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnLMouseUp x=") << event.m_x << _(" y=") << event.m_y;
	wxLogMessage(msg);
#endif
}

/**
 * fetches the right-Mouse-Pressed event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnRMouseDown(wxMouseEvent& event)
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	//selection(event.m_x, event.m_y); BUGGY ON LINUX!!!
	//GNRMouse::getControl(event);
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnRMouseDown x=") << event.m_x << _(" y=") << event.m_y;
	wxLogMessage(msg);
#endif
}

/**
 * fetches the right-Mouse-Up event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnRMouseUp(wxMouseEvent& event)
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	//GNRMouse::dropControl(event);
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnRMouseUp x=") << event.m_x << _(" y=") << event.m_y;
	wxLogMessage(msg);
#endif
}

/**
 * fetches the Mouse-Move event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnMouseMove(wxMouseEvent& event)
{
	//GNRMouse::ObjectTransform(event);
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnMouseMove x=") << event.m_x << _(" y=") << event.m_y;
	wxLogMessage(msg);
#endif
}

/**
 * fetches the Leave-Window event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnLeaveWindow(wxMouseEvent& event)
{
	Disconnect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction) &GNRGLCanvas::OnMouseWheel);
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	//UnFocus???
	
	//GNRMouse::dropControl(event);
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnLeaveWindow x=") << event.m_x << _(" y=") << event.m_y;
	wxLogMessage(msg);
#endif
}

/**
 * fetches the Enter-Window event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnEnterWindow(wxMouseEvent& event)
{
	SetFocus();
	Connect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction) &GNRGLCanvas::OnMouseWheel);
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	
	//GNRMouse::dropControl(event);
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnEnterWindow x=") << event.m_x << _(" y=") << event.m_y;
	wxLogMessage(msg);
#endif
}

/**
 * fetches the double click event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnLMouseDblClick(wxMouseEvent& event)
{
	//GNRMouse::dropControl(event);
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnLMouseDblClick x=") << event.m_x << _(" y=") << event.m_y;
	wxLogMessage(msg);
#endif
}

/**
 * destructor of GNRGLCanvas
 * @access      public
 */
GNRGLCanvas::~GNRGLCanvas() {}
