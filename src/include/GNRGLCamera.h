/**
 * defines a camera-class for the opengl scene
 * @note        [DONE]
 * @name        GNRGLCamera.h
 * @date        2008-10-23
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGLCAMERA_H_
#define _GNRGLCAMERA_H_

#include <GL/glu.h>

#include "GNRVertex.h"

class GNRGLCamera
{
private:

	GNRVertex viewPoint;
	GNRVertex viewDir;
	GNRVertex rightVector;
	GNRVertex upVector;
	
	float m_distance;
	GLfloat rotatedX, rotatedY, rotatedZ;
	
public:
	GNRGLCamera();
	virtual ~GNRGLCamera();
	
	void setAngles(float phi, float theta, float rho);
	void setPosition(float x, float y, float z);
	void changeDistance(float distance);
	float getDistance();
	
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
	
	GNRVertex getViewPoint();
	GNRVertex getViewDir();
	GNRVertex getRightVector();
	GNRVertex getUpVector();
	GLfloat getRotatedX();
	GLfloat getRotatedY();
	GLfloat getRotatedZ();
	
	void setViewPoint(GNRVertex point);
	void setViewDir(GNRVertex dir);
	void setRightVector(GNRVertex right);
	void setUpVector(GNRVertex up);
	void setRotatedX(GLfloat phi);
	void setRotatedY(GLfloat theta);
	void setRotatedZ(GLfloat rho);
	
};

#endif // _GNRGLCAMERA_H_
