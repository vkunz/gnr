#ifdef _WIN32
#include <gl/glu.h>
#endif

#include "GNRGLCanvas3D.h"
#include "GNRGLNotifyEvent.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#define ZNEAR 0.1f
#define ZFAR 100.0f

/**
 * constructor of GNRGLCanvas3D
 * @param       wxWindow*       Parent-Window
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name
 * @access      public
 */
GNRGLCanvas3D::GNRGLCanvas3D(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:GNRGLCanvas(parent, id, pos, size, style, name)
{
}

/**
 * constructor of GNRGLCanvas3D
 * @param       wxWindow*       Parent-Window
 * @param       wxGLContext*    Used GLContext for common Context
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name
 * @access      public
 */
GNRGLCanvas3D::GNRGLCanvas3D(wxWindow* parent, wxGLContext* sharedContext, wxWindowID id, const wxPoint& pos, const wxSize& size,
                             long style, const wxString& name) : GNRGLCanvas(parent, sharedContext, id, pos, size, style, name)
{
}

/** * sets the perspective for the 3D scene
 * @access private
 */
void GNRGLCanvas3D::setPerspective()
{
	gluPerspective(45.0f, (float)m_window_x / (float)m_window_y, ZNEAR, ZFAR);
}

/**
 * Returns the Canvas-ID
 * @return  int     Canvas-ID
 * @access private
 */
canvasType GNRGLCanvas3D::getCanvasID()
{
	return CANVAS3D;
}
