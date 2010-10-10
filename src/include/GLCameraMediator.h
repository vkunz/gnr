/**
 * GLCameraMediator
 * @note        [DONE]
 * @name        GLCameraMediator.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GLCAMERAMEDIATOR_H_
#define _GLCAMERAMEDIATOR_H_

#include "Mediator.h"
#include "Vertex.h"

class GLCameraMediator: public Mediator
{
public:

	void setGLCamera(GLCamera* camera);                   //set pointer to access camera
	void setAssembly(Assembly* WXUNUSED(assembly)) {};    //not needed in camera mediator
	void initialize(GLNotifyEvent& event);                //initialize camera mediator
	int  translate(GLNotifyEvent& event);                 //perform translation to camera
	void finalize();

protected:

	virtual void MoveXY(GLNotifyEvent& event) = 0;
	virtual void MoveXZ(GLNotifyEvent& event) = 0;
	virtual void RotateXY(GLNotifyEvent& event) = 0;
	virtual void RotateXZ(GLNotifyEvent& event) = 0;
	virtual void ZoomIn(GLNotifyEvent& event) = 0;

	GLCamera* m_GLCamera;

	//storage on mouse down
	int m_mouse_x;
	int m_mouse_y;
	int window_w;
	int window_h;
	float m_distance;
	Vertex old_viewPoint;
	Vertex old_viewDir;
	Vertex old_rightVector;
	Vertex old_upVector;
	float old_rotatedX, old_rotatedY, old_rotatedZ;

private:

};

#endif // _GLCAMERAMEDIATOR_H_
