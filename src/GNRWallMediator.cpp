/**
 * Handles mouse-movement to draw walls
 * @name        GNRWallMediator.cpp
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRWallMediator.h"
#include "GNRGlobalDefine.h"
#include "GNRLineDrawEvent.h"
#include "GNRCreatePrimitiveEvent.h"
#include "math.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GNRWallMediator
 * @access      public
 */
GNRWallMediator::GNRWallMediator() {}

/**
 * destructor of GNRWallMediator
 * @access      public
 */
GNRWallMediator::~GNRWallMediator() {}

/**
 * sets values needed for later calculation and sets the startpoint to current mouse-position
 * @param   GNRGLNotifyEvent&    MouseEvent of the canvas
 * @access      public
 */
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
	
	float x = gl_xmin + (float) m_mouse_x / (float) window_w * (gl_xmax-gl_xmin);
	float z = gl_zmax + (float) m_mouse_y / (float) window_h * (gl_zmin-gl_zmax);
	
	doSnapMove(x);
	doSnapMove(z);
	
	startPoint.setX(x);
	startPoint.setY(0.05);
	startPoint.setZ(z);
}

/**
 * calculates the new position of the endpoint of the line and makes canvas draw this line
 * @param   GNRGLNotifyEvent&    MouseEvent of the canvas
 * @access      public
 */
int GNRWallMediator::translate(GNRGLNotifyEvent& event)
{

	float x = startPoint.getX() - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	float z = startPoint.getZ() - (gl_xmax-gl_xmin)/window_w*(m_mouse_y - event.getMouseEvent().GetY());
	
	doSnapMove(x);
	doSnapMove(z);
	
	endPoint.setX(x);
	endPoint.setY(0.05);
	endPoint.setZ(z);
	
	// send event to draw current scene
	GNRLineDrawEvent myevent(wxEVT_COMMAND_GNR_LINE_DRAW);
	myevent.SetEventObject(this);
	myevent.setStartPoint(startPoint);
	myevent.setEndPoint(endPoint);
	ProcessEvent(myevent);
	
	return 1;
}

/**
 * finalizes the wall drawing an sends an event to get the wall-primitive created
 * @access      public
 */
void GNRWallMediator::finalize()
{
	float deltaX = endPoint.getX() - startPoint.getX();
	float deltaZ = endPoint.getZ() - startPoint.getZ();
	float length = sqrt(deltaX*deltaX + deltaZ*deltaZ);
	
	// set middle point ot sif the wall
	GNRVertex middlePoint;
	middlePoint.setX((endPoint.getX() + startPoint.getX()) / 2.0);
	middlePoint.setY(WALLHIGHT / 2.0);
	middlePoint.setZ((endPoint.getZ() + startPoint.getZ()) / 2.0);
	
	double beta = atan2(deltaZ, deltaX) * -180 / M_PI;
	GNRVertex orientation(0, beta, 0);
	GNRVertex dimension(length, WALLHIGHT, WALLDEPTH);
	
	// send event to create cuboid
	GNRCreatePrimitiveEvent myevent(wxEVT_COMMAND_GNR_CREATE_PRIMITIVE);
	myevent.SetEventObject(this);
	myevent.setPrimitiveType(CUBOID);
	myevent.setPosition(middlePoint);
	myevent.setAngles(orientation);
	myevent.setDimensions(dimension);
	ProcessEvent(myevent);
}
