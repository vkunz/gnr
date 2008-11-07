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
	void OnRMouseUp(wxMouseEvent& WXUNUSED(event));
	void OnLMouseDown(wxMouseEvent& event);
	void OnLMouseUp(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	void OnLeaveWindow(wxMouseEvent& event);
	void OnEnterWindow(wxMouseEvent& event);
	void OnKeyDown(wxKeyEvent& WXUNUSED(event));
	void OnResize(wxSizeEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnLMouseDblClick(wxMouseEvent& event);
	DECLARE_EVENT_TABLE()
	
protected:
	int m_window_x, m_window_y;
	static GLuint m_floor_DL;
	unsigned int FloorTexture;
	
	GLfloat light_ambient[4];
	GLfloat light_diffuse[4];
	GLfloat light_specular[4];
	GLfloat light_position[4];
	GLfloat shadow_color[4];
	GLfloat floor_shadow[4][4];
	GLfloat floor_plane[4];
	
	void initGL();
	void connectEvents();
	void disconnectEvents();
	void reconnectEvents();
	void reshape();
	void loadFloorTexture();
	void setMatrix();
	void getGLPos(int x, int y, GNRVertex* glcoords);
	void getGLDim(int x, int y, GNRVertex* glcoords);
	
	//shadow specific function for shadow projection
	void SetShadowMatrix(float shadowMat[4][4], float groundplane[4], float lightpos[4]);
	
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
	void initLights();
	
	void prepareDraw();
	void endDraw();
	
	void loadShadowMatrix();
	void shadowColorOn();
	void shadowColorOff();
	void preparePixelBuffer();
	void endPixelBuffer();
	
	GNRAssembly* selection(GNRAssembly* rootAssembly, GNRGLCamera* camera, int mouse_x, int mouse_y);
	void drawBaseFloor(float fCenterX, float fCenterY, float fCenterZ, int fSize);
	void setActive();
};

#endif // _GNRGLCANVAS_H_
