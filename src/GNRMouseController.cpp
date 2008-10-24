#include "GNRMouseController.h"

GNRMouseController::GNRMouseController(GNRScene* scene)
{
	m_Scene = scene;
	m_AssemblyMediator = new GNRAssemblyMediator();
	m_GLCameraMediator = new GNRGLCameraMediator();
}

GNRMouseController::~GNRMouseController()
{
	delete m_AssemblyMediator;
	delete m_GLCameraMediator;
}

void GNRMouseController::setMediator(buttonType mouse_button, canvasType canvas_id)
{
	switch (mouse_button)
	{
	case MIDDLE_BUTTON:
		m_Mediator = m_GLCameraMediator;
		break;
	case LEFT_BUTTON:
		m_Mediator = m_AssemblyMediator;
		break;
	case RIGHT_BUTTON:
		//nothing
		break;
	}
	
	m_Mediator->setMode(canvas_id);
}

void GNRMouseController::activateMediator(GNRGLNotifyEvent& event)
{
	m_Mediator->translate(event);
}
