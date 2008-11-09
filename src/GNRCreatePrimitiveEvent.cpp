/**
 * This event is send with information to generate a new primitive
 * @name        GNRCreatePrimitiveEvent.cpp
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */


#include "GNRCreatePrimitiveEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_CREATE_PRIMITIVE)
IMPLEMENT_DYNAMIC_CLASS(GNRCreatePrimitiveEvent, wxNotifyEvent)


/**
 * constructor of GNRCreatePrimitiveEvent
 * @param   wxEventType     commandType
 * @param   int             event-id

 */
GNRCreatePrimitiveEvent::GNRCreatePrimitiveEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

/**
 * copy-constructor of GNRCreatePrimitiveEvent
 * @param   GNRCreatePrimitiveEvent&    object that should be cloned

 */
GNRCreatePrimitiveEvent::GNRCreatePrimitiveEvent(const GNRCreatePrimitiveEvent& event): wxNotifyEvent(event) {}

/**
 * clones the current object

 */
wxEvent* GNRCreatePrimitiveEvent::Clone() const
{
	return new GNRCreatePrimitiveEvent(*this);
}

/**
 * destructor of GNRCreatePrimitiveEvent

 */
GNRCreatePrimitiveEvent::~GNRCreatePrimitiveEvent() {}

/**
 * sets the position, the primitive should appear at
 * @param   GNRVertex   position of primitive

 */
void GNRCreatePrimitiveEvent::setPosition(GNRVertex pos)
{
	m_position = pos;
}

/**
 * sets angles, the primitve should be rotated
 * @param   GNRVertex   angles of primitive

 */
void GNRCreatePrimitiveEvent::setAngles(GNRVertex angles)
{
	m_angles = angles;
}

/**
 * sets the dimensions (in x, y, z) of the primitive
 * @param   GNRVertex   dimensions of the primitve

 */
void GNRCreatePrimitiveEvent::setDimensions(GNRVertex dim)
{
	m_dimensions = dim;
}

/**
 * sets the type of the primitive
 * @param   primitivesType  type

 */
void GNRCreatePrimitiveEvent::setPrimitiveType(primitivesType type)
{
	m_type = type;
}

/**
 * returns the position, the primitive should be drawn at
 * @return  GNRVertex   position

 */
GNRVertex GNRCreatePrimitiveEvent::getPosition()
{
	return m_position;
}

/**
 * returns the angles, the primitve should be rotated
 * @return  GNRVertex   angles

 */
GNRVertex GNRCreatePrimitiveEvent::getAngles()
{
	return m_angles;
}

/**
 * returns the dimensions, the primitive should have
 * @return  GNRVertex   dimensions

 */
GNRVertex GNRCreatePrimitiveEvent::getDimensions()
{
	return m_dimensions;
}

/**
 * returns the type, the primitive should be
 * @return primitivesType   type of primitive

 */
primitivesType GNRCreatePrimitiveEvent::getPrimitiveType()
{
	return m_type;
}

