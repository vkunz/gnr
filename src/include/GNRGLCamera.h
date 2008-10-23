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
	
	void setAngles(float phi, float theta, float rho);
	void setPosition(float x, float y, float z);
	void setDistance(float distance);
	
	void reset();
	
	void render();
	
	void rotateX(GLfloat angle);
	void rotateY(GLfloat angle);
	void rotateZ(GLfloat angle);
	
	void move(GNRVertex direction);
	void moveForward(GLfloat distance);
	void moveUpward(GLfloat distance);
	void strafeRight(GLfloat distance);
};

#endif // _GNRGLCAMERA_H_
