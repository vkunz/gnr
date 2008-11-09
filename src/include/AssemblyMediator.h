/**
 * AssemblyMediator
 * @name        AssemblyMediator.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef ASSEMBLYMEDIATOR_H
#define ASSEMBLYMEDIATOR_H

#include "Mediator.h"
#include "Assembly.h"

class AssemblyMediator: public Mediator
{
public:

	AssemblyMediator();
	void setAssembly(Assembly* assembly);                 //set selected assembly id
	void setGLCamera(GLCamera* WXUNUSED(camera)) {}; //not needed in assembly mediator
	void initialize(GLNotifyEvent& event);           //initialize assembly mediator
	int  translate(GLNotifyEvent& event);            //perform translation to assembly
	void finalize();
	
protected:

	virtual void MoveXY(GLNotifyEvent& event) = 0;
	virtual void MoveXZ(GLNotifyEvent& event) = 0;
	virtual void RotateXY(GLNotifyEvent& event) = 0;
	virtual void RotateY(GLNotifyEvent& event) = 0;
	virtual void RotateXZ(GLNotifyEvent& event) = 0;
	
	Assembly* m_Assembly;
	Vertex cam_pos, obj_pos;
	
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

#endif // ASSEMBLYMEDIATOR_H
