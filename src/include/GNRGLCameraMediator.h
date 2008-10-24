#ifndef GNRGLCAMERAMEDIATOR_H
#define GNRGLCAMERAMEDIATOR_H

#include "GNRMediator.h"
#include "GNRGLCamera.h"

class GNRGLCameraMediator: public GNRMediator
{
public:

	GNRGLCameraMediator();
	virtual ~GNRGLCameraMediator();
	
	void setAssemblyID(int assemblyID) {};      //not needed in camera mediator
	void setGLCamera(GNRGLCamera* camera);      //set pointer to access camera
	void initialize(GNRGLNotifyEvent& event) {};
	int  translate(GNRGLNotifyEvent& event);    //perform translation to camera
	
protected:

private:
	GNRGLCamera* m_GLCamera;
	
};

#endif // GNRGLCAMERAMEDIATOR_H
