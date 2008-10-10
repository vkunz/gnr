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
 * @access      protected
 */
void GNRMouse::Init()
{
	in_use = false;
	
	status = MOVEXZ;
	
	phix   = phix_old = 0.0f;
	phiy   = phiy_old = 0.0f;
	phiz   = angle    = 0.0f;
}

/**
 * fetches control of mouse class
 * @param       wxMouseEvent    mouse event of current frame
 * @return      boolean         status of get action
 * @access      public
 */
bool GNRMouse::GetControl(wxMouseEvent& event)
{
	//if in use return false
	if (in_use)
	{
		return false;
	}
	
	//store actual mouse coords on control
	m_mouse_x = event.m_x;
	m_mouse_y = event.m_y;
	
	//set usage true
	in_use = true;
	return true;
}

/**
 * frees the controler for other clients
 * @param       wxMouseEvent    mouse event of current frame
 * @access      public
 */
<<<<<<< .mine
bool GNRMouse::DropControl(wxMouseEvent& event)
{
	=======
	    void GNRMouse::DropControl(wxMouseEvent& event)
	{
		>>>>>>> .r91
		//set in use false
		in_use = false;
		return !in_use;
	}
	
	/**
	 * transforming selected object on mouse event
	 * @param       wxMouseEvent    mouse event of current frame
	 * @access      public
	 */
	void GNRMouse::ObjectTransform(wxMouseEvent& event)
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
	
	/**
	 * rotate the object on XY axis
	 * @param       wxMouseEvent    mouse event of current frame
	 * @access      protected
	 */
	void GNRMouse::ObjectRotate(wxMouseEvent& event)
	{
		phiy  = phiy_old + 720.0*((float)(m_mouse_x - event.m_x)/(float)window_w);
		phix  = phix_old + 720.0*((float)(m_mouse_y - event.m_y)/(float)window_h);
	}
	
	/**
	 * move the object in XY dimension
	 * @param       wxMouseEvent    mouse event of current frame
	 * @access      protected
	 */
	void GNRMouse::ObjectMoveXY(wxMouseEvent& event)
	{
		posx -= (float)(m_mouse_x - event.m_x)/300.0*fabs(posz);
		posy -= (float)(event.m_y - m_mouse_y)/300.0*fabs(posz);
	}
	
	/**
	 * move the object in XZ dimension
	 * @param       wxMouseEvent    mouse event of current frame
	 * @access      protected
	 */
	void GNRMouse::ObjectMoveXZ(wxMouseEvent& event)
	{
		posx -= (float)(m_mouse_x - event.m_x)/360.0*fabs(posz);
		posz -= (float)(m_mouse_y - event.m_y)/10.0;
	}
	