/**
 * defines the gl2dcanvas class
 * @name        GNRGLCanvas2D.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRGLCANVASPREVIEW_H
#define GNRGLCANVASPREVIEW_H

#include "GNREnum.h"
#include "GNRGLCanvas.h"
#include "GNRAssembly.h"

class GNRGLCanvasPreview : public wxGLCanvas
{
public:
	// ctor
	GNRGLCanvasPreview(wxWindow* parent,
	                   wxWindowID id = wxID_ANY,
	                   const wxPoint& pos = wxDefaultPosition,
	                   const wxSize& size = wxDefaultSize,
	                   long style = 0,
	                   const wxString& name = wxT("GNRGLCanvasPreview"));
	                   
	// dtor
	virtual ~GNRGLCanvasPreview();
	
	void setAssembly(GNRAssembly* assembly);
	void draw();
	void reshape();
	
protected:

private:

	float roty;
	float m_mouse_x;
	GNRAssembly* m_assembly;
	
	void InitGL();
	void InitLights();
	
	void OnLMouseDown(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnLMouseUp(wxMouseEvent& WXUNUSED(event));
	void OnSize(wxSizeEvent& WXUNUSED(event));
	void OnLeaveWindow(wxMouseEvent& WXUNUSED(event));
	
	DECLARE_EVENT_TABLE()
};

#endif // GNRGLCANVASPREVIEW_H
