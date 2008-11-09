/**
 * defines a camera-class for the opengl scene
 * @note        [DONE]
 * @name        GLCamera.h
 * @date        2008-10-23
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGLCAMERA_H_
#define _GNRGLCAMERA_H_

#include <GL/glu.h>

#include "Vertex.h"

class GLCamera
{
private:

	Vertex viewPoint;
	Vertex viewDir;
	Vertex rightVector;
	Vertex upVector;
	
	float m_distance;
	GLfloat rotatedX, rotatedY, rotatedZ;
	
public:
	GLCamera();
	virtual ~GLCamera();
	
	void setAngles(float phi, float theta, float rho);
	void setPosition(float x, float y, float z);
	void changeDistance(float distance);
	float getDistance();
	
	void reset();
	
	void render();
	
	void rotateX(GLfloat angle);
	void rotateY(GLfloat angle);
	void rotateZ(GLfloat angle);
	
	void move(Vertex direction);
	void moveForward(GLfloat distance);
	void moveUpward(GLfloat distance);
	void strafeRight(GLfloat distance);
	
	Vertex getPosition();
	
	Vertex getViewPoint();
	Vertex getViewDir();
	Vertex getRightVector();
	Vertex getUpVector();
	GLfloat getRotatedX();
	GLfloat getRotatedY();
	GLfloat getRotatedZ();
	
	void setViewPoint(Vertex point);
	void setViewDir(Vertex dir);
	void setRightVector(Vertex right);
	void setUpVector(Vertex up);
	void setRotatedX(GLfloat phi);
	void setRotatedY(GLfloat theta);
	void setRotatedZ(GLfloat rho);
	
};

#endif // _GNRGLCAMERA_H_
