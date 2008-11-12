/**
 * MouseController
 * @name        MouseController.cpp
 * @date        2008-10-24
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "MouseController.h"
#include "NotifyEvent.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of mousecontroller sets scene to modify and
 * initializes the two mediators
 * @param       scene      pointer to actual scene
 */
MouseController::MouseController(Scene* scene)
{
	m_Scene = scene;
	m_AssemblyMediator2D = new AssemblyMediator2D();
	m_AssemblyMediator3D = new AssemblyMediator3D();
	m_GLCameraMediator2D = new GLCameraMediator2D();
	m_GLCameraMediator3D = new GLCameraMediator3D();
	m_WallMediator       = new WallMediator();
	m_MeasureMediator    = new MeasureMediator();
	m_Mediator  = m_AssemblyMediator3D;
	m_act_trans = MOVEXZ;
}

/**
 * destructor of mousecontroller kills his mediators

 */
MouseController::~MouseController()
{
	delete m_AssemblyMediator3D;
	delete m_AssemblyMediator2D;
	delete m_GLCameraMediator3D;
	delete m_GLCameraMediator2D;
}

/**
 * prepare different mediators for translating mouse actions to
 * the camera and assemblies at once
 * @param       event       command event from canvas
 */
void MouseController::setMediator(GLNotifyEvent& event)
{
	//get mouse coords from event
	updateMouse(event);
	
	//connect the matching mediator
	switch ((buttonType)event.getMouseEvent().GetButton())
	{
	case LEFT_BUTTON:
		//if mode is drawing walls and left button pressed
		if (m_Mediator->getTranslation() == DRAWWALL || m_Mediator->getTranslation() == MEASURING)
		{
			//draw only walls in 2d canvas
			if (event.getCanvasID() == CANVAS2D)
			{
				if (m_Mediator->getTranslation() == DRAWWALL)
				{
					m_Mediator = m_WallMediator;
				}
				else
				{
					m_Mediator = m_MeasureMediator;
				}
			}
			//in 3d canvas move as expected
			else if (event.getCanvasID() == CANVAS3D)
			{
				m_Mediator = m_AssemblyMediator3D;
				event.setCamRotatedX(m_Scene->getGLCamera3D()->getRotatedX());
				event.setCamRotatedY(m_Scene->getGLCamera3D()->getRotatedY());
				event.setCamPosition(m_Scene->getGLCamera3D()->getPosition());
				setAssemblyMediator(event);
				
				//if in wall mode and moving in 3D switch to moveXZ
				NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
				myevent.setGNREventType(TOOLBARCHANGE);
				myevent.SetInt(MOVEXZ);
				ProcessEvent(myevent);
			}
		}
		//otherwise move object normally
		else
		{
			event.setCamRotatedX(m_Scene->getGLCamera3D()->getRotatedX());
			event.setCamRotatedY(m_Scene->getGLCamera3D()->getRotatedY());
			event.setCamPosition(m_Scene->getGLCamera3D()->getPosition());
			m_Mediator = m_AssemblyMediator3D;
			//set original movement from init
			m_Mediator->setTranslation(m_act_trans);
			setAssemblyMediator(event);
		}
		break;
	case MIDDLE_BUTTON:
		//move cam around in 2d canvas
		if (event.getCanvasID() == CANVAS2D)
		{
			//point to 2D mediator if event from canvas 2D
			m_Mediator = m_GLCameraMediator2D;
			m_Mediator->setGLCamera(m_Scene->getGLCamera2D());
		}
		//move or rotate cam in 3d mode (orbit cam)
		else if (event.getCanvasID() == CANVAS3D)
		{
			//else, point to 3D mediator if event from canvas 3D
			m_Mediator = m_GLCameraMediator3D;
			//set for orbit cam
			m_Mediator->setTranslation(ROTATEXY);
			m_Mediator->setGLCamera(m_Scene->getGLCamera3D());
		}
		break;
	case RIGHT_BUTTON:
		//move cam around in 2d canvas
		if (event.getCanvasID() == CANVAS2D)
		{
			//point to 2D mediator if event from canvas 2D
			m_Mediator = m_GLCameraMediator2D;
			m_Mediator->setGLCamera(m_Scene->getGLCamera2D());
		}
		//move or rotate cam in 3d mode
		else if (event.getCanvasID() == CANVAS3D)
		{
			//else, point to 3D mediator if event from canvas 3D
			m_Mediator = m_GLCameraMediator3D;
			//set original movement from init
			m_Mediator->setTranslation(m_act_trans);
			m_Mediator->setGLCamera(m_Scene->getGLCamera3D());
		}
		break;
	}
	
	if (event.getMouseEvent().GetWheelRotation())
	{
		if (event.getCanvasID() == CANVAS2D)
		{
			m_Mediator = m_GLCameraMediator2D;
			m_Mediator->setGLCamera(m_Scene->getGLCamera2D());
		}
		else if (event.getCanvasID() == CANVAS3D)
		{
			m_Mediator = m_GLCameraMediator3D;
			m_Mediator->setGLCamera(m_Scene->getGLCamera3D());
		}
	}
	
	//setup mediator starting position
	m_Mediator->initialize(event);
}

