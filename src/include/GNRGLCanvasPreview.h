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
	
protected:

private:

	bool initialized;           // have OpenGL been initialized?
	float beginx, beginy;       // position of mouse
	float quat[4];              // orientation of object
	float zoom;                 // field of view in degrees
	
	void setPerspective();
	canvasType getCanvasID();
	
	void InitGL();
	void ResetProjectionMode();
	
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& event);
	void OnMouse(wxMouseEvent& event);
	
	DECLARE_EVENT_TABLE()
};

#endif // GNRGLCANVASPREVIEW_H
