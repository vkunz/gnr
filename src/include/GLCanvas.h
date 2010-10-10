/**
 * defines the glcanvas base class
 * @name        GLCanvas.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GLCANVAS_H_
#define _GLCANVAS_H_

#include <wx/glcanvas.h>

#include "Enum.h"

class Assembly;
class GLCamera;
class Vertex;

class GLCanvas : public wxGLCanvas
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
	void OnKeyDown(wxKeyEvent& event);
	void OnResize(wxSizeEvent& WXUNUSED(event));
	void OnPaint(wxPaintEvent& event);
	void OnLMouseDblClick(wxMouseEvent& event);
	DECLARE_EVENT_TABLE();

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
	void getGLPos(int x, int y, Vertex* glcoords);
	void getGLDim(int x, int y, Vertex* glcoords);

	//shadow specific function for shadow projection
	void SetShadowMatrix(float shadowMat[4][4], float groundplane[4], float lightpos[4]);

	virtual void setPerspective() = 0;
	virtual canvasType getCanvasID() = 0;

public:
	// constructor
	GLCanvas(wxWindow* parent,
	         wxWindowID id = wxID_ANY,
	         const wxPoint& pos = wxDefaultPosition,
	         const wxSize& size = wxDefaultSize,
	         long style = 0,
	         const wxString& name = wxT("GLCanvas"));
	GLCanvas(wxWindow* parent,
	         wxGLContext* sharedContext,
	         wxWindowID id = wxID_ANY,
	         const wxPoint& pos = wxDefaultPosition,
	         const wxSize& size = wxDefaultSize,
	         long style = 0,
	         const wxString& name = _("GLCanvas"));

	virtual ~GLCanvas();

	// Drawing the GL-Scene
	void initLights();

	void prepareDraw();
	void endDraw();

	void loadShadowMatrix();
	void shadowColorOn();
	void shadowColorOff();
	void preparePixelBuffer();
	void endPixelBuffer();

	Assembly* selection(Assembly* rootAssembly, GLCamera* camera, int mouse_x, int mouse_y);
	void drawBaseFloor(float fCenterX, float fCenterY, float fCenterZ, int fSize);
	void setActive();
};

#endif // _GLCANVAS_H_
