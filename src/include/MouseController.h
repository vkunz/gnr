/**
 * MouseController
 * @name        MouseController.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

#include "Assembly.h"
#include "AssemblyMediator2D.h"
#include "AssemblyMediator3D.h"
#include "GLCamera.h"
#include "GLCameraMediator2D.h"
#include "GLCameraMediator3D.h"
#include "GLNotifyEvent.h"
#include "Mediator.h"
#include "Scene.h"
#include "WallMediator.h"

class MouseController
{
private:

	//pointer to access the scene
	Scene* m_Scene;
	
	//pointer to objects for modification
	Assembly* m_Assembly;
	GLCamera* m_GLCamera;
	
	//mediators for specific objects
	Mediator* m_Mediator;
	AssemblyMediator2D* m_AssemblyMediator2D;
	AssemblyMediator3D* m_AssemblyMediator3D;
	GLCameraMediator2D* m_GLCameraMediator2D;
	GLCameraMediator3D* m_GLCameraMediator3D;
	WallMediator* m_WallMediator;
	
	int mouse_x;
	int mouse_y;
	
	void updateMouse(GLNotifyEvent& event);
	
protected:

public:
	MouseController(Scene* scene);
	virtual ~MouseController();
	
	void setTranslation(NotifyEvent& event);
	void setSnapfunction(NotifyEvent& event);
	void setSelected(GLNotifyEvent& event);
	void setMediator(GLNotifyEvent& event);
	void setAssemblyMediator(GLNotifyEvent& event);
	void activateMediator(GLNotifyEvent& event);
	void deactivateMediator();
};

#endif // MOUSECONTROLLER_H
