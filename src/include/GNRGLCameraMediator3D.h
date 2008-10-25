#ifndef GNRGLCAMERAMEDIATOR3D_H
#define GNRGLCAMERAMEDIATOR3D_H

#include "GNRGLCamera.h"
#include "GNRGLCameraMediator.h"

class GNRGLCameraMediator3D: public GNRGLCameraMediator
{
public:

	GNRGLCameraMediator3D() {};
	virtual ~GNRGLCameraMediator3D() {};
	
protected:

private:

	void MoveXY(GNRGLNotifyEvent& event);
	void MoveXZ(GNRGLNotifyEvent& event);
	void RotateXY(GNRGLNotifyEvent& event);
	void RotateXZ(GNRGLNotifyEvent& event);
	
};

#endif // GNRGLCAMERAMEDIATOR_H
