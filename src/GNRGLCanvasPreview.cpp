/**
 * defines the gl2dcanvas class
 * @name        GNRGLCanvas2D.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <GL/glu.h>

#include "GNRGLCanvasPreview.h"

#define ZNEAR 0.1f
#define ZFAR 200.0f
#define CAMH 2.0f

BEGIN_EVENT_TABLE(GNRGLCanvasPreview, wxGLCanvas)
	EVT_SIZE(GNRGLCanvasPreview::OnSize)
	EVT_PAINT(GNRGLCanvasPreview::OnPaint)
	EVT_ERASE_BACKGROUND(GNRGLCanvasPreview::OnEraseBackground)
	EVT_MOUSE_EVENTS(GNRGLCanvasPreview::OnMouse)
END_EVENT_TABLE()

// ctor
GNRGLCanvasPreview::GNRGLCanvasPreview(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:wxGLCanvas(parent, id, pos, size, style, name)
{
	initialized = false;
	
	// initialize view matrix
	beginx = 0.0f;
	beginy = 0.0f;
	zoom   = 45.0f;
}

// dtor
GNRGLCanvasPreview::~GNRGLCanvasPreview()
{
}

void GNRGLCanvasPreview::setPerspective()
{
	//gluPerspective(45.0f, (float)m_window_x / (float)m_window_y, ZNEAR, ZFAR);
}

canvasType GNRGLCanvasPreview::getCanvasID()
{
	return CANVASPREVIEW;
}

void GNRGLCanvasPreview::InitGL()
{
	static const GLfloat light0_pos[4]   = { -50.0f, 50.0f, 0.0f, 0.0f };
	
	// white light
	static const GLfloat light0_color[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
	
	static const GLfloat light1_pos[4]   = {  50.0f, 50.0f, 0.0f, 0.0f };
	
	// cold blue light
	static const GLfloat light1_color[4] = { 0.4f, 0.4f, 1.0f, 1.0f };
	
	/* remove back faces */
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	/* speedups */
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	
	/* light */
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_color);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_color);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

void GNRGLCanvasPreview::OnPaint(wxPaintEvent& event)
{
	// Initialize OpenGL
	if (!initialized)
	{
		InitGL();
		ResetProjectionMode();
		initialized = true;
	}
	
	// Clear
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Transformations
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -20.0f);
	GLfloat m[4][4];
	glMultMatrixf(&m[0][0]);
	
	// Flush
	glFlush();
	
	// Swap
	SwapBuffers();
}

void GNRGLCanvasPreview::OnSize(wxSizeEvent& event)
{

}

void GNRGLCanvasPreview::OnEraseBackground(wxEraseEvent& event)
{

}

void GNRGLCanvasPreview::OnMouse(wxMouseEvent& event)
{

}

void GNRGLCanvasPreview::ResetProjectionMode()
{
	int w, h;
	GetClientSize(&w, &h);
	{
		SetCurrent();
		glViewport(0, 0, (GLint) w, (GLint) h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)w/h, 1.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}
