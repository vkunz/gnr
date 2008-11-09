/**
 * this event is used to send information about points to the scene, to draw
 * the line to the opengl-canvas
 * @name        LineDrawEvent.cpp
 * @date        2008-10-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "LineDrawEvent.h"


DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_LINE_DRAW)
IMPLEMENT_DYNAMIC_CLASS(LineDrawEvent, wxNotifyEvent)

/**
 * constructor of LineDrawEvent
 * @param   wxEventType   commandType
 * @param   int           Event-ID

 */
LineDrawEvent::LineDrawEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

/**
 * copy-constructor of LineDrawEvent
 * @param   LineDrawEvent&   LineDrawEvent that has to be copied

 */
LineDrawEvent::LineDrawEvent(const LineDrawEvent& event): wxNotifyEvent(event) {}

/**
 * clones the actual object

 */
wxEvent* LineDrawEvent::Clone() const
{
	return new LineDrawEvent(*this);
}

/**
 * destructor of LineDrawEvent

 */
LineDrawEvent::~LineDrawEvent() {}

/**
 * sets the start-point of the line that should be drawn
 * @param   Vertex&      Vertex with start-Point of the line

 */
void LineDrawEvent::setStartPoint(Vertex& startPoint)
{
	m_startPoint = startPoint;
}

/**
 * sets the end-point of the line that should be drawn
 * @param   Vertex&      Vertex with end-Point of the line

 */
void LineDrawEvent::setEndPoint(Vertex& endPoint)
{
	m_endPoint = endPoint;
}

/**
 * returns the start-point of the line that should be drawn
 * @return   Vertex      Vertex with start-Point of the line

 */
Vertex LineDrawEvent::getStartPoint()
{
	return m_startPoint;
}

/**
 * returns the end-point of the line that should be drawn
 * @return   Vertex      Vertex with end-Point of the line

 */
Vertex LineDrawEvent::getEndPoint()
{
	return m_endPoint;
}
