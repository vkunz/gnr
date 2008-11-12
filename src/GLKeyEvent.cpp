/**
 * GLKeyEvent
 * @note        [DONE]
 * @name        GLKeyEvent.cpp
 * @date        2008-11-12
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GLKeyEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GL_KEY)
IMPLEMENT_DYNAMIC_CLASS(GLKeyEvent, wxNotifyEvent)

/**
 * constructor of GLKeyEvent
 * @param[in]       commandType     type of event
 * @param[in]       id              id of event
 */
GLKeyEvent::GLKeyEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id)
{
}

/**
 * copy constructor of GLKeyEvent
 * @param[in]       event           object to be copied
 */
GLKeyEvent::GLKeyEvent(const GLKeyEvent& event): wxNotifyEvent(event) {}

/**
 * clones the current object
 * @return      wxEvent*        base-class-pointer
 */
wxEvent* GLKeyEvent::Clone() const
{
	return new GLKeyEvent(*this);
}

/**
 * sets the canvas which generated the event
 * @param[in]       id          id of current canvas
 */
void GLKeyEvent::setCanvasID(canvasType id)
{
	m_canvasID = id;
}

/**
 * returns the canvas-id
 * @return      canvasType      id of the canvas
 */
canvasType GLKeyEvent::getCanvasID()
{
	return m_canvasID;
}

void GLKeyEvent::setKey(wxChar key)
{
	m_key = key;
}

wxChar GLKeyEvent::getKey()
{
	return m_key;
}
