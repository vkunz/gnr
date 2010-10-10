/**
 * This class is used to have a preview of an object
 * @note        [DONE]
 * @name        GLCanvasPreview.cpp
 * @date        2008-10-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <GL/glu.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "Assembly.h"
#include "GLCanvasPreview.h"
#include "GlobalDefine.h"

BEGIN_EVENT_TABLE(GLCanvasPreview, wxGLCanvas)
	EVT_LEFT_DOWN(GLCanvasPreview::OnLMouseDown)
	EVT_LEFT_UP(GLCanvasPreview::OnLMouseUp)
	EVT_SIZE(GLCanvasPreview::OnSize)
	EVT_PAINT(GLCanvasPreview::OnPaint)
	EVT_LEAVE_WINDOW(GLCanvasPreview::OnLeaveWindow)
END_EVENT_TABLE()

/**
 * constructor of GLCanvasPreview
 * @param[in]       parent          Parent-Window
 * @param[in]       id              Window-ID
 * @param[in]       pos             Window-Position of the Canvas
 * @param[in]       size            Window-Size of the Canvas
 * @param[in]       style           Window-Style
 * @param[in]       name            Window-Name
 */
GLCanvasPreview::GLCanvasPreview(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:wxGLCanvas(parent, id, pos, size, style, name)
{

	InitGL();
	roty = 0;
	m_assembly = NULL;
}

/**
 * destructor of GLCanvasPreview
 */
GLCanvasPreview::~GLCanvasPreview() {}

/**
 * init lights
 */
void GLCanvasPreview::InitLights()
{
	//define light source
	float light_ambient[4]  = {0.4,0.4,0.4,0.0};
	float light_diffuse[4]  = {0.5,0.5,0.5,0.0};
	float light_specular[4] = {0.1,0.1,0.1,0.0};
	float light_position[4] = {6.0,15.0,-20.0,1.0};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,0);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearColor(0.5, 0.5, 0.5, 1.0);
}

/**
 * does the main initialization of the canvas that has to be done on creation
 */
void GLCanvasPreview::InitGL()
{
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);

	glBlendFunc(GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA);

	glDisable(GL_STENCIL_TEST);
	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearDepth(1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_NORMALIZE);
}

/**
 * Handles the OnPaint-Event of the canvas
 * @param[in]       event       Paint-Event of the canvas
 */
void GLCanvasPreview::OnPaint(wxPaintEvent& event)
{
	draw();
	event.Skip();
}

/**
 * Handles the OnSize-Event of the canvas
 * to the new canvas size
 * @param[in]       WXUNUSED        unused Size-Event of the canvas
 */
void GLCanvasPreview::OnSize(wxSizeEvent& WXUNUSED(event))
{
	reshape();
}

/**
 * reshapes the glcanvas-viewport to new canvas size
 */
void GLCanvasPreview::reshape()
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
	gluPerspective(GLU_PERSPECTIVE, (float)w / (float)h, ZNEAR, ZFAR);

	// Load and Reset Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * sets the intern assembly variable to draw the assembly
 * @param[in]       assembly        Pointer to the assembly that has to be drawn
 */
void GLCanvasPreview::setAssembly(Assembly* assembly)
{
	m_assembly = assembly;
}

/**
 * draw the setted assembly
 */
void GLCanvasPreview::draw()
{
	if (m_assembly != NULL)
	{
		SetCurrent();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glShadeModel(GL_SMOOTH);
		glEnable(GL_BLEND);
		glDisable(GL_STENCIL_TEST);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);

		// scale image to fit in preview
		float max_size = m_assembly->getMaximumSize();

		gluLookAt(2.0,2.0,2.0,0.0,0.0,0.0,0.0,1.0,0.0);

		InitLights();

		// rotate as user determines
		glRotatef(roty, 0.0f, 1.0f, 0.0f);
		glScalef(1.0/max_size, 1.0/max_size, 1.0/max_size);

		glPushMatrix();
		{
			m_assembly->draw();
		}
		glPopMatrix();

		glFlush();
		SwapBuffers();
	}
}

/**
 * Handles the LeftMouseDown-Event of the canvas
 * @param[in]       event       Mouse-Event of the canvas
 */
void GLCanvasPreview::OnLMouseDown(wxMouseEvent& event)
{
	m_mouse_x = event.GetX();
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GLCanvasPreview::OnMouseMove);
}

/**
 * Handles the LeftMouseUp-Event of the canvas
 * @param[in]       WXUNUSED        unused Mouse-Event of the canvas
 */
void GLCanvasPreview::OnLeaveWindow(wxMouseEvent& WXUNUSED(event))
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GLCanvasPreview::OnMouseMove);
}

/**
 * Handles the LeftMouseUp-Event of the canvas
 * @param[in]       WXUNUSED        unused Mouse-Event of the canvas
 */
void GLCanvasPreview::OnLMouseUp(wxMouseEvent& WXUNUSED(event))
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GLCanvasPreview::OnMouseMove);
}

/**
 * Handles the Mouse-Move-Event of the canvas
 * @param[in]       event           Mouse-Event of the canvas
 */
void GLCanvasPreview::OnMouseMove(wxMouseEvent& event)
{
	roty += m_mouse_x - event.GetX();
	m_mouse_x = event.GetX();
	draw();
}
