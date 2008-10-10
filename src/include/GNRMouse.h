/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * defines the mouse controller class
 * @name        GNRMouse.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRMOUSE_H_
#define _GNRMOUSE_H_

#include <wx/dcclient.h>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/timer.h>

#include "GNRAssembly.h"

class GNRMouse
{
private:

	//action to do
	enum { MOVEXZ = 0, MOVEXY, ROTATE };
	int status;
	
	//remember if in use or not
	bool in_use;
	
	//old mouse coords on initialized dragging
	int	m_mouse_x, m_mouse_y;
	
	//window dimensions of actual frame
	int window_w, window_h;
	
	//saved positions in 3d canvas frame (later stored in assembly)
	float posx, posy, posz;
	float phix, phiy, phiz, angle;
	float phix_old, phiy_old;
	
	//pointer to assembly
	GNRAssembly* my_object;
	
protected:

	/**
	 * rotate the object on XY axis
	 * @param       wxMouseEvent    mouse event of current frame
	 * @access      protected
	 * @author      patrick.kracht
	 */
	void ObjectRotate(wxMouseEvent& event);
	
	/**
	 * move the object in XY dimension
	 * @param       wxMouseEvent    mouse event of current frame
	 * @access      protected
	 * @author      patrick.kracht
	 */
	void ObjectMoveXY(wxMouseEvent& event);
	
	/**
	 * move the object in XZ dimension
	 * @param       wxMouseEvent    mouse event of current frame
	 * @access      protected
	 * @author      patrick.kracht
	 */
	void ObjectMoveXZ(wxMouseEvent& event);
	
	/**
	 * init method for setting up the mouse controller
	 * @access      protected
	 * @author      patrick.kracht
	 */
	void Init();
	
public:

	/**
	 * returns true if controller in use
	 * @return      boolean         status of usage
	 * @access      public
	 * @author      patrick.kracht
	 */
	bool IsInUse()
	{
		return in_use;
	};
	
	/**
	 * fetches control of mouse class
	 * @param       wxMouseEvent    mouse event of current frame
	 * @return      boolean         status of get action
	 * @access      public
	 * @author      patrick.kracht
	 */
	bool GetControl(wxMouseEvent& event);
	
	/**
	 * frees the controler for other clients
	 * @param       wxMouseEvent    mouse event of current frame
	 * @return      boolean         status of drop action
	 * @access      public
	 * @author      patrick.kracht
	 */
	bool DropControl(wxMouseEvent& event);
	
	/**
	 * transforming selected object on mouse event
	 * @param       wxMouseEvent    mouse event of current frame
	 * @access      public
	 * @author      patrick.kracht
	 */
	void ObjectTransform(wxMouseEvent& event);
	
	/**
	 * constructor of GNRMouse
	 * @access      public
	 * @author      patrick.kracht
	 */
	GNRMouse();
	
	/**
	 * destructor of GNRMouse
	 * @access      public
	 * @author      patrick.kracht
	 */
	virtual ~GNRMouse();
	
};

#endif // _GNRMOUSE_H_
