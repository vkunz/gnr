/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * the gl-camera class implements functions to move and rotate the
 * camera in a whole scene. rotating is done in 3rd person
 *
 * @name        GNRGLCamera.cpp
 * @date        2008-10-23
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRGLCamera.h"
#include "math.h"

/**
 * constructor of GNRGLCamera
 * @access      public
 */
GNRGLCamera::GNRGLCamera()
{
	reset();
}

/**
 * Moves the camera (View-Point) along the direction-vector
 * @param       GNRAssembly*    RootAssembly
 * @param       int             Mouse-X-Coordinate
 * @param       int             Mouse-Y-Coordinate
 * @return      int             GL-Object-ID
 * @access      public
 */
void GNRGLCamera::move(GNRVertex direction)
{
	viewPoint = viewPoint + direction;
}

/**
 * Rotates the camera arround the x-axis
 * @param       GLfloat     angle to rotate the camera
 * @access      public
 */
void GNRGLCamera::rotateX(GLfloat angle)
{
	rotatedX += angle;
	
	//Rotate viewdir around the right vector:
	viewDir = viewDir*cos(angle*M_PI/180.0) + upVector*sin(angle*M_PI/180.0);
	viewDir.normalize();
	
	//now compute the new UpVector (by cross product)
	upVector = (viewDir * rightVector) *-1;
}

/**
 * Rotates the camera arround the y-axis
 * @param       GLfloat     angle to rotate the camera
 * @access      public
 */
void GNRGLCamera::rotateY(GLfloat angle)
{
	rotatedY += angle;
	
	//Rotate viewdir around the up vector at the viewPoint:
	viewDir = viewDir*cos(angle*M_PI/180.0) - rightVector*sin(angle*M_PI/180.0);
	viewDir.normalize();
	
	//now compute the new RightVector (by cross product)
	rightVector = viewDir * upVector;
}

/**
 * Rotates the camera arround the z-axis
 * @param       GLfloat     angle to rotate the camera
 * @access      public
 */
void GNRGLCamera::rotateZ(GLfloat angle)
{
	rotatedZ += angle;
	
	//Rotate viewdir around the right vector:
	rightVector = rightVector*cos(angle*M_PI/180.0) + upVector*sin(angle*M_PI/180.0);
	rightVector.normalize();
	
	//now compute the new UpVector (by cross product)
	upVector = (viewDir * rightVector)*-1;
}

/**
 * translates the vectors to opengl-commands which set the camera
 * @access      public
 */
void GNRGLCamera::render()
{

	//The point at which the camera looks:
	GNRVertex position = viewPoint - viewDir*m_distance;
	
	//as we know the up vector, we can easily use gluLookAt:
	gluLookAt(position.getX(),position.getY(),position.getZ(),
	          viewPoint.getX(),viewPoint.getY(),viewPoint.getZ(),
	          upVector.getX(),upVector.getY(),upVector.getZ());
	          
}

/**
 * moves the camera into the scene
 * @param       GLfloat     distance, the camera should move forward
 * @access      public
 */
void GNRGLCamera::moveForward(GLfloat distance)
{
	viewPoint = viewPoint + (viewDir*-distance);
}

/**
 * moces the camera in horizontal way
 * @param       GLfloat     distance, the camera should move right
 * @access      public
 */
void GNRGLCamera::strafeRight(GLfloat distance)
{
	viewPoint = viewPoint + (rightVector*distance);
}

/**
 * moces the camera in vertical way
 * @param       GLfloat     distance, the camera should move upwards
 * @access      public
 */
void GNRGLCamera::moveUpward(GLfloat distance)
{
	viewPoint = viewPoint + (upVector*distance);
}

/**
 * sets the absolute position of the camera
 * @param       GLfloat     x position in world coordinates
 * @param       GLfloat     y position in world coordinates
 * @param       GLfloat     z position in world coordinates
 * @access      public
 */
void GNRGLCamera::setPosition(float x, float y, float z)
{
	GNRVertex temp(x, y, z);
	viewPoint = (temp + viewDir*m_distance);
}

/**
 * sets the orientation of the camera
 * @param       float     angle, the camera is rotated arround x-axis
 * @param       float     angle, the camera is rotated arround y-axis
 * @param       float     angle, the camera is rotated arround z-axis
 * @access      public
 */
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

