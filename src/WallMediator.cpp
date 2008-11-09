#include "WallMediator.h"
#include "LineDrawEvent.h"
#include "CreatePrimitiveEvent.h"
#include "math.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#define WALLHIGHT 2.0
#define WALLDEPTH 0.2

/**
 * constructor of wall mediator
 */
WallMediator::WallMediator()
{
}

/**
 * destructor of wall mediator
 */WallMediator::~WallMediator()
{
}

/**
 * init the wall mediator
 * @param[in]       event       GLNotifyEvent
 */
void WallMediator::initialize(GLNotifyEvent& event)
{
	//backup old startpoint
	endPoint = startPoint;
	
	//reset moved flag
	moved = false;
	
	window_w = event.getWinX();
	window_h = event.getWinY();
	
	gl_xmax = event.getWorldXmax();
	gl_xmin = event.getWorldXmin();
	
	gl_zmax = event.getWorldZmax();
	gl_zmin = event.getWorldZmin();
	
	m_mouse_x = event.getMouseEvent().GetX();
	m_mouse_y = event.getMouseEvent().GetY();
	
	float x = gl_xmin + (float) m_mouse_x / (float) window_w * (gl_xmax-gl_xmin);
	float z = gl_zmax + (float) m_mouse_y / (float) window_h * (gl_zmin-gl_zmax);
	
	doSnapMove(x);
	doSnapMove(z);
	
	startPoint.setX(x);
	startPoint.setY(0.01);
	startPoint.setZ(z);
}

/**
 * force wall mediator to translate
 * @param[in]       event        GLNotifyEvent
 * @return          int          return 1 if ok
 */
int WallMediator::translate(GLNotifyEvent& event)
{
	moved = true;
	
	float x = startPoint.getX() - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	float z = startPoint.getZ() - (gl_xmax-gl_xmin)/window_w*(m_mouse_y - event.getMouseEvent().GetY());
	
	doSnapMove(x);
	doSnapMove(z);
	
	endPoint.setX(x);
	endPoint.setY(0.01);
	endPoint.setZ(z);
	
	// send event to draw current scene
	LineDrawEvent myevent(wxEVT_COMMAND_GNR_LINE_DRAW);
	myevent.SetEventObject(this);
	myevent.setStartPoint(startPoint);
	myevent.setEndPoint(endPoint);
	ProcessEvent(myevent);
	
	return 1;
}

/**
 * finalize wall mediator (for undo and redo)
 */
void WallMediator::finalize()
{
	float deltaX = endPoint.getX() - startPoint.getX();
	float deltaZ = endPoint.getZ() - startPoint.getZ();
	float length = sqrt(deltaX*deltaX + deltaZ*deltaZ);
	
	// set middle point of the wall
	Vertex middlePoint;
	middlePoint.setX((endPoint.getX() + startPoint.getX()) / 2.0);
	middlePoint.setY(WALLHIGHT / 2.0);
	middlePoint.setZ((endPoint.getZ() + startPoint.getZ()) / 2.0);
	
	double beta = atan2(deltaZ, deltaX) * -180 / M_PI;
	Vertex orientation(0, beta, 0);
	Vertex dimension(length, WALLHIGHT, WALLDEPTH);
	
	// send event to create cuboid
	CreatePrimitiveEvent myevent(wxEVT_COMMAND_GNR_CREATE_PRIMITIVE);
	myevent.SetEventObject(this);
	myevent.setPrimitiveType(CUBOID);
	myevent.setPosition(middlePoint);
	myevent.setAngles(orientation);
	myevent.setDimensions(dimension);
	ProcessEvent(myevent);
	
	if (moved)
	{
		//if moved, store endpoint
		startPoint = endPoint;
	}
}
