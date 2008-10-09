#ifndef _GNRMOUSE_H_
#define _GNRMOUSE_H_

#include <wx/dcclient.h>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/timer.h>

#include "GNRAssembly.h"

class GNRMouse
{
private:

	//action to do
	enum { MOVEXZ = 0, MOVEXY, ROTATE };
	int status;
	
	//remember if in use or not
	bool in_use;
	
	//old mouse coords on initialized dragging
	int	m_mouse_x, m_mouse_y;
	
	//window dimensions of actual frame
	int window_w, window_h;
	
	//saved positions in 3d canvas frame (later stored in assembly)
	float posx, posy, posz;
	float phix, phiy, phiz, angle;
	float phix_old, phiy_old;
	
	//pointer to assembly
	GNRAssembly* my_object;
	
protected:

	//action for rotating asembly
	void ObjectRotate(wxMouseEvent& event);
	
	//action for moving asembly in XY
	void ObjectMoveXY(wxMouseEvent& event);
	
	//action for moving asembly in XZ (default)
	void ObjectMoveXZ(wxMouseEvent& event);
	
	//init method
	void Init();
	
public:

	bool IsInUse()
	{
		return in_use;
	};
	
	//fetching control of mouse by event
	bool GetControl(wxMouseEvent& event);
	bool DropControl(wxMouseEvent& event);
	void ObjectTransform(wxMouseEvent& event);
	
	//ctor
	GNRMouse();
	GNRMouse(float m_zfar, float m_znear);
	
	//dtor
	virtual ~GNRMouse();
	
};

#endif // _GNRMOUSE_H_
