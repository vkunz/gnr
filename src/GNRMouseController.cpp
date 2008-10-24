/* vim: set expandtab sw=4 ts=4 sts=4: */
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
 * @access      public
 */
GNRMouseController::GNRMouseController(GNRScene* scene)
{
	m_Scene = scene;
	m_AssemblyMediator2D = new GNRAssemblyMediator2D();
	m_AssemblyMediator3D = new GNRAssemblyMediator3D();
	m_GLCameraMediator = new GNRGLCameraMediator();
}

/**
 * destructor of mousecontroller kills his mediators
 * @access      public
 */
GNRMouseController::~GNRMouseController()
{
	delete m_AssemblyMediator3D;
	delete m_AssemblyMediator2D;
	delete m_GLCameraMediator;
}

/**
 * prepare different mediators for translating mouse actions to
 * the camera and assemblies at once
 * @param       buttonType      button-id from mouse event
 * @param       canvasType      canvas-id from mouse event
 * @access      public
 */
void GNRMouseController::setMediator(GNRGLNotifyEvent& event)
{
	int selectedAssemblyID = 0, m_x, m_y;
	//get mouse coords from event
	m_x = event.getMouseEvent().m_x;
	m_y = event.getMouseEvent().m_y;
	
	//connect the matching mediator
	switch ((buttonType)event.getMouseEvent().GetButton())
	{
	case LEFT_BUTTON:
		if (event.getCanvasID() == CANVAS2D)
		{
			//point to 2D mediator if event from canvas 2D
			m_Mediator = m_AssemblyMediator2D;
			//check for assembly id from click
			GNRGL3DCanvas* canvas = (GNRGL3DCanvas*)event.GetInt();
			selectedAssemblyID = canvas->selection(m_Scene->getRootAssembly(), NULL, m_x, m_y);
		}
		else
		{
			//else, point to 3D mediator if event from canvas 3D
			m_Mediator = m_AssemblyMediator3D;
			//check for assembly id from click
			GNRGL2DCanvas* canvas = (GNRGL2DCanvas*)event.GetInt();
			selectedAssemblyID = canvas->selection(m_Scene->getRootAssembly(), m_Scene->getGLCamera() , m_x, m_y);
		}
		
		//store selected assembly id in scene
		m_Scene->setAssemblyID(selectedAssemblyID);
		
		//set assembly mediator target to selected object
		m_Mediator->setAssemblyID(selectedAssemblyID);
		
		//setup mediator starting position
		m_Mediator->initialize(event);
		
		break;
	case MIDDLE_BUTTON:
		m_Mediator = m_GLCameraMediator;
		m_Mediator->setGLCamera(m_Scene->getGLCamera());
		break;
	case RIGHT_BUTTON:
		//maybe for later functions
		break;
	}
}

/**
 * pass through the command event to the selected mediator
 * @param       GNRGLNotifyEvent      command event from canvas
 * @access      public
 */
void GNRMouseController::activateMediator(GNRGLNotifyEvent& event)
{
	m_Mediator->translate(event);
}

/**
 * pass through the command event to the selected mediator
 * @param       GNRGLNotifyEvent      command event from canvas
 * @access      public
 */
void GNRMouseController::setTranslation(GNRNotifyEvent& event)
{
	m_AssemblyMediator2D->setTranslation((transType)event.GetInt());
	m_AssemblyMediator3D->setTranslation((transType)event.GetInt());
}
