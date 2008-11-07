/**
 * declares the GNRWallMediator-class
 * @name        GNRWallMediator.h
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
	void setAssembly(GNRAssembly* WXUNUSED(assembly)) {};
	void setGLCamera(GNRGLCamera* WXUNUSED(camera)) {};
	void finalize();
protected:
private:
	GNRVertex startPoint;
	GNRVertex endPoint;
	
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
