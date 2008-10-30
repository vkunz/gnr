/**
 * GNRAssemblyMediator3D
 * @name        GNRAssemblyMediator3D.cpp
 * @date        2008-10-09
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssemblyMediator3D.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * move the object in XY dimension and limit height over ground
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      protected
 */
void GNRAssemblyMediator3D::MoveXY(GNRGLNotifyEvent& event)
{
	float new_x = old_x - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	float new_y = old_y - (gl_ymax-gl_ymin)*(event.getMouseEvent().GetY() - m_mouse_y)/window_h;
	
	if (new_y <= (m_Assembly->getOverGround()*1.1))
	{
		new_y = m_Assembly->getOverGround();
	}
	
	doSnapMove(new_x);
	doSnapMove(new_y);
	
	m_Assembly->setX(new_x);
	m_Assembly->setY(new_y);
}

/**
 * move the object in XZ dimension
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      private
 */
void GNRAssemblyMediator3D::MoveXZ(GNRGLNotifyEvent& event)
{
	float new_x = old_x - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	float new_z = old_z - (gl_ymax-gl_ymin)*(m_mouse_y - event.getMouseEvent().GetY())/window_h*2.0f;
	
	doSnapMove(new_x);
	doSnapMove(new_z);
	
	m_Assembly->setX(new_x);
	m_Assembly->setZ(new_z);
}

/**
 * rotate the object in XY dimension
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      private
 */
void GNRAssemblyMediator3D::RotateXY(GNRGLNotifyEvent& event)
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
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      private
 */
void GNRAssemblyMediator3D::RotateY(GNRGLNotifyEvent& event)
{
	float new_theta = theta_old + 720.0f*(event.getMouseEvent().GetX() - m_mouse_x)/window_w;
	doSnapRotate(new_theta);
	m_Assembly->setTheta(new_theta);
}

/**
 * rotate the object in XZ dimension
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      private
 */
void GNRAssemblyMediator3D::RotateXZ(GNRGLNotifyEvent& event)
{
	float new_phi = phi_old + 720.0f*(event.getMouseEvent().GetY() - m_mouse_y)/window_h;
	float new_rho = rho_old + 720.0f*(m_mouse_x - event.getMouseEvent().GetX())/window_w;
	
	doSnapRotate(new_phi);
	doSnapRotate(new_rho);
	
	m_Assembly->setPhi(new_phi);
	m_Assembly->setRho(new_rho);
}
