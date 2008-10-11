/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * the gl2dcanvas class implements the speciality for the 2D view
 *
 * @name        GNRGLCanvas.cpp
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifdef _WIN32
#include <gl/glu.h>
#endif

#include "GNRGL2DCanvas.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#define ZNEAR 0.1f
#define ZFAR 1000.0f

/**
 * constructor of GNRGL2DCanvas
 * @param       wxWindow*       Parent-Window
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name
 * @access      public
 */
GNRGL2DCanvas::GNRGL2DCanvas(const GNRAssembly* RootAssembly, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:GNRGLCanvas(RootAssembly, parent, id, pos, size, style, name)
{
	m_camera_height = 10;
	initGL();
}

/**
 * constructor of GNRGL2DCanvas
 * @param       wxWindow*       Parent-Window
 * @param       wxGLContext*    Used GLContext for common Context
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name
 * @access      public
 */
GNRGL2DCanvas::GNRGL2DCanvas(const GNRAssembly* RootAssembly, wxWindow* parent, wxGLContext* sharedContext, wxWindowID id, const wxPoint& pos, const wxSize& size,
                             long style, const wxString& name) : GNRGLCanvas(RootAssembly, parent, sharedContext, id, pos, size, style, name)
{
	m_camera_height = 10;
	initGL();
}

/**
 * does the initialization for the 2D canvas
 * @access      private
 */
void GNRGL2DCanvas::initGL()
{
	// set current GL-Frame
	SetCurrent();
	
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	//glEnable(GL_TEXTURE_2D);   // textures
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * Reshape current frame on resize
 * @access      private
 */
void GNRGL2DCanvas::reshape()
{
	// set current GL-Frame
	SetCurrent();
	
	//get canvas-size
	GetClientSize(&m_window_x, &m_window_y);
	
	glViewport(0, 0, m_window_x, m_window_y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspective();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * does the adjustment of the canvas for the 2D canvas
 * @param       wxSizeEvent*        Size-Event of the current canvas
 * @access      private
 */
void GNRGL2DCanvas::OnResize(wxSizeEvent& event)
{
	reshape();
}

/**
 * sets the camera-position for the 2D scene
 * @access      private
 */
void GNRGL2DCanvas::setCamera()
{
	// set camera-position
	gluLookAt(0,m_camera_height,0,0,1,0,0,0,1);
}

/**
 * sets the perspective for the 2D scene
 * @access      private
 */
void GNRGL2DCanvas::setPerspective()
{
	gluPerspective(45.0f, (float)m_window_x / (float)m_window_y, ZNEAR, ZFAR);
	//glOrtho(m_window_x*(-1.0f/m_camera_height), m_window_x*(1.0f/m_camera_height), m_window_y*(1.0f/m_camera_height), m_window_y*(-1.0f/m_camera_height), ZNEAR, ZFAR);
}

void GNRGL2DCanvas::OnMouseWheel(wxMouseEvent& event)
{
	m_camera_height += (float)event.GetWheelRotation()/720.0;
	setPerspective();
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnMouseWheel, rotation: ") << m_camera_height;
	wxLogMessage(msg);
#endif
}
