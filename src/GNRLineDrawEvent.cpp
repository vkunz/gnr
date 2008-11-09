/**
 * this event is used to send information about points to the scene, to draw
 * the line to the opengl-canvas
 * @name        GNRLineDrawEvent.cpp
 * @date        2008-10-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRLineDrawEvent.h"


DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_LINE_DRAW)
IMPLEMENT_DYNAMIC_CLASS(GNRLineDrawEvent, wxNotifyEvent)

/**
 * constructor of GNRLineDrawEvent
 * @param   wxEventType   commandType
 * @param   int           Event-ID

 */
GNRLineDrawEvent::GNRLineDrawEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

/**
 * copy-constructor of GNRLineDrawEvent
 * @param   GNRLineDrawEvent&   GNRLineDrawEvent that has to be copied

 */
GNRLineDrawEvent::GNRLineDrawEvent(const GNRLineDrawEvent& event): wxNotifyEvent(event) {}

/**
 * clones the actual object

 */
wxEvent* GNRLineDrawEvent::Clone() const
{
	return new GNRLineDrawEvent(*this);
}

/**
 * destructor of GNRLineDrawEvent

 */
GNRLineDrawEvent::~GNRLineDrawEvent() {}

/**
 * sets the start-point of the line that should be drawn
 * @param   GNRVertex&      Vertex with start-Point of the line

 */
void GNRLineDrawEvent::setStartPoint(GNRVertex& startPoint)
{
	m_startPoint = startPoint;
}

/**
 * sets the end-point of the line that should be drawn
 * @param   GNRVertex&      Vertex with end-Point of the line

 */
void GNRLineDrawEvent::setEndPoint(GNRVertex& endPoint)
{
	m_endPoint = endPoint;
}

/**
 * returns the start-point of the line that should be drawn
 * @return   GNRVertex      Vertex with start-Point of the line

 */
GNRVertex GNRLineDrawEvent::getStartPoint()
{
	return m_startPoint;
}

/**
 * returns the end-point of the line that should be drawn
 * @return   GNRVertex      Vertex with end-Point of the line

 */
GNRVertex GNRLineDrawEvent::getEndPoint()
{
	return m_endPoint;
}
