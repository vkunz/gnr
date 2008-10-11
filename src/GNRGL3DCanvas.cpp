#ifdef _WIN32
#include <gl/glu.h>
#endif

#include "GNRGL3DCanvas.h"

#define ZNEAR 0.1f
#define ZFAR 1000.0f

/**
 * constructor of GNRGL3DCanvas
 * @param       wxWindow*       Parent-Window
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name
 * @access      public
 */
GNRGL3DCanvas::GNRGL3DCanvas(const GNRAssembly* RootAssembly, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:GNRGLCanvas(RootAssembly, parent, id, pos, size, style, name)
{
	initGL();
}

/**
 * constructor of GNRGL3DCanvas
 * @param       wxWindow*       Parent-Window
 * @param       wxGLContext*    Used GLContext for common Context
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name
 * @access      public
 */
GNRGL3DCanvas::GNRGL3DCanvas(const GNRAssembly* RootAssembly, wxWindow* parent, wxGLContext* sharedContext, wxWindowID id, const wxPoint& pos, const wxSize& size,
                             long style, const wxString& name) : GNRGLCanvas(RootAssembly, parent, sharedContext, id, pos, size, style, name)
{
	initGL();
}

/**
 * does the initialization for the 3D canvas
 * @access      private
 */
void GNRGL3DCanvas::initGL()
{
	// set current GL-Frame
	SetCurrent();
	
	glClearColor(0.5, 0.5, 0.5, 0.0);
	
	// alizing 3D models
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
	
//  SetCurrent();
//
//  glDepthFunc( GL_LEQUAL );
//  glShadeModel( GL_SMOOTH );
//
//  GLfloat gray[] = { 0.35f, 0.35f, 0.35f, 1.0f };
//  GLfloat light_pos[] = { 50.0f, 50.0f, 50.0f, 1.0f };
//  glEnable( GL_NORMALIZE );
//  glLightfv( GL_LIGHT0, GL_AMBIENT, gray );
//  glLightfv( GL_LIGHT0, GL_DIFFUSE, gray );
//  glLightfv( GL_LIGHT0, GL_POSITION, light_pos );
//
//  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//
//  glEnable( GL_LIGHTING );
//  glEnable( GL_LIGHT0 );
//  glEnable( GL_DEPTH_TEST );
//  glEnable( GL_BLEND );
//
//  glClearColor( 0.4, 0.4, 0.4, 1.0 );
//  glClearDepth( 1.0 );
//  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//  SwapBuffers();
}

/**
 * Reshape current frame on resize
 * @access      private
 */
void GNRGL3DCanvas::reshape()
{
	// set current GL-Frame
	SetCurrent();
	
	//get canvas-size
	GetClientSize(&m_window_x, &m_window_y);
	
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
 * does the adjustment of the canvas for the 3D canvas
 * @param       wxSizeEvent*        Size-Event of the current canvas
 * @access      private
 */
void GNRGL3DCanvas::OnResize(wxSizeEvent& event)
{
	reshape();
}

/**
 * sets the camera-position for the 3D scene
 * @access      private
 */
void GNRGL3DCanvas::setCamera()
{
	// nothing do to
}

/**
 * sets the perspective for the 3D scene
 * @access      private
 */
void GNRGL3DCanvas::setPerspective()
{
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (float)m_window_x / (float)m_window_y, ZNEAR, ZFAR);
}
