/**
 * GNRGLCameraMediator
 * @note        [DONE]
 * @name        GNRGLCameraMediator.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRGLCAMERAMEDIATOR_H
#define GNRGLCAMERAMEDIATOR_H

#include "GNRMediator.h"
#include "GNRGLCamera.h"
#include "GNRVertex.h"

class GNRGLCameraMediator: public GNRMediator
{
public:

	void setGLCamera(GNRGLCamera* camera);                   //set pointer to access camera
	void setAssembly(GNRAssembly* WXUNUSED(assembly)) {};    //not needed in camera mediator
	void initialize(GNRGLNotifyEvent& event);                //initialize camera mediator
	int  translate(GNRGLNotifyEvent& event);                 //perform translation to camera
	void finalize();
	
protected:

	virtual void MoveXY(GNRGLNotifyEvent& event) = 0;
	virtual void MoveXZ(GNRGLNotifyEvent& event) = 0;
	virtual void RotateXY(GNRGLNotifyEvent& event) = 0;
	virtual void RotateXZ(GNRGLNotifyEvent& event) = 0;
	virtual void ZoomIn(GNRGLNotifyEvent& event) = 0;
	
	GNRGLCamera* m_GLCamera;
	
	//storage on mouse down
	int m_mouse_x;
	int m_mouse_y;
	int window_w;
	int window_h;
	float m_distance;
	GNRVertex old_viewPoint;
	GNRVertex old_viewDir;
	GNRVertex old_rightVector;
	GNRVertex old_upVector;
	float old_rotatedX, old_rotatedY, old_rotatedZ;
	
private:

};

#endif // GNRGLCAMERAMEDIATOR_H
