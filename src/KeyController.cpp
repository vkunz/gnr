/**
 * KeyController
 * @name        KeyController.h
 * @date        2008-11-12
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <string>

#include "GLCamera.h"
#include "GLKeyEvent.h"
#include "KeyController.h"
#include "Scene.h"

/**
 * constructor of key controller
 */
KeyController::KeyController()
{
	m_Scene  = Scene::getInstance();
	m_Camera = NULL;
}

/**
 * destructor or key controller
 */
KeyController::~KeyController()
{
}

/**
 * react on gl key event and choose right camera to modify
 * @param[in]   event       GLKeyEvent
 */
void KeyController::KeyPressed(GLKeyEvent& event)
{
	if (event.getCanvasID() == CANVAS2D)
	{
		//set actual camera
		m_Camera = m_Scene->getGLCamera2D();

		//get cam height for more speed
		float cam_height = m_Camera->getPosition().getY();

		//set fix direction values
		m_fx = 0.0;
		m_fz = -cam_height*0.07368;
		m_rx = cam_height*0.07368;
		m_rz = 0.0;
	}
	else
	{
		//set actual camera
		m_Camera = m_Scene->getGLCamera3D();

		//get cam height for more speed
		float cam_height = m_Camera->getPosition().getY();

		//get specific direction values
		m_fx = 0.1368*cam_height*m_Camera->getViewDir().getX();
		m_fz = 0.1368*cam_height*m_Camera->getViewDir().getZ();
		m_rx = 0.1368*cam_height*m_Camera->getRightVector().getX();
		m_rz = 0.1368*cam_height*m_Camera->getRightVector().getZ();
	}

	if (m_Camera != NULL)
	{
		//move cam
		MoveCamera(event);
	}
}

/**
 * move choosen camera right and front
 * @param[in]   event       GLKeyEvent
 */
void KeyController::MoveCamera(GLKeyEvent& event)
{
	//catch mouse event and move cam
	switch (event.getKey())
	{
	case 'W':
	case 'w':
		m_Camera->move(m_fx,0.0,m_fz);
		break;
	case 'S':
	case 's':
		m_Camera->move(-m_fx,0.0,-m_fz);
		break;
	case 'D':
	case 'd':
		m_Camera->move(m_rx,0.0,m_rz);
		break;
	case 'A':
	case 'a':
		m_Camera->move(-m_rx,0.0,-m_rz);
		break;
	}

	//refresh canvas
	m_Scene->glRefresh();
}
