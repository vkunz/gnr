/**
 * defines the gl3dcanvas class
 * @name        GNRGLCanvas3D.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGL3DCANVAS_H_
#define _GNRGL3DCANVAS_H_

#include "GNRGLCanvas.h"

class GNRGLCanvas3D : public GNRGLCanvas
{
private:

	void setPerspective();
	canvasType getCanvasID();
	
public:
	GNRGLCanvas3D(wxWindow* parent,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = wxT("GNRGLCanvas3D"));
	GNRGLCanvas3D(wxWindow* parent,
	              wxGLContext* sharedContext,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = _("GNRGLCanvas3D"));
	              
	~GNRGLCanvas3D() {}
	
};

#endif // _GNRGL3DCANVAS_H_
