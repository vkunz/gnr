#include "TestCanvas.h"


TestCanvas::TestCanvas(wxWindow *parent, wxWindowID id,
const wxPoint& pos,
const wxSize& size, long style,
const wxString& name) : wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name)
{
    m_gldata.initialized = false;

	m_gldata.beginx = 0.0f;
    m_gldata.beginy = 0.0f;
    m_gldata.zoom   = 45.0f;


    this->InitGL();
}

void TestCanvas::InitGL()
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
