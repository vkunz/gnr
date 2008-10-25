/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRAssemblyMediator2D
 * @name        GNRAssemblyMediator2D.cpp
 * @date        2008-10-09
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssemblyMediator2D.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

void GNRAssemblyMediator2D::MoveXY(int m_x,int m_y)
{
	float new_x = old_x - (gl_xmax-gl_xmin)*(m_mouse_x - m_x)/window_w;
	float new_y = old_y - (gl_ymax-gl_ymin)*(m_y - m_mouse_y)/window_h*2.0;
	if (new_y < m_Assembly->getOverGround())
	{
		new_y = m_Assembly->getOverGround();
	}
	m_Assembly->setX(new_x);
	m_Assembly->setY(new_y);
}

void GNRAssemblyMediator2D::MoveXZ(int m_x,int m_y)
{
	float new_x = old_x - (gl_xmax-gl_xmin)*(m_mouse_x - m_x)/window_w;
	float new_z = old_z - (gl_xmax-gl_xmin)/window_w*(m_mouse_y - m_y);
	m_Assembly->setX(new_x);
	m_Assembly->setZ(new_z);
}

void GNRAssemblyMediator2D::RotateXY(int m_x,int m_y)
{
	m_Assembly->setPhi(phi_old + 720.0f*(m_mouse_y - m_y)/window_h);
	m_Assembly->setTheta(theta_old + 720.0f*(m_mouse_x - m_x)/window_w);
}

void GNRAssemblyMediator2D::RotateXZ(int m_x,int m_y)
{
	m_Assembly->setPhi(phi_old + 720.0f*(m_mouse_y - m_y)/window_h);
	m_Assembly->setRho(rho_old + 720.0f*(m_mouse_x - m_x)/window_w);
}
