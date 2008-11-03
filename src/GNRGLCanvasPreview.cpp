/**
 * This class is used to have a preview of an object
 * @name        GNRGLCanvasPreview.cpp
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

#include "GNRGLCanvasPreview.h"
#include "GNRGlobalDefine.h"

BEGIN_EVENT_TABLE(GNRGLCanvasPreview, wxGLCanvas)
	EVT_LEFT_DOWN(GNRGLCanvasPreview::OnLMouseDown)
	EVT_LEFT_UP(GNRGLCanvasPreview::OnLMouseUp)
	EVT_SIZE(GNRGLCanvasPreview::OnSize)
	EVT_PAINT(GNRGLCanvasPreview::OnPaint)
END_EVENT_TABLE()

/**
 * constructor of GNRGLCanvasPreview
 * @param       wxWindow*       Parent-Window
 * @param       wxWindowID      Window-ID
 * @param       wxPoint         Window-Position of the Canvas
 * @param       wxSize          Window-Size of the Canvas
 * @param       long            Window-Style
 * @param       wxString        Window-Name
 * @access      public
 */
GNRGLCanvasPreview::GNRGLCanvasPreview(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		:wxGLCanvas(parent, id, pos, size, style, name)
{

	InitGL();
	roty = 0;
	m_assembly = NULL;
}

/**
 * destructor of GNRGLCanvasPreview
 * @access      public
 */
GNRGLCanvasPreview::~GNRGLCanvasPreview()
{
}

/**
 * does the main initialization of the canvas that has to be done on creation
 * @access      private
 */
void GNRGLCanvasPreview::InitGL()
{
	//define light source
	float light_ambient[4]  = {0.3,0.3,0.3,0.0};
	float light_diffuse[4]  = {1.0,1.0,1.0,0.0};
	float light_specular[4] = {0.1,0.1,0.1,0.0};
	float light_position[4] = {30.0,60.0,20.0,1.0};
	float shadow_color[4]   = {0.3,0.3,0.3,0.7};
	float floor_plane[4]    = {0.0,1.0,0.0,0.0};
	
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	glClearDepth(1.0f);
	
	glEnable(GL_NORMALIZE);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glClearColor(0.3, 0.3, 0.3, 1.0);
}

/**
 * Handles the OnPaint-Event of the canvas
 * @param       wxPaintEvent       Paint-Event of the canvas
 * @access      private
 */
void GNRGLCanvasPreview::OnPaint(wxPaintEvent& event)
{
	draw();
	event.Skip();
}

/**
 * Handles the OnSize-Event of the canvas
 * to the new canvas size
 * @param       wxSizeEvent       Size-Event of the canvas
 * @access      private
 */
void GNRGLCanvasPreview::OnSize(wxSizeEvent& event)
{
	reshape();
}

/**
 * reshapes the glcanvas-viewport to new canvas size
 * @access      public
 */
void GNRGLCanvasPreview::reshape()
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
 * @param       GNRAssembly       Pointer to the assembly that has to be drawn
 * @access      public
 */
void GNRGLCanvasPreview::setAssembly(GNRAssembly* assembly)
{
	m_assembly = assembly;
}

/**
 * draw the setted assembly
 * @access      public
 */
void GNRGLCanvasPreview::draw()
{
	if (m_assembly != NULL)
	{
		SetCurrent();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		
		// scale image to fit in preview
		float max_size = m_assembly->getMaximumSize();
		glScalef(1/max_size, 1/max_size, 1/max_size);
		
		// rotate as user determines
		glRotatef(roty, 0.0f, 1.0f, 0.0f);
		
		glTranslatef(0.0f, 0.0f, -5.0f);
		
		glPushMatrix();
		{
			m_assembly->draw();
		}
		glPopMatrix();
		
		// Swap
		SwapBuffers();
	}
}

/**
 * Handles the LeftMouseDown-Event of the canvas
 * @param       wxMouseEvent       Mouse-Event of the canvas
 * @access      private
 */
void GNRGLCanvasPreview::OnLMouseDown(wxMouseEvent& event)
{
	m_mouse_x = event.GetX();
	Connect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvasPreview::OnMouseMove);
}

/**
 * Handles the LeftMouseUp-Event of the canvas
 * @param       wxMouseEvent       Mouse-Event of the canvas
 * @access      private
 */
void GNRGLCanvasPreview::OnLMouseUp(wxMouseEvent& event)
{
	Disconnect(wxEVT_MOTION, (wxObjectEventFunction)&GNRGLCanvasPreview::OnMouseMove);
}

/**
 * Handles the Mouse-Move-Event of the canvas
 * @param       wxMouseEvent       Mouse-Event of the canvas
 * @access      private
 */
void GNRGLCanvasPreview::OnMouseMove(wxMouseEvent& event)
{
	roty += m_mouse_x - event.GetX();
	m_mouse_x = event.GetX();
	draw();
}
