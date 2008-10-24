#ifndef GNRMOUSECONTROLLER_H
#define GNRMOUSECONTROLLER_H

#include "GNRAssembly.h"
#include "GNRAssemblyMediator2D.h"
#include "GNRAssemblyMediator3D.h"
#include "GNRGLCamera.h"
#include "GNRGLCameraMediator.h"
#include "GNRGLNotifyEvent.h"
#include "GNRMediator.h"
#include "GNRScene.h"
#include "GNREnum.h"

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
	GNRGLCameraMediator* m_GLCameraMediator;
	
protected:

public:
	GNRMouseController(GNRScene* scene);
	virtual ~GNRMouseController();
	
	void setTranslation(GNRNotifyEvent& event);
	void setMediator(GNRGLNotifyEvent& event);
	void activateMediator(GNRGLNotifyEvent& event);
};

#endif // GNRMOUSECONTROLLER_H
