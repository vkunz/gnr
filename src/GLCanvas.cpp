/**
 * the glcanvas class implements the initialization, event-functions,
 * selection and drawing methods that have 2D and 3D in common
 * @note        [TODO]
 * @name        GLCanvas.cpp
 * @date        2008-10-08
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifdef _WIN32
#include <gl/glu.h>
#endif

#include <wx/image.h>

#include "GLCanvas.h"
#include "NotifyEvent.h"
#include "GLNotifyEvent.h"
#include "GlobalDefine.h"

#include "resources/grid_24bit_rgb.xpm"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

BEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
	
END_EVENT_TABLE()

//static display list for floor
GLuint GLCanvas::m_floor_DL;

/**
 * constructor of GLCanvas
 * @param[in]       parent          Parent-Window
 * @param[in]       id              Window-ID
 * @param[in]       pos             Window-Position of the Canvas
 * @param[in]       size            Window-Size of the Canvas
 * @param[in]       style           Window-Style
 * @param[in]       name            Window-Name
 */
GLCanvas::GLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		: wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name)
{
	initGL();
	connectEvents();
}

/**
 * constructor of GLCanvas
 * @param[in]       parent          Parent-Window
 * @param[in]       sharedContext   Used GLContext for common Context
 * @param[in]       id              Window-ID
 * @param[in]       pos             Window-Position of the Canvas
 * @param[in]       size            Window-Size of the Canvas
 * @param[in]       style           Window-Style
 * @param[in]       name            Window-Name
 */
GLCanvas::GLCanvas(wxWindow* parent, wxGLContext* sharedContext, wxWindowID id, const wxPoint& pos, const wxSize& size,
                   long style, const wxString& name) : wxGLCanvas(parent, sharedContext, id, pos, size, style, name)
{
	initGL();
	connectEvents();
}

/**
 * Connecting the events needed for the Canvas
 */
void GLCanvas::connectEvents()
{
	// Connect-methods to connect different Events with functions
	Connect(wxEVT_MIDDLE_DOWN, (wxObjectEventFunction)&GLCanvas::OnMMouseDown);
	Connect(wxEVT_MIDDLE_UP, (wxObjectEventFunction)&GLCanvas::OnMMouseUp);
	Connect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&GLCanvas::OnRMouseDown);
	Connect(wxEVT_RIGHT_UP, (wxObjectEventFunction)&GLCanvas::OnRMouseUp);
	Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&GLCanvas::OnLMouseDown);
	Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&GLCanvas::OnLMouseUp);
	Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&GLCanvas::OnLeaveWindow);
	Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&GLCanvas::OnEnterWindow);
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&GLCanvas::OnResize);
	Connect(wxEVT_PAINT,(wxObjectEventFunction)&GLCanvas::OnPaint);
	Connect(wxEVT_LEFT_DCLICK, (wxObjectEventFunction)&GLCanvas::OnLMouseDblClick);
}

/**
 * Reconnecting the events needed for the Canvas
 */
void GLCanvas::reconnectEvents()
{
	// Connect-methods to connect different Events with functions
	Connect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction)&GLCanvas::OnMouseWheel);
	Connect(wxEVT_MIDDLE_DOWN, (wxObjectEventFunction)&GLCanvas::OnMMouseDown);
	Connect(wxEVT_MIDDLE_UP, (wxObjectEventFunction)&GLCanvas::OnMMouseUp);
	Connect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&GLCanvas::OnRMouseDown);
	Connect(wxEVT_RIGHT_UP, (wxObjectEventFunction)&GLCanvas::OnRMouseUp);
	Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&GLCanvas::OnLMouseDown);
	Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&GLCanvas::OnLMouseUp);
	Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&GLCanvas::OnLeaveWindow);
	Connect(wxEVT_LEFT_DCLICK, (wxObjectEventFunction)&GLCanvas::OnLMouseDblClick);
	Disconnect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&GLCanvas::OnEnterWindow);
}

/**
 * Disconnecting the events needed for the Canvas
 */
