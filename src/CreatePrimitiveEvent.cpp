/**
 * This event is send with information to generate a new primitive
 * @note        [DONE]
 * @name        CreatePrimitiveEvent.cpp
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */


#include "CreatePrimitiveEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GNR_CREATE_PRIMITIVE)
IMPLEMENT_DYNAMIC_CLASS(CreatePrimitiveEvent, wxNotifyEvent)


/**
 * constructor of CreatePrimitiveEvent
 * @param[in]       commandType         Type of event
 * @param[in]       id                  event-id
 */
CreatePrimitiveEvent::CreatePrimitiveEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id) {}

/**
 * copy-constructor of CreatePrimitiveEvent
 * @param[in]       WXUNUSED     unused event               event-object that has to be copied
 */
CreatePrimitiveEvent::CreatePrimitiveEvent(const CreatePrimitiveEvent& event): wxNotifyEvent(event) {}

/**
 * clones the current object
 * @return          wxEvent*            base-class-pointer
 */
wxEvent* CreatePrimitiveEvent::Clone() const
{
	return new CreatePrimitiveEvent(*this);
}

/**
 * destructor of CreatePrimitiveEvent
 */
CreatePrimitiveEvent::~CreatePrimitiveEvent() {}

/**
 * sets the position, the primitive should appear at
 * @param[in]       pos            position of primitive
 */
void CreatePrimitiveEvent::setPosition(Vertex pos)
{
	m_position = pos;
}

/**
 * sets angles, the primitve should be rotated
 * @param[in]       angles          angles of primitive
 */
void CreatePrimitiveEvent::setAngles(Vertex angles)
{
	m_angles = angles;
}

/**
 * sets the dimensions (in x, y, z) of the primitive
 * @param[in]       dim             dimensions of the primitve

 */
void CreatePrimitiveEvent::setDimensions(Vertex dim)
{
	m_dimensions = dim;
}

/**
 * sets the type of the primitive
 * @param[in]       type            type of primitive
 */
void CreatePrimitiveEvent::setPrimitiveType(primitivesType type)
{
	m_type = type;
}

/**
 * returns the position, the primitive should be drawn at
 * @return          Vertex          position
 */
Vertex CreatePrimitiveEvent::getPosition()
{
	return m_position;
}

/**
 * returns the angles, the primitve should be rotated
 * @return          Vertex          angles

 */
Vertex CreatePrimitiveEvent::getAngles()
{
	return m_angles;
}

/**
 * returns the dimensions, the primitive should have
 * @return          Vertex          dimensions
 */
Vertex CreatePrimitiveEvent::getDimensions()
{
	return m_dimensions;
}

/**
 * returns the type, the primitive should be
 * @return          primitivesType  type of primitive
 */
primitivesType CreatePrimitiveEvent::getPrimitiveType()
{
	return m_type;
}