#ifndef GNRGLCAMERAMEDIATOR_H
#define GNRGLCAMERAMEDIATOR_H

#include "GNRMediator.h"

class GNRGLCameraMediator: public GNRMediator
{
public:
	GNRGLCameraMediator();
	void setMode(canvasType canvas_id);
	void translate(GNRGLNotifyEvent& event);
	virtual ~GNRGLCameraMediator();
protected:
private:
};

#endif // GNRGLCAMERAMEDIATOR_H
