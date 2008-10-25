/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * defines the gl2dcanvas class
 * @name        GNRGLCanvas3D.h
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
	float m_camera_height;
	
	void setCamera();
	void setPerspective();
	canvasType getCanvasID();
	
	void OnMouseWheel(wxMouseEvent& event);
	
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