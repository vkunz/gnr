/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * defines the glcanvas base class
 * @name        GNRGLCanvas.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGLCANVAS_H_
#define _GNRGLCANVAS_H_

#include <wx/glcanvas.h>

#include "GNRAssembly.h"
#include "GNRGLCamera.h"
#include "GNRNotifyEvent.h"

class GNRGLCanvas : public wxGLCanvas
{
private:
	void OnMMouseDown(wxMouseEvent& event);
	void OnMMouseUp(wxMouseEvent& event);
	void OnRMouseDown(wxMouseEvent& event);
	void OnRMouseUp(wxMouseEvent& event);
	void OnLMouseDblClick(wxMouseEvent& event);
	void OnLMouseDown(wxMouseEvent& event);
	void OnLMouseUp(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnLeaveWindow(wxMouseEvent& event);
	void OnEnterWindow(wxMouseEvent& event);
	void OnResize(wxSizeEvent& event);
	void OnPaint(wxPaintEvent& event);
	
protected:
	int m_window_x, m_window_y;
	
	void initGL();
	void connectEvents();
	void reshape();
	void initLights();
	GNRVertex getGLPos(int x, int y);
	GNRVertex* getGLDim(int x, int y);
	
	virtual void setCamera() = 0;
	virtual void setPerspective() = 0;
	virtual void OnMouseWheel(wxMouseEvent& event) = 0;
	virtual int getCanvasID() = 0;
	
public:
	// constructor
	GNRGLCanvas(wxWindow* parent,
	            wxWindowID id = wxID_ANY,
	            const wxPoint& pos = wxDefaultPosition,
	            const wxSize& size = wxDefaultSize,
	            long style = 0,
	            const wxString& name = wxT("GNRGLCanvas"));
	GNRGLCanvas(wxWindow* parent,
	            wxGLContext* sharedContext,
	            wxWindowID id = wxID_ANY,
	            const wxPoint& pos = wxDefaultPosition,
	            const wxSize& size = wxDefaultSize,
	            long style = 0,
	            const wxString& name = _("GNRGLCanvas"));
	            
	virtual ~GNRGLCanvas();
	
	// Drawing the GL-Scene
	void setMatrix();
	void prepareDraw();
	void draw();
	void endDraw();
	int selection(GNRAssembly* rootAssembly, GNRGLCamera* camera, int mouse_x, int mouse_y);
};

#endif // _GNRGLCANVAS_H_
