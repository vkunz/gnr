#include "GNRMouse.h"
#include <wx/math.h>

#if defined(__WXDEBUG__)
#include <wx/log.h>
#endif

GNRMouse::GNRMouse()
{
}

GNRMouse::~GNRMouse()
{
}

void GNRMouse::ObjectRotate(int m_x, int m_y)
{
	phiy  = phiy_old + 720.0*((float)(m_mouse_x - m_x)/(float)window_w);
	phix  = phix_old + 720.0*((float)(m_mouse_y - m_y)/(float)window_h);
}

void GNRMouse::ObjectMoveXY(int m_x, int m_y)
{
	posx -= (float)(m_mouse_x - m_x)/300.0*fabs(posz);
	posy -= (float)(m_y - m_mouse_y)/300.0*fabs(posz);
}

void GNRMouse::ObjectMoveXZ(int m_x, int m_y)
{
	posx -= (float)(m_mouse_x - m_x)/360.0*fabs(posz);
	posz -= (float)(m_mouse_y - m_y)/10.0;
}
