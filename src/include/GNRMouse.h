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

	enum { MOVEXZ = 0, MOVEXY, ROTATE };
	int status;                         //action to perform with event
	bool in_use;                        //remember usage of this controller
	int	m_mouse_x, m_mouse_y;           //old mouse coords (x,y) on frame
	int window_w, window_h;             //window dimensions of actual frame (width,height)
	float phi_old, theta_old, rho_old;  //old copy of previous object params (x,y,z-rotation)
	GNRAssembly* my_object;             //pointer to assembly object
	
protected:

	void ObjectRotate(wxMouseEvent& event);
	void ObjectMoveXY(wxMouseEvent& event);
	void ObjectMoveXZ(wxMouseEvent& event);
	void Init();
	
public:

	GNRMouse();
	virtual ~GNRMouse();
	void SetWindow(int width, int height);
	bool GetControl(wxMouseEvent& event);
	void DropControl(wxMouseEvent& event);
	void ObjectTransform(wxMouseEvent& event);
	bool IsInUse()
	{
		return in_use;
	};
	
};

#endif // _GNRMOUSE_H_
