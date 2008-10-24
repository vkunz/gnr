#ifndef GNRGLCAMERAMEDIATOR_H
#define GNRGLCAMERAMEDIATOR_H

#include "GNRMediator.h"
#include "GNRGLCamera.h"

class GNRGLCameraMediator: public GNRMediator
{
public:

	GNRGLCameraMediator();
	void setMode(canvasType canvas_id);
	void setAssemblyID(int assemblyID) {};      //not needed in camera mediator
	void setGLCamera(GNRGLCamera* camera);      //set pointer to access camera
	void translate(GNRGLNotifyEvent& event);    //perform translation to camera
	virtual ~GNRGLCameraMediator();
	
protected:

private:
	GNRGLCamera* m_GLCamera;
	
};

#endif // GNRGLCAMERAMEDIATOR_H
