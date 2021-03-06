/**
 * AssemblyMediator2D
 * @note        [DONE]
 * @name        AssemblyMediator2D.cpp
 * @date        2008-10-09
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "Assembly.h"
#include "AssemblyMediator2D.h"
#include "GLNotifyEvent.h"

/**
 * move the object in XY dimension and limit height over ground
 * @param[in]           event           event from GLNotify
 */
void AssemblyMediator2D::MoveXY(GLNotifyEvent& event)
{
	float new_x = old_x - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	float new_y = old_y - (gl_xmax-gl_xmin)/window_w*2.0f*(event.getMouseEvent().GetY() - m_mouse_y);

	doSnapMove(new_x);
	doSnapMove(new_y);

	if (new_y <= (m_Assembly->getOverGround()*1.1))
	{
		new_y = m_Assembly->getOverGround();
	}

	m_Assembly->position().setX(new_x);
	m_Assembly->position().setY(new_y);
}

/**
 * move the object in XZ dimension
 * @param[in]           event           event from GLNotify
 */
void AssemblyMediator2D::MoveXZ(GLNotifyEvent& event)
{
	float new_x = old_x - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	float new_z = old_z - (gl_xmax-gl_xmin)/window_w*(m_mouse_y - event.getMouseEvent().GetY());

	doSnapMove(new_x);
	doSnapMove(new_z);

	m_Assembly->position().setXZ(new_x, new_z);
}

/**
 * rotate the object in XY dimension
 * @param[in]           event           event from GLNotify
 */
void AssemblyMediator2D::RotateXY(GLNotifyEvent& event)
{
	float new_phi   = phi_old + 720.0f*(event.getMouseEvent().GetY() - m_mouse_y)/window_h;
	float new_theta = theta_old + 720.0f*(event.getMouseEvent().GetX() - m_mouse_x)/window_w;

	doSnapRotate(new_phi);
	doSnapRotate(new_theta);

	m_Assembly->rotation().setXY(new_phi, new_theta);
}

/**
 * rotate the object in Y dimension
 * @param[in]           event           event from GLNotify
 */
void AssemblyMediator2D::RotateY(GLNotifyEvent& event)
{
	float new_theta = theta_old + 720.0f*(event.getMouseEvent().GetX() - m_mouse_x)/window_w;
	doSnapRotate(new_theta);
	m_Assembly->rotation().setY(new_theta);
}

/**
 * rotate the object in XZ dimension
 * @param[in]           event           event from GLNotify
 */
void AssemblyMediator2D::RotateXZ(GLNotifyEvent& event)
{
	float new_phi = phi_old + 720.0f*(event.getMouseEvent().GetY() - m_mouse_y)/window_h;
	float new_rho = rho_old + 720.0f*(m_mouse_x - event.getMouseEvent().GetX())/window_w;

	doSnapRotate(new_phi);
	doSnapRotate(new_rho);

	m_Assembly->rotation().setXZ(new_phi, new_rho);
}