void GLCanvas::disconnectEvents()
{
	// Connect-methods to connect different Events with functions
	Disconnect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction)&GLCanvas::OnMouseWheel);
	Disconnect(wxEVT_MIDDLE_DOWN, (wxObjectEventFunction)&GLCanvas::OnMMouseDown);
	Disconnect(wxEVT_MIDDLE_UP, (wxObjectEventFunction)&GLCanvas::OnMMouseUp);
	Disconnect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&GLCanvas::OnRMouseDown);
	Disconnect(wxEVT_RIGHT_UP, (wxObjectEventFunction)&GLCanvas::OnRMouseUp);
	Disconnect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&GLCanvas::OnLMouseDown);
	Disconnect(wxEVT_LEFT_UP, (wxObjectEventFunction)&GLCanvas::OnLMouseUp);
	Disconnect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&GLCanvas::OnLeaveWindow);
	Disconnect(wxEVT_LEFT_DCLICK, (wxObjectEventFunction)&GLCanvas::OnLMouseDblClick);
	Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&GLCanvas::OnEnterWindow);
}

void GLCanvas::setMatrix()
{
	GetClientSize(&m_window_x, &m_window_y);
	float aspect = (float)m_window_x/(float)m_window_y;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(GLU_PERSPECTIVE, aspect, ZNEAR, ZFAR);
	glViewport(0, 0, m_window_x, m_window_y);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLCanvas::initLights()
{
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,0);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
	
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glClearColor(0.2, 0.2, 0.2, 1.0);
}

/**
 * does the initialization for the 3D canvas
 */
