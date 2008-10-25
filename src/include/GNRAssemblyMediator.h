#ifndef GNRASSEMBLYMEDIATOR_H
#define GNRASSEMBLYMEDIATOR_H

#include "GNRMediator.h"
#include "GNRAssembly.h"

class GNRAssemblyMediator: public GNRMediator
{
public:

	GNRAssemblyMediator() {};
	virtual ~GNRAssemblyMediator() {};
	
	void setAssemblyID(int assemblyID);         //set selected assembly id
	void setGLCamera(GNRGLCamera* camera) {};   //not needed in assembly mediator
	void initialize(GNRGLNotifyEvent& event);   //initialize assembly mediator
	int  translate(GNRGLNotifyEvent& event);    //perform translation to assembly
	
protected:

	virtual void MoveXY(GNRGLNotifyEvent& event) = 0;
	virtual void MoveXZ(GNRGLNotifyEvent& event) = 0;
	virtual void RotateXY(GNRGLNotifyEvent& event) = 0;
	virtual void RotateXZ(GNRGLNotifyEvent& event) = 0;
	
	//storage on mouse down
	float old_x;
	float old_y;
	float old_z;
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
	
	GNRAssembly* m_Assembly;
	
private:

};

#endif // GNRASSEMBLYMEDIATOR_H
