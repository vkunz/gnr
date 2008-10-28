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
#include "GNREnum.h"
#include "GNRGLCamera.h"

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
	void OnMouseWheel(wxMouseEvent& event);
	void OnLeaveWindow(wxMouseEvent& event);
	void OnEnterWindow(wxMouseEvent& event);
	void OnResize(wxSizeEvent& event);
	void OnPaint(wxPaintEvent& event);
	
protected:
	int m_window_x, m_window_y;
	unsigned int FloorTexture;
	
	void initGL();
	void connectEvents();
	void reshape();
	void loadFloorTexture();
	void getGLPos(int x, int y, GNRVertex* glcoords);
	void getGLDim(int x, int y, GNRVertex* glcoords);
	
	virtual void setPerspective() = 0;
	virtual canvasType getCanvasID() = 0;
	
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
	void initLights();
	void draw();
	void endDraw();
	int selection(GNRAssembly* rootAssembly, GNRGLCamera* camera, int mouse_x, int mouse_y);
	void drawBaseFloor(float fCenterX, float fCenterY, float fCenterZ, int fSize);
};

#endif // _GNRGLCANVAS_H_
