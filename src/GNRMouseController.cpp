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

/**
 * constructor of mousecontroller sets scene to modify and
 * initializes the two mediators
 * @access      public
 */
GNRMouseController::GNRMouseController(GNRScene* scene)
{
	m_Scene = scene;
	m_AssemblyMediator = new GNRAssemblyMediator();
	m_GLCameraMediator = new GNRGLCameraMediator();
}

/**
 * destructor of mousecontroller kills his mediators
 * @access      public
 */
GNRMouseController::~GNRMouseController()
{
	delete m_AssemblyMediator;
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
	//connect the matching mediator
	switch ((buttonType)event.getMouseEvent().GetButton())
	{
	case LEFT_BUTTON:
		m_Mediator = m_AssemblyMediator;
		
		m_Scene->setAssemblyID(event.getSelectedObj());
		m_Mediator->setAssemblyID(event.getSelectedObj());
		break;
	case MIDDLE_BUTTON:
		m_Mediator = m_GLCameraMediator;
		m_Mediator->setGLCamera(m_Scene->getGLCamera());
		break;
	case RIGHT_BUTTON:
		//maybe for later functions
		break;
	}
	
	//set mode of mediator
	m_Mediator->setMode(event.getCanvasID());
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
