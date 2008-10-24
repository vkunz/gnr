#ifdef _WIN32
#include <gl/glu.h>
#endif

#include "GNRGL3DCanvas.h"
#include "GNRGLNotifyEvent.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#define ZNEAR 0.1f
#define ZFAR 100.0f

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
	// set camera-position
	//gluLookAt(0, 3, 3, 0, 0, 0, 0, 1, 0);
}

/** * sets the perspective for the 3D scene
 * @access private
 */
void GNRGL3DCanvas::setPerspective()
{
	gluPerspective(45.0f, (float)m_window_x / (float)m_window_y, ZNEAR, ZFAR);
}

/**
 * Returns the Canvas-ID
 * @return  int     Canvas-ID
 * @access private
 */
canvasType GNRGL3DCanvas::getCanvasID()
{
	return CANVAS3D;
}

void GNRGL3DCanvas::OnMouseWheel(wxMouseEvent& event)
{
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	myevent.setMouseEvent(event);
	myevent.setCanvasID(getCanvasID());
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}
