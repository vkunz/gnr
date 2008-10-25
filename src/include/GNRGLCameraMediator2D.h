#ifndef GNRGLCAMERAMEDIATOR2D_H
#define GNRGLCAMERAMEDIATOR2D_H

#include "GNRGLCamera.h"
#include "GNRGLCameraMediator.h"

class GNRGLCameraMediator2D: public GNRGLCameraMediator
{

private:

	void MoveXY(GNRGLNotifyEvent& event);
	void MoveXZ(GNRGLNotifyEvent& event);
	void RotateXY(GNRGLNotifyEvent& event);
	void RotateXZ(GNRGLNotifyEvent& event);
	
};

#endif // GNRGLCAMERAMEDIATOR_H
