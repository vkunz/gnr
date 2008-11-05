/**
 * the glcanvas class implements the initialization, event-functions,
 * selection and drawing methods that have 2D and 3D in common
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

#include <wx/image.h>

#include "GNRGLCanvas.h"
#include "GNRNotifyEvent.h"
#include "GNRGLNotifyEvent.h"
#include "GNRMaterialLibrary.h"
#include "GNRGlobalDefine.h"

#include "resources/grid_24bit_rgb.xpm"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

BEGIN_EVENT_TABLE(GNRGLCanvas, wxGLCanvas)
	EVT_KEY_DOWN(GNRGLCanvas::OnKeyDown)
END_EVENT_TABLE()

extern GNRMaterialLibrary mtllib;

//static display list for floor
GLuint GNRGLCanvas::m_floor_DL;

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
	Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseDown);
	Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseUp);
	Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&GNRGLCanvas::OnLeaveWindow);
	Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&GNRGLCanvas::OnEnterWindow);
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&GNRGLCanvas::OnResize);
	Connect(wxEVT_PAINT,(wxObjectEventFunction)&GNRGLCanvas::OnPaint);
	Connect(wxEVT_LEFT_DCLICK, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseDblClick);
}

/**
 * Reconnecting the events needed for the Canvas
 * @access      private
 */
void GNRGLCanvas::reconnectEvents()
{
	// Connect-methods to connect different Events with functions
	Connect(wxEVT_MIDDLE_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnMMouseDown);
	Connect(wxEVT_MIDDLE_UP, (wxObjectEventFunction)&GNRGLCanvas::OnMMouseUp);
	Connect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnRMouseDown);
	Connect(wxEVT_RIGHT_UP, (wxObjectEventFunction)&GNRGLCanvas::OnRMouseUp);
	Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseDown);
	Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseUp);
	Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&GNRGLCanvas::OnLeaveWindow);
	Connect(wxEVT_LEFT_DCLICK, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseDblClick);
	Disconnect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&GNRGLCanvas::OnEnterWindow);
}

/**
 * Disconnecting the events needed for the Canvas
 * @access      private
 */
void GNRGLCanvas::disconnectEvents()
{
	// Connect-methods to connect different Events with functions
	Disconnect(wxEVT_MIDDLE_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnMMouseDown);
	Disconnect(wxEVT_MIDDLE_UP, (wxObjectEventFunction)&GNRGLCanvas::OnMMouseUp);
	Disconnect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnRMouseDown);
	Disconnect(wxEVT_RIGHT_UP, (wxObjectEventFunction)&GNRGLCanvas::OnRMouseUp);
	Disconnect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseDown);
	Disconnect(wxEVT_LEFT_UP, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseUp);
	Disconnect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&GNRGLCanvas::OnLeaveWindow);
	Disconnect(wxEVT_LEFT_DCLICK, (wxObjectEventFunction)&GNRGLCanvas::OnLMouseDblClick);
	Connect(wxEVT_ENTER_WINDOW, (wxObjectEventFunction)&GNRGLCanvas::OnEnterWindow);
}

void GNRGLCanvas::setMatrix()
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

void GNRGLCanvas::initLights()
{
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position[0]);
	
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
//  glLightfv(GL_LIGHT1, GL_AMBIENT, light_diffuse);
//	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
//	glLightfv(GL_LIGHT1, GL_POSITION, light_position[1]);
//
//	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
//  glLightfv(GL_LIGHT2, GL_AMBIENT, light_diffuse);
//	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
//	glLightfv(GL_LIGHT2, GL_POSITION, light_position[2]);
//
//	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
//  glLightfv(GL_LIGHT3, GL_AMBIENT, light_diffuse);
//	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
//	glLightfv(GL_LIGHT3, GL_POSITION, light_position[3]);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
//	glEnable(GL_LIGHT2);
//	glEnable(GL_LIGHT3);

	glClearColor(0.2, 0.2, 0.2, 1.0);
}

