#include "GNRGLCamera.h"
#include "math.h"

GNRGLCamera::GNRGLCamera()
{
	//Init with standard OGL values:
	viewPoint   = GNRVertex(0.0, 0.0,-1.0);
	viewDir     = GNRVertex(0.0, 0.0,-1.0);
	rightVector = GNRVertex(1.0, 0.0, 0.0);
	upVector    = GNRVertex(0.0, 1.0, 0.0);
	
	m_distance = 1.5;
	
	rotatedX = rotatedY = rotatedZ = 0.0;
}

void GNRGLCamera::move(GNRVertex direction)
{
	viewPoint = viewPoint + direction;
}


void GNRGLCamera::rotateX(GLfloat angle)
{
	rotatedX += angle;
	
	//Rotate viewdir around the right vector:
	viewDir = viewDir*cos(angle*M_PI/180.0) + upVector*sin(angle*M_PI/180.0);
	viewDir.normalize();
	
	//now compute the new UpVector (by cross product)
	upVector = (viewDir * rightVector) *-1;
}

void GNRGLCamera::rotateY(GLfloat angle)
{
	rotatedY += angle;
	
	//Rotate viewdir around the up vector at the viewPoint:
	viewDir = viewDir*cos(angle*M_PI/180.0) - rightVector*sin(angle*M_PI/180.0);
	viewDir.normalize();
	
	//now compute the new RightVector (by cross product)
	rightVector = viewDir * upVector;
}

void GNRGLCamera::rotateZ(GLfloat angle)
{
	rotatedZ += angle;
	
	//Rotate viewdir around the right vector:
	rightVector = rightVector*cos(angle*M_PI/180.0) + upVector*sin(angle*M_PI/180.0);
	rightVector.normalize();
	
	//now compute the new UpVector (by cross product)
	upVector = (viewDir * rightVector)*-1;
}

void GNRGLCamera::render()
{

	//The point at which the camera looks:
	GNRVertex position = viewPoint - viewDir*m_distance;
	
	//as we know the up vector, we can easily use gluLookAt:
	gluLookAt(position.getX(),position.getY(),position.getZ(),
	          viewPoint.getX(),viewPoint.getY(),viewPoint.getZ(),
	          upVector.getX(),upVector.getY(),upVector.getZ());
	          
}

void GNRGLCamera::moveForward(GLfloat distance)
{
	viewPoint = viewPoint + (viewDir*-distance);
}

void GNRGLCamera::strafeRight(GLfloat distance)
{
	viewPoint = viewPoint + (rightVector*distance);
}

void GNRGLCamera::moveUpward(GLfloat distance)
{
	viewPoint = viewPoint + (upVector*distance);
}

void GNRGLCamera::setPosition(float x, float y, float z)
{
	GNRVertex temp(x, y, z);
	viewPoint = (temp + viewDir*m_distance);
}

void GNRGLCamera::setAngles(float phi, float theta, float rho)
{
	viewDir.setX(0);
	viewDir.setY(0);
	viewDir.setZ(-1);
	viewDir.rotate(phi, theta, 0.0);
	viewDir.normalize();
	
	upVector.setX(0);
	upVector.setY(1);
	upVector.setZ(0);
	upVector.rotate(0.0, 0.0, 0.0);
	upVector.normalize();
	
	rotatedX = phi;
	rotatedY = theta;
	rotatedZ = rho;
}

void GNRGLCamera::setDistance(float distance)
{
	m_distance = distance;
}
