/**
 * defines the gl2dcanvas class
 * @name        GLCanvas2D.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GLCANVASPREVIEW_H
#define GLCANVASPREVIEW_H

#include "Enum.h"
#include "GLCanvas.h"
#include "Assembly.h"

class GLCanvasPreview : public wxGLCanvas
{
public:
	// ctor
	GLCanvasPreview(wxWindow* parent,
	                wxWindowID id = wxID_ANY,
	                const wxPoint& pos = wxDefaultPosition,
	                const wxSize& size = wxDefaultSize,
	                long style = 0,
	                const wxString& name = wxT("GLCanvasPreview"));
	                
	// dtor
	virtual ~GLCanvasPreview();
	
	void setAssembly(Assembly* assembly);
	void draw();
	void reshape();
	
protected:

private:

	float roty;
	float m_mouse_x;
	Assembly* m_assembly;
	
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

#endif // GLCANVASPREVIEW_H
