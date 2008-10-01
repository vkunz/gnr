#ifndef _ATHOS_TESTCANVAS_H_
#define _ATHOS_TESTCANVAS_H_

#include <wx/glcanvas.h>

#include <glm.h>

struct GLData
{
    bool initialized;           // have OpenGL been initialized?
    float beginx, beginy;       // position of mouse
    float quat[4];              // orientation of object
    float zoom;                 // field of view in degrees
};

class TestCanvas : public wxGLCanvas
{
private:
	GLData m_gldata;

	void InitGL();

protected:

public:
	TestCanvas(wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = 0,
        const wxString& name = wxT("TestGLCanvas"));

    GLMmodel* pmodel;
};


#endif // _ATHOS_TESTCANVAS_H_