void GLCanvas::initGL()
{
	//define light source
	light_ambient[0] = 0.2;
	light_ambient[1] = 0.2;
	light_ambient[2] = 0.2;
	light_ambient[3] = 0.0;
	
	light_diffuse[0] = 1.0;
	light_diffuse[1] = 1.0;
	light_diffuse[2] = 1.0;
	light_diffuse[3] = 0.0;
	
	light_specular[0] = 0.1;
	light_specular[1] = 0.1;
	light_specular[2] = 0.1;
	light_specular[3] = 0.0;
	
	//define light position 1
	light_position[0] = 30.0;
	light_position[1] = 60.0;
	light_position[2] = 20.0;
	light_position[3] = 1.0;
	
	//define shadow color
	shadow_color[0] = 0.2;
	shadow_color[1] = 0.2;
	shadow_color[2] = 0.2;
	shadow_color[3] = 0.6;
	
	//normal of floor
	floor_plane[0] = 0.0;
	floor_plane[1] = 1.0;
	floor_plane[2] = 0.0;
	floor_plane[3] = 0.0;
	
	//calculate shadow matrix on init
	SetShadowMatrix(floor_shadow,floor_plane,light_position);
	
	//set active canvas
	SetCurrent();
	
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	glCullFace(GL_BACK);
	
	glDepthFunc(GL_LEQUAL);
	
	glBlendFunc(GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	loadFloorTexture();
	
	glLineWidth(10.0f);
	glClearDepth(1.0f);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glEnable(GL_NORMALIZE);
}

void GLCanvas::drawBaseFloor(float fCenterX, float fCenterY, float fCenterZ, int fSize)
{
	//is valid display list, call list
	if (glIsList(m_floor_DL))
	{
		glCallList(m_floor_DL);
		return;
	}
	
	float FloorColor[4] = { 0.9f, 0.9f, 0.9f, 0.0f };
	
	//create new display list for floor
	m_floor_DL = glGenLists(1);
	
	glNewList(m_floor_DL,GL_COMPILE);
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		glMaterialfv(GL_FRONT, GL_SPECULAR, FloorColor);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, FloorColor);
		glMaterialfv(GL_FRONT, GL_EMISSION, FloorColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
		
		glBindTexture(GL_TEXTURE_2D, FloorTexture);
		
		glBegin(GL_QUADS);
		
		//set normal
		glNormal3f(0.0, 1.0, 0.0);
		
		//set starting edge half of size from center
		float s = fSize/2;
		
		//calculate start and end
		int start = -(int)s;
		int end   = (int)s;
		
		//draw fSize quads in x-axis
		for (GLint i = start; i < end; i++)
		{
			//draw fSize quads in z-axis
			for (GLint j = start; j < end; j++)
			{
				glTexCoord2f(0.0,0.0);
				glVertex3f(j+fCenterX,fCenterY,i+fCenterZ);
				glTexCoord2f(0.0,1.0);
				glVertex3f(j+fCenterX,fCenterY,i+fCenterZ+1.0f);
				glTexCoord2f(1.0,1.0);
				glVertex3f(j+fCenterX+1.0f,fCenterY,i+fCenterZ+1.0f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(j+fCenterX+1.0f,fCenterY,i+fCenterZ);
			}
		}
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
	}
	glEndList();
	//finish display list...
}

void GLCanvas::loadFloorTexture()
{
	wxImage image(grid_24bit_rgb_xpm);
	glGenTextures(1, &FloorTexture);
	glBindTexture(GL_TEXTURE_2D, FloorTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());
}

void GLCanvas::SetShadowMatrix(float shadowMat[4][4], float groundplane[4], float lightpos[4])
{
	float dot = groundplane[X]*lightpos[X] + groundplane[Y]*lightpos[Y] + groundplane[Z]*lightpos[Z] + groundplane[W]*lightpos[W];
	shadowMat[X][0] = dot - lightpos[X] * groundplane[X];
	shadowMat[Y][0] = 0.f - lightpos[X] * groundplane[Y];
	shadowMat[Z][0] = 0.f - lightpos[X] * groundplane[Z];
	shadowMat[W][0] = 0.f - lightpos[X] * groundplane[W];
	shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
	shadowMat[Y][1] = dot - lightpos[Y] * groundplane[Y];
	shadowMat[Z][1] = 0.f - lightpos[Y] * groundplane[Z];
	shadowMat[W][1] = 0.f - lightpos[Y] * groundplane[W];
	shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
	shadowMat[Y][2] = 0.f - lightpos[Z] * groundplane[Y];
	shadowMat[Z][2] = dot - lightpos[Z] * groundplane[Z];
	shadowMat[W][2] = 0.f - lightpos[Z] * groundplane[W];
	shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
	shadowMat[Y][3] = 0.f - lightpos[W] * groundplane[Y];
	shadowMat[Z][3] = 0.f - lightpos[W] * groundplane[Z];
	shadowMat[W][3] = dot - lightpos[W] * groundplane[W];
	
}

void GLCanvas::loadShadowMatrix()
{
	glMultMatrixf((float *) floor_shadow);
}

void GLCanvas::shadowColorOn()
{
	glColor4f(shadow_color[0],shadow_color[1],shadow_color[2],shadow_color[3]);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glCullFace(GL_FRONT);
}

void GLCanvas::shadowColorOff()
{
	//glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glCullFace(GL_BACK);
}

void GLCanvas::endPixelBuffer()
{
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}

/**
 * Clears the screen and does all the work that has to be done before drawing
 */
void GLCanvas::prepareDraw()
{
	SetCurrent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
}

/**
 * does the things that have to be done after drawing;
 */
void GLCanvas::endDraw()
{
	glFlush();
	SwapBuffers();
}

void GLCanvas::preparePixelBuffer()
{
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
}

/**
 * Checks which GL-Object has been selected by the mouse in the GL-Scene
 * @param[in]       rootAssembly    Pointer to root-assembly
 * @param[in]       camera          Pointer to adequate camera-object
 * @param[in]       mouse_x         Mouse-X-Coordinate
 * @param[in]       mouse_y         Mouse-Y-Coordinate
 * @return          Assemby*        GL-Object-ID
 */
Assembly* GLCanvas::selection(Assembly* rootAssembly, GLCamera* camera, int mouse_x, int mouse_y)
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
		camera->render();
		
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
		
		//if choose > 0, an object was hit
		if (choose > 0)
		{
			//return pointer to master of assembly
			Assembly* a = (Assembly*)choose;
			return a->getMaster();
		}
	}
	return NULL;
}

/**
 * fetches the Left-Mouse-Pressed event
 * @param[in]       event		       Mouse-Event of current canvas
 */
void GLCanvas::OnLMouseDown(wxMouseEvent& event)
{
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GLCanvas::OnMouseMove);
	
	Vertex* glcoords = new Vertex[2];
	getGLDim(event.GetX(), event.GetY(), glcoords);
	
	// send Event to handle Mouse
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	myevent.SetInt((int)this);
	myevent.setWindowSize(m_window_x, m_window_y);
	myevent.setWorldSize(glcoords);
	GetEventHandler()->ProcessEvent(myevent);
	
	delete[] glcoords;
}

/**
 * fetches the Double-Click event for selection of objects
 * @param[in]       event       Mouse-Event of current canvas
 */
void GLCanvas::OnLMouseDblClick(wxMouseEvent& event)
{
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GLCanvas::OnMouseMove);
	
	Vertex* glcoords = new Vertex[2];
	getGLDim(event.GetX(), event.GetY(), glcoords);
	
	// send Event to handle Mouse
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	myevent.SetInt((int)this);
	myevent.setWindowSize(m_window_x, m_window_y);
	myevent.setWorldSize(glcoords);
	GetEventHandler()->ProcessEvent(myevent);
	
	delete[] glcoords;
}

