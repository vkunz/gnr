/**
 * GNRMouseController
 * @name        GNRMouseController.cpp
 * @date        2008-10-24
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRMouseController.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of mousecontroller sets scene to modify and
 * initializes the two mediators
 * @param       GNRScene      pointer to actual scene
 * @access      public
 */
GNRMouseController::GNRMouseController(GNRScene* scene)
{
	m_Scene = scene;
	m_AssemblyMediator2D = new GNRAssemblyMediator2D();
	m_AssemblyMediator3D = new GNRAssemblyMediator3D();
	m_GLCameraMediator2D = new GNRGLCameraMediator2D();
	m_GLCameraMediator3D = new GNRGLCameraMediator3D();
	m_Mediator = m_AssemblyMediator3D;
}

/**
 * destructor of mousecontroller kills his mediators
 * @access      public
 */
GNRMouseController::~GNRMouseController()
{
	delete m_AssemblyMediator3D;
	delete m_AssemblyMediator2D;
	delete m_GLCameraMediator3D;
	delete m_GLCameraMediator2D;
}

/**
 * prepare different mediators for translating mouse actions to
 * the camera and assemblies at once
 * @param       GNRGLNotifyEvent      command event from canvas
 * @access      public
 */
void GNRMouseController::setMediator(GNRGLNotifyEvent& event)
{
	//get mouse coords from event
	updateMouse(event);
	
	//connect the matching mediator
	switch ((buttonType)event.getMouseEvent().GetButton())
	{
	case LEFT_BUTTON:
		if (m_Mediator->getTranslation() == DRAWWALL)
		{
			/*	//TODO WALL MEDIATOR
				GNRAssemblyCuboid* cub = new GNRAssemblyCuboid();
				m_WallMediator->setAssemblyID((int)GNRAssemblyCuboid);
			
				m_Mediator = m_WallMediator;*/
		}
		else
		{
			setAssemblyMediator(event);
		}
		break;
	case MIDDLE_BUTTON:
		if (event.getCanvasID() == CANVAS2D)
		{
			//point to 2D mediator if event from canvas 2D
			m_Mediator = m_GLCameraMediator2D;
			m_Mediator->setGLCamera(m_Scene->getGLCamera2D());
		}
		else
		{
			//else, point to 3D mediator if event from canvas 3D
			m_Mediator = m_GLCameraMediator3D;
			m_Mediator->setGLCamera(m_Scene->getGLCamera3D());
		}
		break;
	case RIGHT_BUTTON:
		if (event.getCanvasID() == CANVAS2D)
		{
			//point to 2D mediator if event from canvas 2D
			m_Mediator = m_GLCameraMediator2D;
			m_Mediator->setGLCamera(m_Scene->getGLCamera2D());
		}
		else
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
		else
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
 * @param       GNRGLNotifyEvent      command event from canvas
 * @access      public
 */
void GNRMouseController::activateMediator(GNRGLNotifyEvent& event)
{
	if (m_Mediator->translate(event) == 0)
	{
		m_Scene->glRefresh();
	}
}

/**
 * tell mediator to stop translation and create command-object
 * @param       GNRGLNotifyEvent      command event from canvas
 * @access      public
 */
void GNRMouseController::deactivateMediator()
{
	m_Mediator->finalize();
}

/**
 * pass through the command event to the selected mediator
 * @param       GNRNotifyEvent      command event from canvas
 * @access      public
 */
void GNRMouseController::setTranslation(GNRNotifyEvent& event)
{
	m_Mediator->setTranslation((transType)event.GetInt());
}

/**
 * set snap to grid and angle values
 * @param       GNRNotifyEvent      command event from canvas
 * @access      public
 */
void GNRMouseController::setSnapfunction(GNRNotifyEvent& event)
{
	m_Mediator->setSnapfunction(event);
}

/**
 * update actual mouse position
 * @param       GNRGLNotifyEvent      command event from canvas
 * @access      protected
 */
void GNRMouseController::updateMouse(GNRGLNotifyEvent& event)
{
	mouse_x = event.getMouseEvent().GetX();
	mouse_y = event.getMouseEvent().GetY();
}

void GNRMouseController::setAssemblyMediator(GNRGLNotifyEvent& event)
{
	GNRAssembly* selectedAssembly = NULL;
	
	if (event.getCanvasID() == CANVAS2D)
	{
		//point to 2D mediator if event from canvas 2D
		m_Mediator = m_AssemblyMediator2D;
		//check for assembly id from click
		selectedAssembly = (m_Scene->getCanvas2D())->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera2D(), mouse_x, mouse_y);
	}
	else
	{
		//else, point to 3D mediator if event from canvas 3D
		m_Mediator = m_AssemblyMediator3D;
		//check for assembly id from click
		selectedAssembly = (m_Scene->getCanvas3D())->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera3D(), mouse_x, mouse_y);
	}
	
	//store selected assembly id in scene
	m_Scene->setAssembly(selectedAssembly);
	
	//select assembly (move to IS_SELECTED group)
	m_Scene->selectAssembly(selectedAssembly);
	
	//set assembly mediator target to selected object
	m_Mediator->setAssembly(selectedAssembly);
}
