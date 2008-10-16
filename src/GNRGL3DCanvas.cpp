#ifdef _WIN32
#include <gl/glu.h>
#endif

#include "GNRGL3DCanvas.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

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
GNRGL3DCanvas::GNRGL3DCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:GNRGLCanvas(parent, id, pos, size, style, name)
{
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
GNRGL3DCanvas::GNRGL3DCanvas(wxWindow* parent, wxGLContext* sharedContext, wxWindowID id, const wxPoint& pos, const wxSize& size,
                             long style, const wxString& name) : GNRGLCanvas(parent, sharedContext, id, pos, size, style, name)
{
}

/**
 * sets the camera-position for the 3D scene
 * @access      private
 */
void GNRGL3DCanvas::setCamera()
{
	// nothing do to
}

/** * sets the perspective for the 3D scene
 * @access private
 */
void GNRGL3DCanvas::setPerspective()
{
	gluPerspective(45.0f, (float)m_window_x / (float)m_window_y, ZNEAR, ZFAR);
}

void GNRGL3DCanvas::OnMouseWheel(wxMouseEvent& event)
{
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << _("OnMouseWheel, rotation: ") << event.GetWheelRotation();
	wxLogMessage(msg);
#endif
}
