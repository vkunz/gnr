/**
 * the gl2dcanvas class implements the speciality for the 2D view
 * @note        [DONE]
 * @name        GLCanvas3D.cpp
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <GL/glu.h>

#include "GLCanvas3D.h"
#include "GlobalDefine.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GLCanvas3D
 * @param[in]       parent       Parent-Window
 * @param[in]       id           Window-ID
 * @param[in]       pos          Window-Position of the Canvas
 * @param[in]       size         Window-Size of the Canvas
 * @param[in]       style        Window-Style
 * @param[in]       name         Window-Name
 */
GLCanvas3D::GLCanvas3D(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:GLCanvas(parent, id, pos, size, style, name)
{
}

/**
 * constructor of GLCanvas3D
 * @param[in]       parent          Parent-Window
 * @param[in]       sharedContext   shared with context pointer
 * @param[in]       id              Window-ID
 * @param[in]       pos             Window-Position of the Canvas
 * @param[in]       size            Window-Size of the Canvas
 * @param[in]       style           Window-Style
 * @param[in]       name            Window-Name
 */
GLCanvas3D::GLCanvas3D(wxWindow* parent, wxGLContext* sharedContext, wxWindowID id, const wxPoint& pos, const wxSize& size,
                       long style, const wxString& name) : GLCanvas(parent, sharedContext, id, pos, size, style, name)
{
}

/**
 * sets the perspective for the 3D scene
 */
void GLCanvas3D::setPerspective()
{
	gluPerspective(GLU_PERSPECTIVE, (float)m_window_x / (float)m_window_y, ZNEAR, ZFAR);
}

/**
 * Returns the Canvas-ID
 * @return  canvasType     Canvas-ID
 */
canvasType GLCanvas3D::getCanvasID()
{
	return CANVAS3D;
}
