/**
 * MouseController
 * @name        MouseController.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _MOUSECONTROLLER_H_
#define _MOUSECONTROLLER_H_

#include <wx/event.h>

#include "Enum.h"

class Assembly;
class AssemblyMediator2D;
class AssemblyMediator3D;
class GLCamera;
class GLCameraMediator2D;
class GLCameraMediator3D;
class GLNotifyEvent;
class MeasureMediator;
class Mediator;
class NotifyEvent;
class Scene;
class WallMediator;

class MouseController : public wxEvtHandler
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
	WallMediator*       m_WallMediator;
	MeasureMediator*    m_MeasureMediator;

	int mouse_x;
	int mouse_y;

	transType m_act_trans;

	void updateMouse(GLNotifyEvent& event);

protected:

public:
	MouseController();
	virtual ~MouseController();

	void setTranslation(NotifyEvent& event);
	void setSnapfunction(NotifyEvent& event);
	void setSelected(GLNotifyEvent& event);
	void setMediator(GLNotifyEvent& event);
	void setAssemblyMediator(GLNotifyEvent& event);
	void activateMediator(GLNotifyEvent& event);
	void deactivateMediator();
	Assembly* getAssembly();
};

#endif // _MOUSECONTROLLER_H_