/**
 * fetches the Left-Mouse-Up event
 * @param[in]       event       Mouse-Event of current canvas
 */
void GLCanvas::OnLMouseUp(wxMouseEvent& event)
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GLCanvas::OnMouseMove);
	
	// send Event to handle Mouse
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}


/**
 * fetches the Middle-Mouse-Pressed event
 * @param[in]       event		Mouse-Event of current canvas
 */
void GLCanvas::OnMMouseDown(wxMouseEvent& event)
{
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GLCanvas::OnMouseMove);
	
	Vertex* glcoords = new Vertex[2];
	getGLDim(event.GetX(), event.GetY(), glcoords);
	
	// send Event to handle Mouse
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	myevent.SetInt((int)this);
	myevent.setWindowSize(m_window_x, m_window_y);
	myevent.setWorldSize(glcoords);
	GetEventHandler()->ProcessEvent(myevent);
	
	delete[] glcoords;
}

/**
 * fetches the Middle-Mouse-Up event
 * @param[in]       event       Mouse-Event of current canvas
 */
void GLCanvas::OnMMouseUp(wxMouseEvent& event)
{
	// send Event to handle Mouse
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * fetches the right-Mouse-Pressed event
 * @param[in]       event       Mouse-Event of current canvas
 */
void GLCanvas::OnRMouseDown(wxMouseEvent& event)
{
	Vertex* glcoords = new Vertex[2];
	getGLDim(event.GetX(), event.GetY(), glcoords);
	
	// send Event to handle Mouse
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	myevent.SetInt((int)this);
	myevent.setWindowSize(m_window_x, m_window_y);
	myevent.setWorldSize(glcoords);
	GetEventHandler()->ProcessEvent(myevent);
	
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GLCanvas::OnMouseMove);
	delete[] glcoords;
}

/**
 * fetches the right-Mouse-Up event
 * @param[in]       WXUNUSED       unused Mouse-Event of current canvas
 */
void GLCanvas::OnRMouseUp(wxMouseEvent& WXUNUSED(event))
{
	//nothing anymore
}

/**
 * fetches the Mouse-Move event
 * @param[in]       event       Mouse-Event of current canvas
 */
void GLCanvas::OnMouseMove(wxMouseEvent& event)
{
	// send Event to handle Mouse
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * fetches the MouseWheel event
 * @param[in]       event       Mouse-Event of current canvas
 */
void GLCanvas::OnMouseWheel(wxMouseEvent& event)
{
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * fetches the Leave-Window event
 * @param[in]       event       Mouse-Event of current canvas
 */
void GLCanvas::OnLeaveWindow(wxMouseEvent& event)
{
	disconnectEvents();
	
	// send Event to handle Mouse
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * fetches the Enter-Window event
 * @param[in]       event       Mouse-Event of current canvas
 */
void GLCanvas::OnEnterWindow(wxMouseEvent& event)
{
	SetCurrent();
	reconnectEvents();
	
	// send Event to handle Mouse
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * fetches ResizeEvent; event for redrawing
 * @param[in]       WXUNUSED     unused Size-Event of current canvas
 */
void GLCanvas::OnResize(wxSizeEvent& WXUNUSED(event))
{
	//get canvas-size
	GetClientSize(&m_window_x, &m_window_y);
	
	// Adjust Viewport, ...
	reshape();
}

/**
 * Reshape current frame on resize; adjust Viewport
 */
void GLCanvas::reshape()
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
 * @param[in]       event       paint event from canvas
 */
void GLCanvas::OnPaint(wxPaintEvent& event)
{
	// Event for Redrawing the Canvases
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(GLREFRESH);
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
	event.Skip();
}

/**
 * reads out canvas dimensions
 * @param[in]       x           mouse-x-position
 * @param[in]       y           mouse-y-position
 * @param[out]      glcoords    array of vertex to store dimensions in
 */
void GLCanvas::getGLDim(int x, int y, Vertex* glcoords)
{
	SetFocus();
	SetCurrent();
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
}

/**
 * Set the Canvas as active
 */
void GLCanvas::setActive()
{
	SetCurrent();
}

/**
 * destructor of GLCanvas
 */
GLCanvas::~GLCanvas() {}
