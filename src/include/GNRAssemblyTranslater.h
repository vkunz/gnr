/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * defines the mouse controller class
 * @name        GNRAssemblyTranslater.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRAssemblyTranslater_H_
#define _GNRAssemblyTranslater_H_

#include <wx/dcclient.h>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/timer.h>

#include "GNRAssembly.h"
#include "GNRGLCamera.h"
#include "GNRGLNotifyEvent.h"

class GNRAssemblyTranslater
{
private:

	enum { MOVEXZ = 0, MOVEXY, ROTATE };
	int status;                         //action to perform with event
	bool in_use;                        //remember usage of this controller
	int	m_mouse_x, m_mouse_y;           //old mouse coords (x,y) on frame
	int window_w, window_h;             //window dimensions of actual frame (width,height)
	float phi_old, theta_old, rho_old;  //old copy of previous object params (x,y,z-rotation)
	float old_x, old_y, old_z;          //old copy of previous object params (x,y,z-coords)
	GNRAssembly* my_object;             //pointer to assembly object
	GNRGLCamera* m_glcamera;                 //pointer to camera object
	
protected:

	void ObjectRotate(GNRGLNotifyEvent& event);
	void ObjectMoveXY(GNRGLNotifyEvent& event);
	void ObjectMoveXZ(GNRGLNotifyEvent& event);
	void init();
	
public:

	GNRAssemblyTranslater();
	virtual ~GNRAssemblyTranslater();
	void setAssembly(GNRAssembly* assembly);
	void setGLCamera(GNRGLCamera* camera);
	void setWindow(GNRGLNotifyEvent& event);
	bool getControl(GNRGLNotifyEvent& event);
	void dropControl(GNRGLNotifyEvent& event);
	void ObjectTransform(GNRGLNotifyEvent& event);
	void setDirection(int dir);
	bool isInUse();
	
};

#endif // _GNRAssemblyTranslater_H_
