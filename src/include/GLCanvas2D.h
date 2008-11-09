/**
 * defines the gl2dcanvas class
 * @name        GLCanvas2D.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGL2DCANVAS_H_
#define _GNRGL2DCANVAS_H_

#include "GLCanvas.h"

class GLCanvas2D : public GLCanvas
{
private:

	void setPerspective();
	canvasType getCanvasID();
	
public:
	GLCanvas2D(wxWindow* parent,
	           wxWindowID id = wxID_ANY,
	           const wxPoint& pos = wxDefaultPosition,
	           const wxSize& size = wxDefaultSize,
	           long style = 0,
	           const wxString& name = wxT("GLCanvas2D"));
	GLCanvas2D(wxWindow* parent,
	           wxGLContext* sharedContext,
	           wxWindowID id = wxID_ANY,
	           const wxPoint& pos = wxDefaultPosition,
	           const wxSize& size = wxDefaultSize,
	           long style = 0,
	           const wxString& name = _("GLCanvas2D"));
	           
	~GLCanvas2D() {}
	
	
};

#endif // _GNRGL2DCANVAS_H_
