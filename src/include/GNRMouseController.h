#ifndef GNRMOUSECONTROLLER_H
#define GNRMOUSECONTROLLER_H

#include "GNRAssembly.h"
#include "GNRAssemblyMediator.h"
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
	GNRAssemblyMediator* m_AssemblyMediator;
	GNRGLCameraMediator* m_GLCameraMediator;
	
protected:

public:
	GNRMouseController(GNRScene* scene);
	virtual ~GNRMouseController();
	
	void setMediator(buttonType mouse_button, canvasType canvas_id);
	void activateMediator(GNRGLNotifyEvent& event);
};

#endif // GNRMOUSECONTROLLER_H
