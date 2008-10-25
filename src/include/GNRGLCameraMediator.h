#ifndef GNRGLCAMERAMEDIATOR_H
#define GNRGLCAMERAMEDIATOR_H

#include "GNRMediator.h"
#include "GNRGLCamera.h"

class GNRGLCameraMediator: public GNRMediator
{
public:

	GNRGLCameraMediator() {};
	virtual ~GNRGLCameraMediator() {};
	
	void setGLCamera(GNRGLCamera* camera);      //set pointer to access camera
	void setAssemblyID(int assemblyID) {};      //not needed in camera mediator
	void initialize(GNRGLNotifyEvent& event);   //initialize camera mediator
	int  translate(GNRGLNotifyEvent& event);    //perform translation to camera
	
protected:

	virtual void MoveXY(GNRGLNotifyEvent& event) = 0;
	virtual void MoveXZ(GNRGLNotifyEvent& event) = 0;
	virtual void RotateXY(GNRGLNotifyEvent& event) = 0;
	virtual void RotateXZ(GNRGLNotifyEvent& event) = 0;
	
	GNRGLCamera* m_GLCamera;
	
	//storage on mouse down
	int m_mouse_x;
	int m_mouse_y;
	
private:

};

#endif // GNRGLCAMERAMEDIATOR_H
