#include <gl/glu.h>

#include "GNRGLCanvas.h"

int const ID_TIMER = wxNewId();

GNRGLCanvas::GNRGLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
		: wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name)
{

	// Timer to refresh the GL-Window
	m_timer = new wxTimer(this, ID_TIMER);
	m_timer->Start(40);
	
	connectEvents();
	
}

GNRGLCanvas::GNRGLCanvas(wxWindow* parent, wxGLContext* sharedContext, wxWindowID id, const wxPoint& pos, const wxSize& size,
                         long style, const wxString& name) : wxGLCanvas(parent, sharedContext, id, pos, size, style, name)
{

	// Timer to refresh the GL-Window
	m_timer = new wxTimer(this, ID_TIMER);
	m_timer->Start(40);
	
	connectEvents();
}

void GNRGLCanvas::connectEvents()
{
	// Connect-methods to connect different Events with functions
	Connect(ID_TIMER, wxEVT_TIMER, (wxObjectEventFunction)&GNRGLCanvas::OnTimer);
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&GNRGLCanvas::OnResize);
}

void GNRGLCanvas::OnTimer(wxTimerEvent* event)
{
	prepareDraw();
	setCamera();
	draw();
	glFlush();
	SwapBuffers();
}

void GNRGLCanvas::prepareDraw()
{
	// set current GL-Context as activ
	SetCurrent();
	
	// Clear the Window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Reset The Current Modelview Matrix
	glLoadIdentity();
}

void GNRGLCanvas::draw()
{
	glTranslatef(2.0f, 1.5f, -6.0f);
	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,  0.0f,  0.0f);     /* Rot                           		*/
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der Front der Pyramide	*/
	glVertex3f(-1.0f, -1.0f,  1.0f);   /* linker Punkt der Front der Pyramide	*/
	glVertex3f(1.0f, -1.0f,  1.0f);    /* rechter Punkt der Fornt der Pyramide      */
	
	glColor3f(0.0f,  1.0f,  0.0f);     /* gruen                         		*/
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der rechten Seite der Pyramide  */
	glVertex3f(1.0f, -1.0f,  1.0f);    /* linker Punkt der rechten Seite der Pyramide  */
	glVertex3f(1.0f, -1.0f, -1.0f);    /* rechter Punkt der rechten Seite der Pyramide */
	
	glColor3f(0.0f,  0.0f,  1.0f);     /* blau		                           */
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der Rueckseite der Pyramide	*/
	glVertex3f(1.0f, -1.0f, -1.0f);    /* linker Punkt der Rueckseite der Pyramide  */
	glVertex3f(-1.0f, -1.0f, -1.0f);   /* rechter Punkt der Rueckseite der Pyaramide*/
	
	glColor3f(1.0f,  1.0f,  0.0f);     /* Gelb                           		 */
	glVertex3f(0.0f,  1.0f,  0.0f);    /* oberer Punkt der linken Seite der Pyramide */
	glVertex3f(-1.0f, -1.0f, -1.0f);   /* linker Punkt der linken Seite der Pyramide */
	glVertex3f(-1.0f, -1.0f,  1.0f);   /* rechter Punkt der linken Seite der Pyramide*/
	glEnd();
}

GNRGLCanvas::~GNRGLCanvas() {}
