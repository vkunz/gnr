/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * the mouse controller class implements the conversion and
 * detection of object movements calculates world coordinates
 * for the glcanvas frames
 * @name        GNRMouse.cpp
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRMouse.h"
#include <wx/math.h>

#include "GNRAssembly.h"

#if defined(__WXDEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GNRMouse
 * @access      public
 */
GNRMouse::GNRMouse()
{
	Init();
}

/**
 * destructor of GNRMouse
 * @access      public
 */
GNRMouse::~GNRMouse()
{
}

/**
 * init method for setting up the mouse controller
 * @param       int         width of frame
 * @param       int         height of frame
 * @access      public
 */
void GNRMouse::SetWindow(int width, int height)
{
	window_w = width;
	window_h = height;
}

/**
 * init method for setting up the mouse controller
 * @access      protected
 */
void GNRMouse::Init()
{
	//controller not in use
	in_use = false;
	
	//set default to move XY axis
	status = MOVEXZ;
	
	//initialize with default values
	SetWindow(640,480);
}

/**
 * fetches control of mouse class
 * @param       GNRAssembly     pointer to assembly object
 * @param       wxMouseEvent    mouse event of current frame
 * @return      boolean         status of get action
 * @access      public
 */
bool GNRMouse::GetControl(GNRAssembly* object, wxMouseEvent& event)
{
	//if in use return false
	if (in_use)
	{
		return false;
	}
	//set usage true
	in_use = true;
	
	//store object pointer
	my_object = object;
	
	//store old rotation values
	phi_old   = my_object->m_phi;
	theta_old = my_object->m_theta;
	rho_old   = my_object->m_rho;
	
	//store actual mouse coords on control
	m_mouse_x = event.m_x;
	m_mouse_y = event.m_y;
	
	return true;
}

/**
 * frees the controler for other clients
 * @param       wxMouseEvent    mouse event of current frame
 * @access      public
 */
void GNRMouse::DropControl(wxMouseEvent& event)
{
	//set in use false
	in_use = false;
}

/**
 * transforming selected object on mouse event
 * @param       wxMouseEvent    mouse event of current frame
 * @access      public
 */
void GNRMouse::ObjectTransform(wxMouseEvent& event)
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
void GNRMouse::ObjectRotate(wxMouseEvent& event)
{
	my_object->m_phi    = phi_old   + 720.0*((float)(m_mouse_y - event.m_y)/(float)window_h);
	my_object->m_theta  = theta_old + 720.0*((float)(m_mouse_x - event.m_x)/(float)window_w);
}

/**
 * move the object in XY dimension
 * @param       wxMouseEvent    mouse event of current frame
 * @access      protected
 */
void GNRMouse::ObjectMoveXY(wxMouseEvent& event)
{
	my_object->m_xOffset -= (float)(m_mouse_x - event.m_x)/300.0*fabs(my_object->m_yOffset);
	my_object->m_yOffset -= (float)(event.m_y - m_mouse_y)/300.0*fabs(my_object->m_yOffset);
}

/**
 * move the object in XZ dimension
 * @param       wxMouseEvent    mouse event of current frame
 * @access      protected
 */
void GNRMouse::ObjectMoveXZ(wxMouseEvent& event)
{
	my_object->m_xOffset -= (float)(m_mouse_x - event.m_x)/360.0*fabs(my_object->m_yOffset);
	my_object->m_zOffset -= (float)(m_mouse_y - event.m_y)/10.0;
}
