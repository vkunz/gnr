/**
 * MeasureMediator
 * @name        MeasureMediator.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "GLNotifyEvent.h"
#include "MeasureMediator.h"
#include "LineDrawEvent.h"
#include "CreatePrimitiveEvent.h"
#include "math.h"

#define WALLHIGHT 2.0
#define WALLDEPTH 0.2

/**
 * constructor of wall mediator
 */
MeasureMediator::MeasureMediator()
{
}

/**
 * destructor of wall mediator
 */MeasureMediator::~MeasureMediator()
{
}

/**
 * init the wall mediator
 * @param[in]       event       GLNotifyEvent
 */
void MeasureMediator::initialize(GLNotifyEvent& event)
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
int MeasureMediator::translate(GLNotifyEvent& event)
{
	moved = true;

	float x = startPoint.getX() - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	float z = startPoint.getZ() - (gl_xmax-gl_xmin)/window_w*(m_mouse_y - event.getMouseEvent().GetY());

	doSnapMove(x);
	doSnapMove(z);

	endPoint.setX(x);
	endPoint.setY(0.15); //draw 15cm over ground
	endPoint.setZ(z);

	// send event to draw current scene
	LineDrawEvent myevent(wxEVT_COMMAND_GNR_LINE_DRAW);
	myevent.SetEventObject(this);
	myevent.setStartPoint(startPoint);
	myevent.setEndPoint(endPoint);
	myevent.SetInt(0);
	ProcessEvent(myevent);

	return 1;
}

/**
 * finalize wall mediator (for undo and redo)
 */
void MeasureMediator::finalize()
{
}
