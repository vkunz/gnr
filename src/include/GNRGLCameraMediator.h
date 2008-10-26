#ifndef GNRGLCAMERAMEDIATOR_H
#define GNRGLCAMERAMEDIATOR_H

#include "GNRMediator.h"
#include "GNRGLCamera.h"
#include "GNRVertex.h"

class GNRGLCameraMediator: public GNRMediator
{
public:

	void setGLCamera(GNRGLCamera* camera);              //set pointer to access camera
	void setAssemblyID(int WXUNUSED(assemblyID)) {};    //not needed in camera mediator
	void initialize(GNRGLNotifyEvent& event);           //initialize camera mediator
	int  translate(GNRGLNotifyEvent& event);            //perform translation to camera
	
protected:

	virtual void MoveXY(GNRGLNotifyEvent& event) = 0;
	virtual void MoveXZ(GNRGLNotifyEvent& event) = 0;
	virtual void RotateXY(GNRGLNotifyEvent& event) = 0;
	virtual void RotateXZ(GNRGLNotifyEvent& event) = 0;
	virtual void ZoomIn(GNRGLNotifyEvent& event) = 0;
	
	GNRGLCamera* m_GLCamera;
	
	//storage on mouse down
	int m_mouse_x;
	int m_mouse_y;
	int window_w;
	int window_h;
	float gl_xmax;
	float gl_xmin;
	float gl_ymax;
	float gl_ymin;
	
	GNRVertex old_viewPoint;
	GNRVertex old_viewDir;
	GNRVertex old_rightVector;
	GNRVertex old_upVector;
	float old_rotatedX, old_rotatedY, old_rotatedZ;
	
	
private:


};

#endif // GNRGLCAMERAMEDIATOR_H