/**
 * does the initialization for the 3D canvas
 * @access      protected
 */
void GNRGLCanvas::initGL()
{
	//define light source
	light_ambient[0] = 0.3;
	light_ambient[1] = 0.3;
	light_ambient[2] = 0.3;
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
	light_position[0][0] = 30.0;
	light_position[0][1] = 60.0;
	light_position[0][2] = 20.0;
	light_position[0][3] = 1.0;
	
	//define light position 2
	light_position[1][0] = -64.0;
	light_position[1][1] = 64.0;
	light_position[1][2] = 64.0;
	light_position[1][3] = 1.0;
	
	//define light position 3
	light_position[2][0] = -64.0;
	light_position[2][1] = 64.0;
	light_position[2][2] = -64.0;
	light_position[2][3] = 1.0;
	
	//define light position 4
	light_position[3][0] = 64.0;
	light_position[3][1] = 64.0;
	light_position[3][2] = -64.0;
	light_position[3][3] = 1.0;
	
	//define shadow color
	shadow_color[0] = 0.3;
	shadow_color[1] = 0.3;
	shadow_color[2] = 0.3;
	shadow_color[3] = 0.7;
	
	//normal of floor
	floor_plane[0] = 0.0;
	floor_plane[1] = 1.0;
	floor_plane[2] = 0.0;
	floor_plane[3] = 0.0;
	
	//calculate shadow matrix on init
	SetShadowMatrix(floor_shadow,floor_plane,light_position[0]);
	
	//set active canvas
	SetCurrent();
	
	glShadeModel(GL_SMOOTH);
	
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	
	glDepthFunc(GL_LEQUAL);
	
	glBlendFunc(GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
	
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_CULL_FACE);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glEnable(GL_POINT_SMOOTH);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	loadFloorTexture();
	
	glLineWidth(10.0f);
	glClearDepth(1.0f);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glEnable(GL_NORMALIZE);
}

void GNRGLCanvas::drawBaseFloor(float fCenterX, float fCenterY, float fCenterZ, int fSize)
{
	//is valid display list, call list
	if (glIsList(m_floor_DL))
	{
		glCallList(m_floor_DL);
		return;
	}
	
	float FloorColor[4] = { 0.8f, 0.8f, 0.8f, 0.2f };
	
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
		float x = fCenterX - s, z = fCenterZ - s;
		int start = -(int)s;
		int end   = (int)s;
		//draw fSize quads in x-axis
		for (GLint i = start; i < end; i++)
		{
			//draw fSize quads in z-axis
			for (GLint j = start; j < end; j++)
			{
				glTexCoord2f(0.0,0.0);
				glVertex3f(j,fCenterY,i);
				glTexCoord2f(0.0,1.0);
				glVertex3f(j,fCenterY,i+1.0f);
				glTexCoord2f(1.0,1.0);
				glVertex3f(j+1.0f,fCenterY,i+1.0f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(j+1.0f,fCenterY,i);
			}
		}
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
	}
	glEndList();
	//finish display list...
}

void GNRGLCanvas::loadFloorTexture()
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

void GNRGLCanvas::SetShadowMatrix(float shadowMat[4][4], float groundplane[4], float lightpos[4])
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

void GNRGLCanvas::loadShadowMatrix()
{
	glMultMatrixf((float *) floor_shadow);
}

void GNRGLCanvas::shadowColorOn()
{
	glColor4f(shadow_color[0],shadow_color[1],shadow_color[2],shadow_color[3]);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glCullFace(GL_FRONT);
}

void GNRGLCanvas::shadowColorOff()
{
	glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glCullFace(GL_BACK);
}

void GNRGLCanvas::endPixelBuffer()
{
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}

/**
 * Clears the screen and does all the work that has to be done before drawing
 * @access      private
 */
void GNRGLCanvas::prepareDraw()
{
	SetCurrent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
}

void GNRGLCanvas::endDraw()
{
	SwapBuffers();
}

void GNRGLCanvas::preparePixelBuffer()
{
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
}

