#include "GNRGLNotifyEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_GL_NOTIFY)
IMPLEMENT_DYNAMIC_CLASS(GNRGLNotifyEvent, wxNotifyEvent)

/**
 * constructor of an even
 * @param       wxEventType
 * @param       int
 * @access      public
 */
GNRGLNotifyEvent::GNRGLNotifyEvent(wxEventType commandType, int id)
		: wxNotifyEvent(commandType, id)
{
	selectedObj = 0;
}

/**
 * copy-constructor of an event
 * @param       wxEventType
 * @access      public
 */
GNRGLNotifyEvent::GNRGLNotifyEvent(const GNRGLNotifyEvent& event): wxNotifyEvent(event) {}

/**
 * clone an event
 * @return      wxEvent*       pointer to cloned event
 * @access      public
 */
wxEvent* GNRGLNotifyEvent::Clone() const
{
	return new GNRGLNotifyEvent(*this);
}

/**
 * set canvas id
 * @param       int     id of canvas
 * @access      public
 */
void GNRGLNotifyEvent::setCanvasID(int id)
{
	canvasID = id;
}

/**
 * get canvas id
 * @return      int       id of selected canvas
 * @access      public
 */
int GNRGLNotifyEvent::getCanvasID()
{
	return canvasID;
}

/**
 * set object id
 * @param       int
 * @access      public
 */
void GNRGLNotifyEvent::setSelectedObj(int obj)
{
	selectedObj = obj;
}

/**
 * get object id
 * @return      int       id of selected object
 * @access      public
 */
int GNRGLNotifyEvent::getSelectedObj()
{
	return selectedObj;
}

/**
 * get mouse event
 * @return      wxMouseEvent       mouse event
 * @access      public
 */
wxMouseEvent GNRGLNotifyEvent::getMouseEvent()
{
	return event;
}

/**
 * set mouse event
 * @param       wxMouseEvent
 * @access      public
 */
void GNRGLNotifyEvent::setMouseEvent(wxMouseEvent event)
{
	this->event = event;
}

/**
 * set windows dimensions
 * @param       int         window width
 * @param       int         window height
 * @access      public
 */
void GNRGLNotifyEvent::setWindowSize(int x, int y)
{
	win_x = x;
	win_y = y;
}

/**
 * get window width
 * @return      int       window width
 * @access      public
 */
int GNRGLNotifyEvent::getWinX()
{
	return win_x;
}

/**
 * get windows height
 * @return      int       window height
 * @access      public
 */
int GNRGLNotifyEvent::getWinY()
{
	return win_y;
}

/**
 * set world dimensions
 * @param       float       world width
 * @param       float       world height
 * @access      public
 */
void GNRGLNotifyEvent::setWorldSize(float x, float y)
{
	world_x = x;
	world_y = y;
}

/**
 * get world width
 * @return      float       world width
 * @access      public
 */
float GNRGLNotifyEvent::getWorldX()
{
	return world_x;
}

/**
 * get world height
 * @return      float       world height
 * @access      public
 */
float GNRGLNotifyEvent::getWorldY()
{
	return world_y;
}
