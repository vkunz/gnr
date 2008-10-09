#include "GNRMouse.h"
#include <wx/math.h>

#if defined(__WXDEBUG__)
#include <wx/log.h>
#endif

GNRMouse::GNRMouse()
{
	Init(1.0f, 1000.0f);
}

GNRMouse::GNRMouse(float m_znear, float m_zfar)
{
	Init(m_znear, m_zfar);
}

GNRMouse::~GNRMouse()
{
}

void GNRMouse::Init(float m_znear, float m_zfar)
{
	in_use = false;
	
	status = MOVEXZ;
	
	phix   = phix_old = 0.0f;
	phiy   = phiy_old = 0.0f;
	phiz   = angle    = 0.0f;
	
	zfar   = m_zfar;
	znear  = m_znear;
}

bool GNRMouse::GetControl(wxMouseEvent& event)
{
	if (in_use)
	{
		return false;
	}
	
//TODO
//    my_object = assembly;

	//store actual mouse coords on control
	m_mouse_x = event.m_x;
	m_mouse_y = event.m_y;
	
	in_use = true;
	return true;
}

bool GNRMouse::DropControl(wxMouseEvent& event)
{
//TODO
//    if ( in_use && my_object == assembly )
//    {
//        my_object = NULL;
//        in_use = false;
//    }
	in_use = false;
	return !in_use;
}

void GNRMouse::ObjectTransform(wxMouseEvent& event)
{
	switch (status)
	{
	case MOVEXZ:
		ObjectMoveXZ(event);
		break;
	case MOVEXY:
		ObjectMoveXY(event);
		break;
	case ROTATE:
		ObjectRotate(event);
		break;
	default:
		ObjectMoveXZ(event);
		break;
	}
}

void GNRMouse::ObjectRotate(wxMouseEvent& event)
{
	phiy  = phiy_old + 720.0*((float)(m_mouse_x - event.m_x)/(float)window_w);
	phix  = phix_old + 720.0*((float)(m_mouse_y - event.m_y)/(float)window_h);
}

void GNRMouse::ObjectMoveXY(wxMouseEvent& event)
{
	posx -= (float)(m_mouse_x - event.m_x)/300.0*fabs(posz);
	posy -= (float)(event.m_y - m_mouse_y)/300.0*fabs(posz);
}

void GNRMouse::ObjectMoveXZ(wxMouseEvent& event)
{
	posx -= (float)(m_mouse_x - event.m_x)/360.0*fabs(posz);
	posz -= (float)(m_mouse_y - event.m_y)/10.0;
}
