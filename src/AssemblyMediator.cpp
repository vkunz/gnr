/**
 * AssemblyMediator
 * @note        [DONE]
 * @name        AssemblyMediator.cpp
 * @date        2008-10-09
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "AssemblyMediator.h"
#include "UndoRedo.h"
#include "CommandTransform.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of AssemblyMediator
 */
AssemblyMediator::AssemblyMediator()
{
	m_Assembly    = NULL;
	m_initialized = false;
};

/**
 * set active assembly which was hit by selection
 * @param[in]       assembly        hidden assembly
 */
void AssemblyMediator::setAssembly(Assembly* assembly)
{
	m_Assembly = assembly;
	m_initialized = false;
}

/**
 * global initialize of assembly mediator on mouse down
 * @param[in]       event           GLNotifyEvent-information
 */
void AssemblyMediator::initialize(GLNotifyEvent& event)
{
	if (m_Assembly != NULL)
	{
		m_initialized = true;
		
		old_x = m_Assembly->getX();
		old_y = m_Assembly->getY();
		old_z = m_Assembly->getZ();
		
		scale_x = m_Assembly->getScaleX();
		scale_y = m_Assembly->getScaleY();
		scale_z = m_Assembly->getScaleZ();
		
		phi_old   = m_Assembly->getPhi();
		theta_old = m_Assembly->getTheta();
		rho_old   = m_Assembly->getRho();
		
		window_w = event.getWinX();
		window_h = event.getWinY();
		
		gl_xmax = event.getWorldXmax();
		gl_xmin = event.getWorldXmin();
		
		gl_ymax = event.getWorldYmax();
		gl_ymin = event.getWorldYmin();
		
		gl_zmax = event.getWorldZmax();
		gl_zmin = event.getWorldZmin();
		
		cam_rot_x = event.getCamRotatedX();
		cam_rot_y = event.getCamRotatedY();
		cam_pos   = event.getCamPosition();
		obj_pos   = m_Assembly->getCenterVertex();
		
		m_mouse_x = event.getMouseEvent().GetX();
		m_mouse_y = event.getMouseEvent().GetY();
	}
}

/**
 * call specific translation function of 2D or 3D mediator
 * @param[in]       event           GLNotifyEvent-information
 * @return          int             status of translation
 */
int AssemblyMediator::translate(GLNotifyEvent& event)
{
	//if no active assembly, return
	if (m_initialized && m_Assembly != NULL)
	{
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
//			if (m_Assembly->isType(IS_GROUP))
//			{
//				//forbid rotate in x-axis
//				RotateY(event);
//				return 0;
//			}
			RotateXY(event);
			break;
		case ROTATEXZ:
//			if (m_Assembly->isType(IS_GROUP))
//			{
//				//forbid rotate in x and z-axis
//				RotateY(event);
//				return 0;
//			}
			RotateXZ(event);
			break;
		default:
			MoveXZ(event);
			break;
		}
		
		return 0;
	}
	
	return 1;
}

/**
 * gets called on mouse-up to finish the transformation;
 * in some cases undo-information is written
 */
void AssemblyMediator::finalize()
{
	//is active assembly, return
	if (m_initialized && m_Assembly != NULL && (int)m_Assembly != 0)
	{
		CommandTransform* command = new CommandTransform;
		command->setAssembly(m_Assembly);
		Vertex old_pos(old_x, old_y, old_z);
		command->setOldPosition(old_pos);
		Vertex old_angles(phi_old, theta_old, rho_old);
		command->setOldAngles(old_angles);
		Vertex new_pos(m_Assembly->getX(), m_Assembly->getY(), m_Assembly->getZ());
		command->setNewPosition(new_pos);
		Vertex new_angles(m_Assembly->getPhi(), m_Assembly->getTheta(), m_Assembly->getRho());
		command->setNewAngles(new_angles);
		
		UndoRedo* undo = UndoRedo::getInstance();
		undo->enqueue(command);
		
		m_Assembly = NULL;
	}
}
