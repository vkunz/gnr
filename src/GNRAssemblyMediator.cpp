/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRAssemblyMediator
 * @name        GNRAssemblyMediator.cpp
 * @date        2008-10-09
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssemblyMediator.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

void GNRAssemblyMediator::setAssemblyID(int assemblyID)
{
	m_Assembly = (GNRAssembly*)assemblyID;
}

void GNRAssemblyMediator::initialize(GNRGLNotifyEvent& event)
{
	if (m_Assembly != NULL)
	{
		old_x = m_Assembly->getX();
		old_y = m_Assembly->getY();
		old_z = m_Assembly->getZ();
		
		phi_old   = m_Assembly->getPhi();
		theta_old = m_Assembly->getTheta();
		rho_old   = m_Assembly->getRho();
		
		window_w = event.getWinX();
		window_h = event.getWinY();
		
		gl_xmax = event.getWorldXmax();
		gl_ymax = event.getWorldYmax();
		gl_xmin = event.getWorldXmin();
		gl_ymin = event.getWorldYmin();
		
		m_mouse_x = event.getMouseEvent().m_x;
		m_mouse_y = event.getMouseEvent().m_y;
	}
}

int GNRAssemblyMediator::translate(GNRGLNotifyEvent& event)
{
	//if no active assembly, return
	if (m_Assembly == NULL)
	{
		return -1;
	}
	
	//do specific translations
	switch (m_Translation)
	{
	case MOVEXZ:
		MoveXZ(event);
		break;
	case MOVEXY:
		MoveXY(event);
		break;
	case ROTATEXY:
		RotateXY(event);
		break;
	case ROTATEXZ:
		RotateXZ(event);
		break;
	default:
		MoveXZ(event);
		break;
	}
	
	return 0;
}
