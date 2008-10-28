/**
 * GNRMouseController
 * @name        GNRMouseController.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRMOUSECONTROLLER_H
#define GNRMOUSECONTROLLER_H

#include "GNRAssembly.h"
#include "GNRAssemblyMediator2D.h"
#include "GNRAssemblyMediator3D.h"
#include "GNRGLCamera.h"
#include "GNRGLCameraMediator2D.h"
#include "GNRGLCameraMediator3D.h"
#include "GNRGLNotifyEvent.h"
#include "GNRMediator.h"
#include "GNRScene.h"

class GNRMouseController
{
private:

	//pointer to access the scene
	GNRScene* m_Scene;
	
	//pointer to objects for modification
	GNRAssembly* m_Assembly;
	GNRGLCamera* m_GLCamera;
	
	//mediators for specific objects
	GNRMediator* m_Mediator;
	GNRAssemblyMediator2D* m_AssemblyMediator2D;
	GNRAssemblyMediator3D* m_AssemblyMediator3D;
	GNRGLCameraMediator2D* m_GLCameraMediator2D;
	GNRGLCameraMediator3D* m_GLCameraMediator3D;
	
	int mouse_x;
	int mouse_y;
	
	void updateMouse(GNRGLNotifyEvent& event);
	
protected:

public:
	GNRMouseController(GNRScene* scene);
	virtual ~GNRMouseController();
	
	void setTranslation(GNRNotifyEvent& event);
	void setSnapfunction(GNRNotifyEvent& event);
	void setMediator(GNRGLNotifyEvent& event);
	void setAssemblyMediator(GNRGLNotifyEvent& event);
	void activateMediator(GNRGLNotifyEvent& event);
};

#endif // GNRMOUSECONTROLLER_H
