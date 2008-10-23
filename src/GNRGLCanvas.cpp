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
#include "GNRNotifyEvent.h"
#include "GNRGLNotifyEvent.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#define ZNEAR 0.1f
#define ZFAR 1000.0f

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
	Connect(wxEVT_PAINT,(wxObjectEventFunction)&GNRGLCanvas::OnPaint);
}

void GNRGLCanvas::setMatrix()
{
	GetClientSize(&m_window_x, &m_window_y);
	float aspect = (float)m_window_x/(float)m_window_y;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, ZNEAR, ZFAR);
	glViewport(0, 0, m_window_x, m_window_y);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
	    0.0, 0.0, 2.0,
	    0.0, 0.0, 0.0,
	    0.0, 1.0, 0.0
	);
}

void GNRGLCanvas::initLights()
{
	glEnable(GL_LIGHTING);
	
	glEnable(GL_LIGHT0);
	
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_specular[] = { 0.2, 0.2, 0.0, 1.0 };
	GLfloat light_position[] = { 2.0, 2.0, 2.0, 1.0 };
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
//	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
//	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
//	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);
}

/**
 * does the initialization for the 3D canvas
 * @access      protected
 */
void GNRGLCanvas::initGL()
{
	SetCurrent();
	glClearColor(0.4, 0.4, 0.4, 0.0);
	
	setMatrix();
	initLights();
	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glEnable(GL_COLOR_MATERIAL);
	
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glEnable(GL_NORMALIZE);
}

/**
 * flush the buffer to screen
 * @access      public
 */
void GNRGLCanvas::endDraw()
{
	setMatrix();
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
	
	glMatrixMode(GL_MODELVIEW);
	
	// Reset The Current Modelview Matrix
	glLoadIdentity();
	
	setCamera();
	
	/*glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	    glVertex3f(-40.0f, 0.0f, -40.0f);
	    glVertex3f(-40.0f, 0.0f, -2.0f);
	    glVertex3f(40.0f, 0.0f, -2.0f);
	    glVertex3f(40.0f, 0.0f, -40.0f);
	glEnd();*/
	
}

/**
 * Checks which GL-Object has been selected by the mouse in the GL-Scene
 * @param       GNRAssembly*    RootAssembly
 * @param       int             Mouse-X-Coordinate
 * @param       int             Mouse-Y-Coordinate
 * @return      int             GL-Object-ID
 * @access      public
 */
int GNRGLCanvas::selection(GNRAssembly* rootAssembly, GNRGLCamera* camera, int mouse_x, int mouse_y)
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
		gluPickMatrix((GLdouble) mouse_x, (GLdouble)(viewport[3]-mouse_y), 1.0f, 1.0f, viewport);
		
		// Apply The Perspective Matrix
		setPerspective();
		glMatrixMode(GL_MODELVIEW);
		
		// Reset The Modelview Matrix
		glLoadIdentity();
		
		//prepareDraw();
		setCamera();
		if (camera != NULL)
		{
			camera->Render();
		}
		rootAssembly->draw();
		
		// Select The Projection Matrix
		glMatrixMode(GL_PROJECTION);
	}
	glPopMatrix();
	glPopName();
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
		return choose;
	}
	return 0;
}

