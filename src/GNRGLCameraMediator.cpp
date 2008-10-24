#include "GNRGLCameraMediator.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

GNRGLCameraMediator::GNRGLCameraMediator()
{
	m_CanvasID = NONE;
}

GNRGLCameraMediator::~GNRGLCameraMediator()
{
	//dtor
}

void GNRGLCameraMediator::translate(GNRGLNotifyEvent& event)
{
	switch (m_CanvasID)
	{
	case CANVAS2D:
		wxLogDebug(wxT("GNRGLCameraMediator 2D"));
		break;
	case CANVAS3D:
		wxLogDebug(wxT("GNRGLCameraMediator 3D"));
		break;
	default:
		break;
	}
}

void GNRGLCameraMediator::setMode(canvasType canvas_id)
{
	m_CanvasID = canvas_id;
}
