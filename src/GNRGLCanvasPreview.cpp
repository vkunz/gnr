/**
 * defines the glcanvaspreview class
 * @name        GNRGLCanvasPreview.h
 * @date        2008-10-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <GL/glu.h>

#include "GNRGLCanvasPreview.h"
#include "GNRGlobalDefine.h"

BEGIN_EVENT_TABLE(GNRGLCanvasPreview, wxGLCanvas)
	EVT_LEFT_DOWN(GNRGLCanvasPreview::OnLMouseDown)
	EVT_LEFT_UP(GNRGLCanvasPreview::OnLMouseUp)
	EVT_MOTION(GNRGLCanvasPreview::OnMouseMove)
	EVT_SIZE(GNRGLCanvasPreview::OnSize)
	EVT_PAINT(GNRGLCanvasPreview::OnPaint)
END_EVENT_TABLE()

// ctor
GNRGLCanvasPreview::GNRGLCanvasPreview(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:wxGLCanvas(parent, id, pos, size, style, name)
{

	InitGL();
	roty = 0;
	m_assembly = NULL;
}

// dtor
GNRGLCanvasPreview::~GNRGLCanvasPreview()
{
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
	
	glClearDepth(1.0f);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void GNRGLCanvasPreview::OnPaint(wxPaintEvent& event)
{
	draw();
}

void GNRGLCanvasPreview::OnSize(wxSizeEvent& event)
{
	// set current GL-Frame
	SetCurrent();
	
	// get size of current canvas
	int w, h;
	GetClientSize(&w, &h);
	
	// set viewport with resolution
	glViewport(0, 0, (GLint) w, (GLint) h);
	
	// Load and Reset Modelview
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, ZNEAR, ZFAR);
	
	// Load and Reset Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GNRGLCanvasPreview::setAssembly(GNRAssembly* assembly)
{
	m_assembly = assembly;
}

void GNRGLCanvasPreview::draw()
{
	if (m_assembly != NULL)
	{
		// Clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Transformations
		glLoadIdentity();
		
		// scale image to fit in preview
		float max_size = m_assembly->getMaximumSize();
		glScalef(1/max_size, 1/max_size, 1/max_size);
		
		// rotate as user determines
		glRotatef(roty, 0.0f, 1.0f, 0.0f);
		
		glTranslatef(0.0f, 0.0f, -5.0f);
		
		m_assembly->draw();
		
		// Flush
		glFlush();
		
		// Swap
		SwapBuffers();
	}
}

void GNRGLCanvasPreview::OnLMouseDown(wxMouseEvent& event)
{
	m_mouse_x = event.GetX();
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvasPreview::OnMouseMove);
}

void GNRGLCanvasPreview::OnLMouseUp(wxMouseEvent& event)
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvasPreview::OnMouseMove);
}

void GNRGLCanvasPreview::OnMouseMove(wxMouseEvent& event)
{
	roty += m_mouse_x - event.GetX();
	m_mouse_x = event.GetX();
	draw();
}
