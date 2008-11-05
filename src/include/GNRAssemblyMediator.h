/**
 * GNRAssemblyMediator
 * @name        GNRAssemblyMediator.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRASSEMBLYMEDIATOR_H
#define GNRASSEMBLYMEDIATOR_H

#include "GNRMediator.h"
#include "GNRAssembly.h"

class GNRAssemblyMediator: public GNRMediator
{
public:

	GNRAssemblyMediator();
	void setAssembly(GNRAssembly* assembly);                 //set selected assembly id
	void setGLCamera(GNRGLCamera* WXUNUSED(camera)) {}; //not needed in assembly mediator
	void initialize(GNRGLNotifyEvent& event);           //initialize assembly mediator
	int  translate(GNRGLNotifyEvent& event);            //perform translation to assembly
	void finalize();
	
protected:

	virtual void MoveXY(GNRGLNotifyEvent& event) = 0;
	virtual void MoveXZ(GNRGLNotifyEvent& event) = 0;
	virtual void RotateXY(GNRGLNotifyEvent& event) = 0;
	virtual void RotateY(GNRGLNotifyEvent& event) = 0;
	virtual void RotateXZ(GNRGLNotifyEvent& event) = 0;
	
	GNRAssembly* m_Assembly;
	GNRVertex cam_pos, obj_pos;
	
	//storage on mouse down
	float old_x, old_y, old_z;
	float scale_x, scale_y, scale_z;
	float phi_old, theta_old, rho_old;
	float gl_xmax, gl_ymax, gl_zmax;
	float gl_xmin, gl_ymin, gl_zmin;
	float cam_rot_x, cam_rot_y;
	int window_w, window_h;
	int m_mouse_x, m_mouse_y;
	bool m_initialized;
	
private:

};

#endif // GNRASSEMBLYMEDIATOR_H