/**
 * pass through the command event to the selected mediator
 * @param       event      command event from canvas
 */
void MouseController::activateMediator(GLNotifyEvent& event)
{
	if (m_Mediator->translate(event) == 0)
	{
		m_Scene->glRefresh();
	}
}

/**
 * tell mediator to stop translation and create command-object
 */
void MouseController::deactivateMediator()
{
	m_Mediator->finalize();
}

/**
 * pass through the command event to the selected mediator
 * @param       event      command event from canvas
 */
void MouseController::setTranslation(NotifyEvent& event)
{
	//store actual translation
	m_act_trans = (transType)event.GetInt();
	//set translation to mediator
	m_Mediator->setTranslation(m_act_trans);
}

/**
 * set snap to grid and angle values
 * @param       event      command event from canvas
 */
void MouseController::setSnapfunction(NotifyEvent& event)
{
	m_Mediator->setSnapfunction(event);
}

/**
 * update actual mouse position
 * @param       event      command event from canvas
 */
void MouseController::updateMouse(GLNotifyEvent& event)
{
	mouse_x = event.getMouseEvent().GetX();
	mouse_y = event.getMouseEvent().GetY();
}

/**
 * set actual assembly mediator active
 * @param       event      command event from canvas
 */
void MouseController::setAssemblyMediator(GLNotifyEvent& event)
{
	m_Assembly = NULL;
	
	if (event.getCanvasID() == CANVAS2D)
	{
		//point to 2D mediator if event from canvas 2D
		m_Mediator = m_AssemblyMediator2D;
		//check for assembly id from click
		m_Assembly = (m_Scene->getCanvas2D())->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera2D(), mouse_x, mouse_y);
	}
	else if (event.getCanvasID() == CANVAS3D)
	{
		//else, point to 3D mediator if event from canvas 3D
		m_Mediator = m_AssemblyMediator3D;
		//check for assembly id from click
		m_Assembly = (m_Scene->getCanvas3D())->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera3D(), mouse_x, mouse_y);
	}
	
	//set assembly mediator target to selected object
	m_Mediator->setAssembly(m_Assembly);
}

/**
 * set actual assembly active
 * @param       event      command event from canvas
 */
void MouseController::setSelected(GLNotifyEvent& event)
{
	m_Assembly = NULL;
	
	if (event.getCanvasID() == CANVAS2D)
	{
		m_Assembly = (m_Scene->getCanvas2D())->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera2D(), mouse_x, mouse_y);
	}
	else if (event.getCanvasID() == CANVAS3D)
	{
		m_Assembly = (m_Scene->getCanvas3D())->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera3D(), mouse_x, mouse_y);
	}
	
	//select assembly (move to IS_SELECTED group)
	m_Scene->selectAssembly(m_Assembly);
}

/**
 * get actual hit assembly
 * @return       Assembly*          hit assembly
 */
Assembly* MouseController::getAssembly()
{
	return m_Assembly;
}
