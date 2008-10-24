#include "GNRGLCameraMediator.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

GNRGLCameraMediator::GNRGLCameraMediator()
{
	m_CanvasID = NONE;
	m_GLCamera = NULL;
}

GNRGLCameraMediator::~GNRGLCameraMediator()
{
	//dtor
}

int GNRGLCameraMediator::translate(GNRGLNotifyEvent& event)
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
	
	return 0;
}

void GNRGLCameraMediator::setGLCamera(GNRGLCamera* camera)
{
	m_GLCamera = camera;
}
