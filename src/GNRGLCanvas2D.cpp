/**
 * the gl2dcanvas class implements the speciality for the 2D view
 *
 * @name        GNRGLCanvas2D.cpp
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifdef _WIN32
#include <gl/glu.h>
#endif

#include "GNRGLCanvas2D.h"
#include "GNRGlobalDefine.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GNRGLCanvas2D
 * @param       wxWindow*       Parent-Window
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name

 */
GNRGLCanvas2D::GNRGLCanvas2D(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:GNRGLCanvas(parent, id, pos, size, style, name)
{
}

/**
 * constructor of GNRGLCanvas2D
 * @param       wxWindow*       Parent-Window
 * @param       wxGLContext*    Used GLContext for common Context
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name

 */
GNRGLCanvas2D::GNRGLCanvas2D(wxWindow* parent, wxGLContext* sharedContext, wxWindowID id, const wxPoint& pos, const wxSize& size,
                             long style, const wxString& name) : GNRGLCanvas(parent, sharedContext, id, pos, size, style, name)
{
}

/**
 * sets the perspective for the 2D scene
 * @access private
 */
void GNRGLCanvas2D::setPerspective()
{
	gluPerspective(GLU_PERSPECTIVE, (float)m_window_x / (float)m_window_y, ZNEAR, ZFAR);
	//glOrtho(m_window_x*(-1.0f/m_camera_height), m_window_x*(1.0f/m_camera_height), m_window_y*(1.0f/m_camera_height), m_window_y*(-1.0f/m_camera_height), ZNEAR, ZFAR);
}

/**
 * Returns the Canvas-ID
 * @return  int     Canvas-ID
 * @access private
 */
canvasType GNRGLCanvas2D::getCanvasID()
{
	return CANVAS2D;
}
