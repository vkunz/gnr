/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * the mouse controller class implements the conversion and
 * detection of object movements calculates world coordinates
 * for the glcanvas frames
 * @name        GNRAssemblyProxy.cpp
 * @date        2008-10-09
 * @author              Konstantin Balabin  <k.balabin@googlemail.com>
 * @author              Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author              Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author              Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssemblyProxy.h"
#include <wx/math.h>

#include "GNRAssembly.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GNRAssemblyProxy
 * @access      public
 */
GNRAssemblyProxy::GNRAssemblyProxy()
{
	init();
}

/**
 * destructor of GNRAssemblyProxy
 * @access      public
 */
GNRAssemblyProxy::~GNRAssemblyProxy()
{
}

/**
 * init method for setting up the mouse controller
 * @access      public
 */
void GNRAssemblyProxy::setWindow(GNRGLNotifyEvent& event)
{
	window_w = event.getWinX();
	window_h = event.getWinY();
}

/**
 * init method for setting up the mouse controller
 * @param       int         width of frame
 * @param       int         height of frame
 * @access      public
 */
void GNRAssemblyProxy::setDirection(int dir)
{
	status = dir;
}


/**
 * init method for setting up the mouse controller
 * @access      protected
 */
void GNRAssemblyProxy::init()
{
	//controller not in use
	in_use = false;
	
	//set default to move XY axis
	status = MOVEXY;
	
	//my_object to null pointer
	my_object = NULL;
}

/**
 * set assembly pointer
 * @param       GNRAssembly     pointer to assembly object
 * @access      public
 */
void GNRAssemblyProxy::setAssembly(GNRAssembly* assembly)
{
	//store object pointer
	my_object = (GNRAssembly*) assembly;
}

/**
 * fetches control of mouse class
 * @param       GNRAssembly     pointer to assembly object
 * @param       wxMouseEvent    mouse event of current frame
 * @return      boolean         status of get action
 * @access      public
 */
bool GNRAssemblyProxy::getControl(GNRGLNotifyEvent& event)
{
	//if in use return false
	if (in_use)
	{
		return false;
	}
	//set usage true
	in_use = true;
	
	//store old rotation values
	phi_old   = my_object->getPhi();
	theta_old = my_object->getTheta();
	rho_old   = my_object->getRho();
	
	//store old rotation values
	ass_x = my_object->getX();
	ass_y = my_object->getY();
	ass_z = my_object->getZ();
	
	//store actual mouse coords on control
	m_mouse_x = event.getMouseEvent().m_x;
	m_mouse_y = event.getMouseEvent().m_y;
	
	return true;
}

/**
 * frees the controler for other clients
 * @param       wxMouseEvent    mouse event of current frame
 * @access      public
 */
void GNRAssemblyProxy::dropControl(GNRGLNotifyEvent& event)
{
	//set in use false
	in_use = false;
}

/**
 * transforming selected object on mouse event
 * @param       wxMouseEvent    mouse event of current frame
 * @access      public
 */
void GNRAssemblyProxy::ObjectTransform(GNRGLNotifyEvent& event)
{
	if (in_use)
	{
		switch (status)
		{
		case MOVEXZ:
			ObjectMoveXZ(event);
			break;
		case MOVEXY:
			ObjectMoveXY(event);
			break;
		case ROTATE:
			ObjectRotate(event);
			break;
		default:
			ObjectMoveXZ(event);
			break;
		}
	}
}

/**
 * rotate the object on XY axis
 * @param       wxMouseEvent    mouse event of current frame
 * @access      protected
 */
void GNRAssemblyProxy::ObjectRotate(GNRGLNotifyEvent& event)
{
	my_object->setPhi(phi_old + 720.0*((float)(m_mouse_y - event.getMouseEvent().m_y)/(float)window_h));
	my_object->setTheta(theta_old + 720.0*((float)(m_mouse_x - event.getMouseEvent().m_x)/(float)window_w));
}

/**
 * move the object in XY dimension
 * @param       wxMouseEvent    mouse event of current frame
 * @access      protected
 */
void GNRAssemblyProxy::ObjectMoveXY(GNRGLNotifyEvent& event)
{
	my_object->setX(ass_x - (float)((1.0f+fabs(ass_z))*(m_mouse_x - event.getMouseEvent().m_x)/50.0f));
	my_object->setY(ass_y - (float)((1.0f+fabs(ass_z))*(event.getMouseEvent().m_y - m_mouse_y)/50.0f));
}

/**
 * move the object in XZ dimension
 * @param       wxMouseEvent    mouse event of current frame
 * @access      protected
 */
void GNRAssemblyProxy::ObjectMoveXZ(GNRGLNotifyEvent& event)
{
	my_object->setZ(ass_z - (float)(m_mouse_y - event.getMouseEvent().m_y)/13.0f);
	my_object->setX(ass_x - (float)((1.0f+fabs(my_object->getZ())*2.0f)*(m_mouse_x - event.getMouseEvent().m_x)/100.0f));
}

/**
 * check usage of mouse controller
 * @return      boolean         status of usage
 * @access      public
 */
bool GNRAssemblyProxy::isInUse()
{
	return in_use;
}