/**
 * fetches the Left-Mouse-Pressed event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnLMouseDown(wxMouseEvent& event)
{

	GNRVertex* glcoords = getGLDim(event.GetX(), event.GetY());
	
	// send Event to handle Mouse
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	myevent.setWindowSize(m_window_x, m_window_y);
	myevent.setWorldSize(glcoords[1].getX() - glcoords[0].getX(), glcoords[1].getY() - glcoords[0].getY());
	GetEventHandler()->ProcessEvent(myevent);
	
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
}

/**
 * fetches the Left-Mouse-Up event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnLMouseUp(wxMouseEvent& event)
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	
	// send Event to handle Mouse
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}


/**
 * fetches the Middle-Mouse-Pressed event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnMMouseDown(wxMouseEvent& event)
{
	// send Event to handle Mouse
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	myevent.setWindowSize(m_window_x, m_window_y);
	GetEventHandler()->ProcessEvent(myevent);
	
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
}

/**
 * fetches the Middle-Mouse-Up event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnMMouseUp(wxMouseEvent& event)
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	
	// send Event to handle Mouse
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * fetches the right-Mouse-Pressed event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnRMouseDown(wxMouseEvent& event)
{
	// nothing has do be done yet
	
}

/**
 * fetches the right-Mouse-Up event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnRMouseUp(wxMouseEvent& event)
{
	// nothing has do be done yet
}

/**
 * fetches the Mouse-Move event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnMouseMove(wxMouseEvent& event)
{
	// send Event to handle Mouse
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
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
	
	// send Event to handle Mouse
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
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
	
	// send Event to handle Mouse
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
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
 * fetches ResizeEvent; event for redrawing
 * @param       wxSizeEvent    Size-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnResize(wxSizeEvent& event)
{
	//get canvas-size
	GetClientSize(&m_window_x, &m_window_y);
	
	// Adjust Viewport, ...
	reshape();
}

/**
 * Reshape current frame on resize; adjust Viewport
 * @access      private
 */
void GNRGLCanvas::reshape()
{
	// set current GL-Frame
	SetCurrent();
	
	// set viewport with resolution
	glViewport(0, 0, (GLint) m_window_x, (GLint) m_window_y);
	
	// Load and Reset Modelview
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspective();
	
	// Load and Reset Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * Canvas needs to be redrawn; Send Event to Redraw Canvases
 * @access      private
 */
void GNRGLCanvas::OnPaint(wxPaintEvent& event)
{
	// Event for Redrawing the Canvases
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(GLRefresh);
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
	event.Skip();
}

// Convert Mouse-Coordinates to GL-Coordinates
GNRVertex GNRGLCanvas::getGLPos(int x, int y)
{
	glPushMatrix();
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
	gluUnProject(x, viewport[3]-y, z, modelview, projection, viewport, &xpos, &ypos, &zpos);
	
	glPopMatrix();
	
	// return world coordinates
	GNRVertex glcoords(xpos, ypos, zpos);
	return glcoords;
}

// Convert Mouse-Coordinates to GL-Coordinates
GNRVertex* GNRGLCanvas::getGLDim(int x, int y)
{
	glPushMatrix();
	GLdouble modelview[16], projection[16];
	GLint viewport[4];
	float z;
	double xpos, ypos, zpos;
	GNRVertex* glcoords = new GNRVertex[2];
	
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);       //get the modelview matrix
	glGetDoublev(GL_PROJECTION_MATRIX, projection);     //get the projection matrix
	glGetIntegerv(GL_VIEWPORT, viewport);               //get the viewport
	
	//Read the window z co-ordinate (the z value on that point in unit cube)
	glReadPixels((int)x, (int)(viewport[3]-y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	
	//Unproject the window co-ordinates to find the world co-ordinates.
	gluUnProject(0, 0, z, modelview, projection, viewport, &xpos, &ypos, &zpos);
	
	glcoords[0].setX(xpos);
	glcoords[0].setY(ypos);
	glcoords[0].setZ(zpos);
	
	//Unproject the window co-ordinates to find the world co-ordinates.
	gluUnProject(m_window_x, m_window_y, z, modelview, projection, viewport, &xpos, &ypos, &zpos);
	
	glcoords[1].setX(xpos);
	glcoords[1].setY(ypos);
	glcoords[1].setZ(zpos);
	
	glPopMatrix();
	
	// return world coordinates
	return glcoords;
}

/**
 * destructor of GNRGLCanvas
 * @access      public
 */
GNRGLCanvas::~GNRGLCanvas() {}
