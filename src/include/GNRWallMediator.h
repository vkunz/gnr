#ifndef _GNRWALL_H_
#define _GNRWALL_H_

#include "GNRMediator.h"
#include "GNRGLNotifyEvent.h"
#include "GNRAssembly.h"
#include "GNRGLCamera.h"
#include "GNRVertex.h"

class GNRWallMediator: public GNRMediator, wxEvtHandler
{
public:
	GNRWallMediator();
	virtual ~GNRWallMediator();
	void initialize(GNRGLNotifyEvent& event);
	int  translate(GNRGLNotifyEvent& event);
	void setAssembly(GNRAssembly* assembly);
	void setGLCamera(GNRGLCamera* camera) {};
	void finalize();
protected:
private:
	GNRVertex startPoint;
	GNRVertex endPoint;
	GNRAssembly* m_assembly;
	
	float gl_xmax;
	float gl_xmin;
	float gl_zmax;
	float gl_zmin;
	int window_w;
	int window_h;
	int m_mouse_x;
	int m_mouse_y;
	
	void calculate();
};

#endif // _GNRWALL_H_
