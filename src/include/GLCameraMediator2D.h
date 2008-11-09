/**
 * GLCameraMediator2D
 * @note        [FINISHED]
 * @name        GLCameraMediator2D.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GLCAMERAMEDIATOR2D_H
#define GLCAMERAMEDIATOR2D_H

#include "GLCameraMediator.h"

class GLCameraMediator2D: public GLCameraMediator
{

private:

	void MoveXY(GLNotifyEvent& event);
	void MoveXZ(GLNotifyEvent& event);
	void RotateXY(GLNotifyEvent& event);
	void RotateXZ(GLNotifyEvent& event);
	void ZoomIn(GLNotifyEvent& event);
	
};

#endif // GLCAMERAMEDIATOR_H
