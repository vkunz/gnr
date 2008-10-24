#include "GNRAssemblyMediator.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

GNRAssemblyMediator::GNRAssemblyMediator()
{
	m_CanvasID = NONE;
}

GNRAssemblyMediator::~GNRAssemblyMediator()
{
	//dtor
}

void GNRAssemblyMediator::translate(GNRGLNotifyEvent& event)
{
	switch (m_CanvasID)
	{
	case CANVAS2D:
		wxLogDebug(wxT("GNRAssemblyMediator 2D"));
		break;
	case CANVAS3D:
		wxLogDebug(wxT("GNRAssemblyMediator 3D"));
		break;
	default:
		break;
	}
}

void GNRAssemblyMediator::setMode(canvasType canvas_id)
{
	m_CanvasID = canvas_id;
}
