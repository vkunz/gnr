/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * defines the gl2dcanvas class
 * @name        GNRGL3DCanvas.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGL2DCANVAS_H_
#define _GNRGL2DCANVAS_H_

#include "GNRGLCanvas.h"

class GNRGL2DCanvas : public GNRGLCanvas
{
private:
	float m_camera_hight;
	
	void initGL();
	void reshape();
	void setCamera();
	void setPerspective();
	
	void OnMouseWheel(wxMouseEvent& event);
	void OnResize(wxSizeEvent& event);
	
public:
	GNRGL2DCanvas(wxWindow* parent,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = wxT("GNRGL2DCanvas"));
	GNRGL2DCanvas(wxWindow* parent,
	              wxGLContext* sharedContext,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = _("GNRGL2DCanvas"));
	              
	~GNRGL2DCanvas() {}
	
	
};

#endif // _GNRGL2DCANVAS_H_
