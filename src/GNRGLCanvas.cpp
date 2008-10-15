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
 * Clears the screen and does all the work that has to be done before drawing
 * @access      private
 */
void GNRGLCanvas::prepareDraw()
{
	// set current GL-Context as activ
	SetCurrent();
	
	// Clear the Window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	
	// Reset The Current Modelview Matrix
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
