/**
 * defines the gl2dcanvas class
 * @name        GNRGLCanvas2D.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGL2DCANVAS_H_
#define _GNRGL2DCANVAS_H_

#include "GNRGLCanvas.h"

class GNRGLCanvas2D : public GNRGLCanvas
{
private:

	void setPerspective();
	canvasType getCanvasID();
	
public:
	GNRGLCanvas2D(wxWindow* parent,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = wxT("GNRGLCanvas2D"));
	GNRGLCanvas2D(wxWindow* parent,
	              wxGLContext* sharedContext,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = _("GNRGLCanvas2D"));
	              
	~GNRGLCanvas2D() {}
	
	
};

#endif // _GNRGL2DCANVAS_H_
