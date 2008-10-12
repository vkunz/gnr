#include "GNRController.h"
#include "wx/wx.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

GNRController::GNRController()
{
	// create MainFrame
	mainFrame = new GNRFrame(0);
//    SetTopWindow(mainFrame);

	// initialize GNRMouse
	mouse = new GNRMouse;
}

void GNRController::OnGLMouseEvent(GNRGLMouseEvent& event)
{
#if defined(__ATHOS_DEBUG__)
	wxLogMessage(_("Event ausgelöst"));
#endif
}
