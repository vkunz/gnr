/**
 * defines the gl3dcanvas class
 * @name        GLCanvas3D.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GL3DCANVAS_H_
#define _GL3DCANVAS_H_

#include "GLCanvas.h"

class GLCanvas3D : public GLCanvas
{
private:

	void setPerspective();
	canvasType getCanvasID();

public:
	GLCanvas3D(wxWindow* parent,
	           wxWindowID id = wxID_ANY,
	           const wxPoint& pos = wxDefaultPosition,
	           const wxSize& size = wxDefaultSize,
	           long style = 0,
	           const wxString& name = wxT("GLCanvas3D"));
	GLCanvas3D(wxWindow* parent,
	           wxGLContext* sharedContext,
	           wxWindowID id = wxID_ANY,
	           const wxPoint& pos = wxDefaultPosition,
	           const wxSize& size = wxDefaultSize,
	           long style = 0,
	           const wxString& name = _("GLCanvas3D"));

	~GLCanvas3D() {}

};

#endif // _GL3DCANVAS_H_
