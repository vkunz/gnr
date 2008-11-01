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
#include "GNRUndoRedo.h"
#include "GNRCommandAssembly.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * set active assembly which was hit by selection
 * @param       int         assemblyID int cast of pointer
 * @access      public
 */
void GNRAssemblyMediator::setAssembly(GNRAssembly* assembly)
{
	m_Assembly = assembly;
}

/**
 * global initialize of assembly mediator on mouse down
 * @param       GNRGLNotifyEvent         event information
 * @access      public
 */
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
		gl_xmin = event.getWorldXmin();
		
		gl_ymax = event.getWorldYmax();
		gl_ymin = event.getWorldYmin();
		
		m_mouse_x = event.getMouseEvent().GetX();
		m_mouse_y = event.getMouseEvent().GetY();
	}
}

/**
 * call specific translation function of 2D or 3D mediator
 * @param       GNRGLNotifyEvent     event information
 * @return      int                  status of translation
 * @access      public
 */
int GNRAssemblyMediator::translate(GNRGLNotifyEvent& event)
{
	//if no active assembly, return
	if (m_Assembly == NULL || (int)m_Assembly == 0)
	{
		return 1;
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
		if (m_Assembly->isType(IS_GROUP))
		{
			//forbid rotate in x-axis
			RotateY(event);
			return 0;
		}
		RotateXY(event);
		break;
	case ROTATEXZ:
		if (m_Assembly->isType(IS_GROUP))
		{
			//forbid rotate in x and z-axis
			RotateY(event);
			return 0;
		}
		RotateXZ(event);
		break;
	default:
		MoveXZ(event);
		break;
	}
	
	return 0;
}

void GNRAssemblyMediator::finalize()
{
	//is active assembly, return
	if (m_Assembly != NULL && (int)m_Assembly != 0)
	{
		GNRCommandAssembly* command = new GNRCommandAssembly;
		command->setAssembly(m_Assembly);
		GNRVertex old_pos(old_x, old_y, old_z);
		command->setOldPosition(old_pos);
		GNRVertex old_angles(phi_old, theta_old, rho_old);
		command->setOldAngles(old_angles);
		GNRVertex new_pos(m_Assembly->getX(), m_Assembly->getY(), m_Assembly->getZ());
		command->setNewPosition(new_pos);
		GNRVertex new_angles(m_Assembly->getPhi(), m_Assembly->getTheta(), m_Assembly->getRho());
		command->setNewAngles(new_angles);
		
		GNRUndoRedo* undo = GNRUndoRedo::getInstance();
		undo->enqueue(command);
		
		m_Assembly = NULL;
	}
}
