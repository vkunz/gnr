/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * defines the mouse controller class
 * @name        GNRAssemblyProxy.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRAssemblyProxy_H_
#define _GNRAssemblyProxy_H_

#include <wx/dcclient.h>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/timer.h>

#include "GNRAssembly.h"
#include "GNRGLNotifyEvent.h"

class GNRAssemblyProxy
{
private:

	enum { MOVEXZ = 0, MOVEXY, ROTATE };
	int status;                         //action to perform with event
	bool in_use;                        //remember usage of this controller
	int	m_mouse_x, m_mouse_y;           //old mouse coords (x,y) on frame
	int window_w, window_h;             //window dimensions of actual frame (width,height)
	float phi_old, theta_old, rho_old;  //old copy of previous object params (x,y,z-rotation)
	float ass_x, ass_y, ass_z;          //old copy of previous object params (x,y,z-coords)
	GNRAssembly* my_object;             //pointer to assembly object
	
protected:

	void ObjectRotate(GNRGLNotifyEvent& event);
	void ObjectMoveXY(GNRGLNotifyEvent& event);
	void ObjectMoveXZ(GNRGLNotifyEvent& event);
	void init();
	
public:

	GNRAssemblyProxy();
	virtual ~GNRAssemblyProxy();
	void setAssembly(GNRAssembly* assembly);
	void setWindow(GNRGLNotifyEvent& event);
	bool getControl(GNRGLNotifyEvent& event);
	void dropControl(GNRGLNotifyEvent& event);
	void ObjectTransform(GNRGLNotifyEvent& event);
	bool isInUse();
	
};

#endif // _GNRAssemblyProxy_H_
