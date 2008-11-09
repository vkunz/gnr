/**
 * GLCameraMediator3D
 * @note        [FINISHED]
 * @name        GLCameraMediator3D.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GLCAMERAMEDIATOR3D_H
#define GLCAMERAMEDIATOR3D_H

#include "GLCameraMediator.h"

class GLCameraMediator3D: public GLCameraMediator
{

private:

	void MoveXY(GLNotifyEvent& event);
	void MoveXZ(GLNotifyEvent& event);
	void RotateXY(GLNotifyEvent& event);
	void RotateXZ(GLNotifyEvent& event);
	void ZoomIn(GLNotifyEvent& event);
	
};

#endif // GLCAMERAMEDIATOR_H
