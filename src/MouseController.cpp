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

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of mousecontroller sets scene to modify and
 * initializes the two mediators
 * @param       Scene      pointer to actual scene

 */
MouseController::MouseController(Scene* scene)
{
	m_Scene = scene;
	m_AssemblyMediator2D = new AssemblyMediator2D();
	m_AssemblyMediator3D = new AssemblyMediator3D();
	m_GLCameraMediator2D = new GLCameraMediator2D();
	m_GLCameraMediator3D = new GLCameraMediator3D();
	m_WallMediator       = new WallMediator();
	m_Mediator = m_AssemblyMediator3D;
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
 * @param       GLNotifyEvent      command event from canvas

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
		if (m_Mediator->getTranslation() == DRAWWALL)
		{
			//draw only walls in 2d canvas
			if (event.getCanvasID() == CANVAS2D)
			{
				m_Mediator = m_WallMediator;
			}
			//in 3d canvas move as expected
			else if (event.getCanvasID() == CANVAS3D)
			{
				m_Mediator = m_AssemblyMediator3D;
				event.setCamRotatedX(m_Scene->getGLCamera3D()->getRotatedX());
				event.setCamRotatedY(m_Scene->getGLCamera3D()->getRotatedY());
				event.setCamPosition(m_Scene->getGLCamera3D()->getPosition());
				setAssemblyMediator(event);
			}
		}
		//otherwise move object normally
		else
		{
			event.setCamRotatedX(m_Scene->getGLCamera3D()->getRotatedX());
			event.setCamRotatedY(m_Scene->getGLCamera3D()->getRotatedY());
			event.setCamPosition(m_Scene->getGLCamera3D()->getPosition());
			m_Mediator = m_AssemblyMediator3D;
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
		//move or rotate cam in 3d mode
		else if (event.getCanvasID() == CANVAS3D)
		{
			//else, point to 3D mediator if event from canvas 3D
			m_Mediator = m_GLCameraMediator3D;
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
 * @param       GLNotifyEvent      command event from canvas

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
 * @param       GLNotifyEvent      command event from canvas

 */
void MouseController::deactivateMediator()
{
	m_Mediator->finalize();
}

/**
 * pass through the command event to the selected mediator
 * @param       NotifyEvent      command event from canvas

 */
void MouseController::setTranslation(NotifyEvent& event)
{
	m_Mediator->setTranslation((transType)event.GetInt());
}

/**
 * set snap to grid and angle values
 * @param       NotifyEvent      command event from canvas

 */
void MouseController::setSnapfunction(NotifyEvent& event)
{
	m_Mediator->setSnapfunction(event);
}

/**
 * update actual mouse position
 * @param       GLNotifyEvent      command event from canvas

 */
void MouseController::updateMouse(GLNotifyEvent& event)
{
	mouse_x = event.getMouseEvent().GetX();
	mouse_y = event.getMouseEvent().GetY();
}

void MouseController::setAssemblyMediator(GLNotifyEvent& event)
{
	Assembly* selectedAssembly = NULL;
	
	if (event.getCanvasID() == CANVAS2D)
	{
		//point to 2D mediator if event from canvas 2D
		m_Mediator = m_AssemblyMediator2D;
		//check for assembly id from click
		selectedAssembly = (m_Scene->getCanvas2D())->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera2D(), mouse_x, mouse_y);
	}
	else if (event.getCanvasID() == CANVAS3D)
	{
		//else, point to 3D mediator if event from canvas 3D
		m_Mediator = m_AssemblyMediator3D;
		//check for assembly id from click
		selectedAssembly = (m_Scene->getCanvas3D())->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera3D(), mouse_x, mouse_y);
	}
	
	if (selectedAssembly != NULL)
	{
		//set assembly mediator target to selected object
		m_Mediator->setAssembly(selectedAssembly);
	}
	else
	{
		m_Mediator->setAssembly(NULL);
	}
}

void MouseController::setSelected(GLNotifyEvent& event)
{
	Assembly* selectedAssembly = NULL;
	
	if (event.getCanvasID() == CANVAS2D)
	{
		selectedAssembly = (m_Scene->getCanvas2D())->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera2D(), mouse_x, mouse_y);
	}
	else if (event.getCanvasID() == CANVAS3D)
	{
		selectedAssembly = (m_Scene->getCanvas3D())->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera3D(), mouse_x, mouse_y);
	}
	
	if (selectedAssembly != NULL)
	{
		//select assembly (move to IS_SELECTED group)
		m_Scene->selectAssembly(selectedAssembly);
	}
}