/**
 * Checks which GL-Object has been selected by the mouse in the GL-Scene
 * @param       GNRAssembly*    RootAssembly
 * @param       int             Mouse-X-Coordinate
 * @param       int             Mouse-Y-Coordinate
 * @return      int             GL-Object-ID
 * @access      public
 */
GNRAssembly* GNRGLCanvas::selection(GNRAssembly* rootAssembly, GNRGLCamera* camera, int mouse_x, int mouse_y)
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
			GNRAssembly* a = (GNRAssembly*)choose;
			return a->getMaster();
		}
	}
	return NULL;
}

/**
 * fetches the Left-Mouse-Pressed event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnLMouseDown(wxMouseEvent& event)
{
	SetFocus();
	Connect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction)&GNRGLCanvas::OnMouseWheel);
	
	GNRVertex* glcoords = new GNRVertex[2];
	getGLDim(event.GetX(), event.GetY(), glcoords);
	
	// send Event to handle Mouse
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	myevent.SetInt((int)this);
	myevent.setWindowSize(m_window_x, m_window_y);
	myevent.setWorldSize(glcoords);
	GetEventHandler()->ProcessEvent(myevent);
	
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	delete[] glcoords;
}

/**
 * fetches the Double-Click event for selection of objects
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnLMouseDblClick(wxMouseEvent& event)
{
	SetFocus();
	Connect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction)&GNRGLCanvas::OnMouseWheel);
	
	GNRVertex* glcoords = new GNRVertex[2];
	getGLDim(event.GetX(), event.GetY(), glcoords);
	
	// send Event to handle Mouse
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	myevent.SetInt((int)this);
	myevent.setWindowSize(m_window_x, m_window_y);
	myevent.setWorldSize(glcoords);
	GetEventHandler()->ProcessEvent(myevent);
	
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	delete[] glcoords;
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
	SetFocus();
	Connect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction)&GNRGLCanvas::OnMouseWheel);
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
	SetFocus();
	Connect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction)&GNRGLCanvas::OnMouseWheel);
	// nothing has do be done yet
	OnMMouseDown(event);
}

/**
 * fetches the right-Mouse-Up event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnRMouseUp(wxMouseEvent& event)
{
	//Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvas::OnMouseMove);
	// nothing has do be done yet
	OnMMouseUp(event);
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
 * fetches the MouseWheel event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnMouseWheel(wxMouseEvent& event)
{
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
	disconnectEvents();
	
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
	reconnectEvents();
	
	// send Event to handle Mouse
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * fetches ResizeEvent; event for redrawing
 * @param       wxSizeEvent    Size-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnResize(wxSizeEvent& WXUNUSED(event))
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
	myevent.setGNREventType(GLREFRESH);
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
	event.Skip();
}
/*
// Convert Mouse-Coordinates to GL-Coordinates
void GNRGLCanvas::getGLPos(int x, int y, GNRVertex* glcoords) {
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
	gluUnProject(x, viewport[3]-y, z, modelview, projection, viewport, &xpos, &ypos, &zpos);

	glPopMatrix();

	// return world coordinates
	glcoords->setX(xpos);
	glcoords->setY(ypos);
	glcoords->setZ(zpos);
}
*/
// Convert Mouse-Coordinates to GL-Coordinates
void GNRGLCanvas::getGLDim(int x, int y, GNRVertex* glcoords)
{
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
 * @access      public
 */
void GNRGLCanvas::setActive()
{
	SetCurrent();
}

/**
 * fetches the KeyDown
 * @param       wxKeyEvent    Key-Event of current canvas
 * @access      private
 */
void GNRGLCanvas::OnKeyDown(wxKeyEvent& WXUNUSED(event))
{
//#if defined(__ATHOS_DEBUG__)
//	wxLogDebug(wxT("Key-Event"));
//#endif
}

/**
 * destructor of GNRGLCanvas
 * @access      public
 */
GNRGLCanvas::~GNRGLCanvas() {}
