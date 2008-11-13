/**
 * AssemblyMediator3D
 * @note        [DONE]
 * @name        AssemblyMediator3D.cpp
 * @date        2008-10-09
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "AssemblyMediator3D.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * move the object in XY dimension and limit height over ground
 * @param[in]           event           event from GLNotify
 */
void AssemblyMediator3D::MoveXY(GLNotifyEvent& event)
{
	Vertex to_obj = cam_pos - obj_pos;
	
	float mouse_dx = to_obj.length()*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	float mouse_dy = to_obj.length()*(m_mouse_y - event.getMouseEvent().GetY())/window_h;
	
	Vertex direction(mouse_dx,mouse_dy,0.0);
	direction.rotate(0.0,cam_rot_y,0.0);
	
	float new_x = old_x - direction.getX();
	float new_y = old_y + direction.getY();
	
	doSnapMove(new_x);
	doSnapMove(new_y);
	
	if (new_y <= (m_Assembly->getOverGround()*1.1))
	{
		new_y = m_Assembly->getOverGround();
	}
	
	m_Assembly->setX(new_x);
	m_Assembly->setY(new_y);
	
	obj_pos.setX(new_x);
	obj_pos.setY(new_y);
}

/**
 * move the object in XZ dimension
 * @param[in]           event           event from GLNotify
 */
void AssemblyMediator3D::MoveXZ(GLNotifyEvent& event)
{
	Vertex to_obj = cam_pos - obj_pos;
	
	float mouse_dx = to_obj.length()*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	float mouse_dy = to_obj.length()*(m_mouse_y - event.getMouseEvent().GetY())/window_h*1.1;
	
	Vertex direction(mouse_dx,0.0,mouse_dy);
	direction.rotate(0.0,cam_rot_y,0.0);
	
	float new_x = old_x - direction.getX();
	float new_z = old_z - direction.getZ();
	
	doSnapMove(new_x);
	doSnapMove(new_z);
	
	m_Assembly->setX(new_x);
	m_Assembly->setZ(new_z);
	
	obj_pos.setX(new_x);
	obj_pos.setZ(new_z);
}

/**
 * rotate the object in XY dimension
 * @param[in]           event           event from GLNotify
 */
void AssemblyMediator3D::RotateXY(GLNotifyEvent& event)
{
	float new_phi   = phi_old + 720.0f*(event.getMouseEvent().GetY() - m_mouse_y)/window_h;
	float new_theta = theta_old + 720.0f*(event.getMouseEvent().GetX() - m_mouse_x)/window_w;
	
	doSnapRotate(new_phi);
	doSnapRotate(new_theta);
	
	m_Assembly->setPhi(new_phi);
	m_Assembly->setTheta(new_theta);
}

/**
 * rotate the object in Y dimension
 * @param[in]           event           event from GLNotify
 */
void AssemblyMediator3D::RotateY(GLNotifyEvent& event)
{
	float new_theta = theta_old + 720.0f*(event.getMouseEvent().GetX() - m_mouse_x)/window_w;
	doSnapRotate(new_theta);
	m_Assembly->setTheta(new_theta);
}

/**
 * rotate the object in XZ dimension
 * @param[in]           event           event from GLNotify
 */
void AssemblyMediator3D::RotateXZ(GLNotifyEvent& event)
{
	float new_phi = phi_old + 720.0f*(event.getMouseEvent().GetY() - m_mouse_y)/window_h;
	float new_rho = rho_old + 720.0f*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	
	doSnapRotate(new_phi);
	doSnapRotate(new_rho);
	
	m_Assembly->setPhi(new_phi);
	m_Assembly->setRho(new_rho);
}
