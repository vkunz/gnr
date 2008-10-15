/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * defines the gl3dcanvas class
 * @name        GNRGL3DCanvas.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGL3DCANVAS_H_
#define _GNRGL3DCANVAS_H_

#include "GNRGLCanvas.h"

class GNRGL3DCanvas : public GNRGLCanvas
{
private:
	void reshape();
	void setCamera();
	void setPerspective();
	
	void OnResize(wxSizeEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	
public:
	GNRGL3DCanvas(wxWindow* parent,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = wxT("GNRGL3DCanvas"));
	GNRGL3DCanvas(wxWindow* parent,
	              wxGLContext* sharedContext,
	              wxWindowID id = wxID_ANY,
	              const wxPoint& pos = wxDefaultPosition,
	              const wxSize& size = wxDefaultSize,
	              long style = 0,
	              const wxString& name = _("GNRGL3DCanvas"));
	              
	~GNRGL3DCanvas() {}
	
};

#endif // _GNRGL3DCANVAS_H_
