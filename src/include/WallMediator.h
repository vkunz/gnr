/**
 * declares the WallMediator-class
 * @name        WallMediator.h
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRWALL_H_
#define _GNRWALL_H_

#include "Mediator.h"
#include "GLNotifyEvent.h"
#include "Assembly.h"
#include "GLCamera.h"
#include "Vertex.h"

class WallMediator: public Mediator, wxEvtHandler
{
public:
	WallMediator();
	virtual ~WallMediator();
	void initialize(GLNotifyEvent& event);
	int  translate(GLNotifyEvent& event);
	void setAssembly(Assembly* WXUNUSED(assembly)) {};
	void setGLCamera(GLCamera* WXUNUSED(camera)) {};
	void finalize();
protected:
private:
	Vertex startPoint;
	Vertex endPoint;
	
	bool moved;
	float gl_xmax;
	float gl_xmin;
	float gl_zmax;
	float gl_zmin;
	int window_w;
	int window_h;
	int m_mouse_x;
	int m_mouse_y;
};

#endif // _GNRWALL_H_
