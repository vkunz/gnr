#ifndef _GNRCONTROLLER_H_
#define _GNRCONTROLLER_H_

#include "GNRMain.h"
#include "GNRMouse.h"
#include "GNRGLMouseEvent.h"

class GNRController : public wxEvtHandler
{
private:
	GNRMouse* mouse;
	GNRFrame* mainFrame;
	void OnGLMouseEvent(GNRGLMouseEvent& event);
public:
	GNRController();
	
};

#endif // _GNRCONTROLLER_H_
