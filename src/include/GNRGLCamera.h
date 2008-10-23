/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * defines a camera-class for the opengl scene
 * @name        GNRGLCamera.h
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGLCAMERA_H_
#define _GNRGLCAMERA_H_

#include "GNRVertex.h"
#include <GL/glu.h>

class GNRGLCamera
{
private:

	GNRVertex viewDir;
	GNRVertex rightVector;
	GNRVertex upVector;
	GNRVertex viewPoint;
	
	float m_distance;
	
	GLfloat rotatedX, rotatedY, rotatedZ;
	
public:
	GNRGLCamera();
	virtual ~GNRGLCamera();
	
	void setAngles(float phi, float theta, float rho);
	void setPosition(float x, float y, float z);
	void changeDistance(float distance);
	
	void reset();
	
	void render();
	
	void rotateX(GLfloat angle);
	void rotateY(GLfloat angle);
	void rotateZ(GLfloat angle);
	
	void move(GNRVertex direction);
	void moveForward(GLfloat distance);
	void moveUpward(GLfloat distance);
	void strafeRight(GLfloat distance);
	
	GNRVertex getPosition();
};

#endif // _GNRGLCAMERA_H_
