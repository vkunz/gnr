#include "GNRWallMediator.h"
#include "GNRLineDrawEvent.h"
#include "math.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#define WALLHIGHT 2.0
#define WALLDEPTH 0.2

GNRWallMediator::GNRWallMediator()
{
	//ctor
}

GNRWallMediator::~GNRWallMediator()
{
	//dtor
}

void GNRWallMediator::initialize(GNRGLNotifyEvent& event)
{
	window_w = event.getWinX();
	window_h = event.getWinY();
	
	gl_xmax = event.getWorldXmax();
	gl_xmin = event.getWorldXmin();
	
	gl_zmax = event.getWorldZmax();
	gl_zmin = event.getWorldZmin();
	
	m_mouse_x = event.getMouseEvent().GetX();
	m_mouse_y = event.getMouseEvent().GetY();
	
	startPoint.setX(gl_xmin + (float) m_mouse_x / (float) window_w * (gl_xmax-gl_xmin));
	startPoint.setY(0.05);
	startPoint.setZ(gl_zmax + (float) m_mouse_y / (float) window_h * (gl_zmin-gl_zmax));
}

void GNRWallMediator::setAssembly(GNRAssembly* assembly)
{
	m_assembly = assembly;
}

int GNRWallMediator::translate(GNRGLNotifyEvent& event)
{
	endPoint.setX(startPoint.getX() - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().GetX())/window_w);
	endPoint.setY(0.05);
	endPoint.setZ(startPoint.getZ() - (gl_xmax-gl_xmin)/window_w*(m_mouse_y - event.getMouseEvent().GetY()));
	
	// send event to draw current scene
	GNRLineDrawEvent myevent(wxEVT_COMMAND_GNR_LINE_DRAW);
	myevent.SetEventObject(this);
	myevent.setStartPoint(startPoint);
	myevent.setEndPoint(endPoint);
	ProcessEvent(myevent);
	/*
	    wxString str;
	    str << wxT("x:") << startPoint.getX() << wxT("y:") << startPoint.getY() << wxT("z:") << startPoint.getZ() << wxT("\n");
	    str << wxT("x:") << endPoint.getX() << wxT("y:") << endPoint.getY() << wxT("z:") << endPoint.getZ() << wxT("\n");
	    wxLogDebug(str);
	*/
	return 1;
}

void GNRWallMediator::calculate()
{
	/*float deltaX = endPoint.getX() - startPoint.getX();
	float deltaZ = endPoint.getZ() - startPoint.getZ();
	float length = sqrt(deltaX*deltaX + deltaZ*deltaZ);
	
	GNRVertex middlePoint();
	middlePoint.setX((endPoint.getX() + startPoint.getX()) / 2.0);
	middlePoint.setY((endPoint.getY() + startPoint.getY()) / 2.0);
	middlePoint.setZ((endPoint.getZ() + startPoint.getZ()) / 2.0);
	
	double beta = atan2(deltaZ, deltaX) * 180 / PI;
	GNRVertex orientation(0, beta, 0);
	
	m_assembly->setLocationOffset(middlePoint);
	m_assembly->setOrientationOffset(orientation);
	m_assembly->setWidth(length);
	m_assembly->setHeight(WALLHEIGHT);
	m_assembly->setDepth(WALLDEPTH);*/
}

void GNRWallMediator::finalize()
{

}