/**
 * changes the distance between camera and view-point
 * @param       float     amount, the distance should raise
 * @access      public
 */
void GNRGLCamera::changeDistance(float distance)
{
	m_distance += distance;
}

/**
 * resets the camera to initial-position
 * @access      public
 */
void GNRGLCamera::reset()
{
	//Init with standard OGL values:
	viewPoint   = GNRVertex(0.0, 0.0, 0.0);
	viewDir     = GNRVertex(0.0, 0.0,-1.0);
	rightVector = GNRVertex(1.0, 0.0, 0.0);
	upVector    = GNRVertex(0.0, 1.0, 0.0);
	
	rotatedX = rotatedY = rotatedZ = 0.0;
	
	m_distance = 2.5;
}

/**
 * returns the position of the camera
 * @return  GNRVertex   Camera-Position
 * @access      public
 */
GNRVertex GNRGLCamera::getPosition()
{
	GNRVertex position = viewPoint - viewDir*m_distance;
	return position;
}

/**
 * returns the ViewPoint of the camera
 * @return  GNRVertex   ViewPoint
 * @access      public
 */
GNRVertex GNRGLCamera::getViewPoint()
{
	return viewPoint;
}

/**
 * returns the View-Direction of the camera
 * @return  GNRVertex   View-Direction
 * @access      public
 */
GNRVertex GNRGLCamera::getViewDir()
{
	return viewDir;
}

/**
 * returns the right-Vector of the camera
 * @return  GNRVertex   right-Vector
 * @access      public
 */
GNRVertex GNRGLCamera::getRightVector()
{
	return rightVector;
}

/**
 * returns the up-Vector of the camera
 * @return  GNRVertex   up-Vector
 * @access      public
 */
GNRVertex GNRGLCamera::getUpVector()
{
	return upVector;
}

/**
 * returns the rotation of the camera arround x-axis
 * @return  GLfloat   x-Rotation in Degree
 * @access      public
 */
GLfloat GNRGLCamera::getRotatedX()
{
	return rotatedX;
}

/**
 * returns the rotation of the camera arround y-axis
 * @return  GLfloat   y-Rotation in Degree
 * @access      public
 */
GLfloat GNRGLCamera::getRotatedY()
{
	return rotatedY;
}

/**
 * returns the rotation of the camera arround z-axis
 * @return  GLfloat   z-Rotation in Degree
 * @access      public
 */
GLfloat GNRGLCamera::getRotatedZ()
{
	return rotatedZ;
}

/**
 * sets the View-Point of the camera
 * @param  GNRVertex   View-Point
 * @access      public
 */
void GNRGLCamera::setViewPoint(GNRVertex point)
{
	viewPoint = point;
}

/**
 * sets the View-Direction of the camera
 * @param  GNRVertex   View-Direction
 * @access      public
 */
void GNRGLCamera::setViewDir(GNRVertex dir)
{
	viewDir = dir;
}

/**
 * sets the right-Vector of the camera
 * @param  GNRVertex   right-Vector
 * @access      public
 */
void GNRGLCamera::setRightVector(GNRVertex right)
{
	rightVector = right;
}

/**
 * sets the up-Vector of the camera
 * @param  GNRVertex   up-Vector
 * @access      public
 */
void GNRGLCamera::setUpVector(GNRVertex up)
{
	upVector = up;
}

/**
 * sets the rotation of the camera arround x-axis
 * @param  GLfloat   x-Rotation in Degree
 * @access      public
 */
void GNRGLCamera::setRotatedX(GLfloat phi)
{
	rotatedX = phi;
}

/**
 * sets the rotation of the camera arround y-axis
 * @param  GLfloat   y-Rotation in Degree
 * @access      public
 */
void GNRGLCamera::setRotatedY(GLfloat theta)
{
	rotatedY = theta;
}

/**
 * sets the rotation of the camera arround z-axis
 * @param  GLfloat   z-Rotation in Degree
 * @access      public
 */
void GNRGLCamera::setRotatedZ(GLfloat rho)
{
	rotatedZ = rho;
}

/**
 * destructor of GNRGLCamera
 * @access      public
 */
GNRGLCamera::~GNRGLCamera() {}
