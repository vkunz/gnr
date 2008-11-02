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

	void GNRMediator()
	{
		m_Assembly    = NULL;
		m_initialized = false;
	};
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
	
	//storage on mouse down
	float old_x;
	float old_y;
	float old_z;
	float scale_x;
	float scale_y;
	float scale_z;
	float phi_old;
	float theta_old;
	float rho_old;
	float gl_xmax;
	float gl_ymax;
	float gl_xmin;
	float gl_ymin;
	int window_w;
	int window_h;
	int m_mouse_x;
	int m_mouse_y;
	bool m_initialized;
	
private:

};

#endif // GNRASSEMBLYMEDIATOR_H
