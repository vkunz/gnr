/**
 * the gl-camera class implements functions to move and rotate the
 * camera in a whole scene. rotating is done in 3rd person
 * @note        [DONE]
 * @name        GLCamera.cpp
 * @date        2008-10-23
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <math.h>

#include "GLCamera.h"
#include "GlobalDefine.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GLCamera
 */
GLCamera::GLCamera()
{
	reset();
}

/**
 * Moves the camera (View-Point) along the direction-vector
 * @param[in]       direction       direction to move the camera
 */
void GLCamera::move(Vertex direction)
{
	viewPoint = viewPoint + direction;
}

/**
 * Moves the camera (View-Point) along the direction-vector
 * @param[in]       x       direction to move the camera in x
 * @param[in]       y       direction to move the camera in y
 * @param[in]       z       direction to move the camera in z
 */
void GLCamera::move(const float x, const float y, const float z)
{
	viewPoint = viewPoint + Vertex(x,y,z);
}

/**
 * Rotates the camera arround the x-axis
 * @param[in]       angle           angle to rotate the camera
 */
void GLCamera::rotateX(GLfloat angle)
{
	rotatedX += angle;
	
	//Rotate viewdir around the right-Vector:
	viewDir = viewDir*cos(angle*M_PI/180.0) + upVector*sin(angle*M_PI/180.0);
	viewDir.normalize();
	
	//now compute the new UpVector (by cross product)
	upVector = (viewDir * rightVector) *-1;
}

/**
 * Rotates the camera arround the y-axis
 * @param[in]       angle           angle to rotate the camera
 */
void GLCamera::rotateY(GLfloat angle)
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
 * @param[in]       angle               angle to rotate the camera
 */
void GLCamera::rotateZ(GLfloat angle)
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
 */
void GLCamera::render()
{

	//The point at which the camera looks:
	Vertex position = viewPoint - viewDir*m_distance;
	if (position.getY() <= CAMERA_HEIGHT_MIN)
	{
		position.setY(CAMERA_HEIGHT_MIN);
		viewPoint = position + viewDir*m_distance;
	}
	
	//as we know the up vector, we can easily use gluLookAt:
	gluLookAt(position.getX(),position.getY(),position.getZ(),
	          viewPoint.getX(),viewPoint.getY(),viewPoint.getZ(),
	          upVector.getX(),upVector.getY(),upVector.getZ());
	          
}

/**
 * moves the camera into the scene
 * @param[in]       distance        distance, the camera should move forward
 */
void GLCamera::moveForward(GLfloat distance)
{
	viewPoint = viewPoint + (viewDir*-distance);
	if (viewPoint.getY() <= CAMERA_HEIGHT_MIN)
	{
		viewPoint.setY(CAMERA_HEIGHT_MIN);
	}
}

/**
 * moces the camera in horizontal way
 * @param[in]       distance        distance, the camera should move right
 */
void GLCamera::strafeRight(GLfloat distance)
{
	viewPoint = viewPoint + (rightVector*distance);
}

/**
 * moces the camera in vertical way
 * @param[in]       distance        distance, the camera should move upwards
 */
void GLCamera::moveUpward(GLfloat distance)
{
	viewPoint = viewPoint + (upVector*distance);
	if (viewPoint.getY() <= CAMERA_HEIGHT_MIN)
	{
		viewPoint.setY(CAMERA_HEIGHT_MIN);
	}
}

/**
 * sets complete camera
 * @param[in]       x               x position, the camera is standing
 * @param[in]       y               y position, the camera is standing
 * @param[in]       z               z position, the camera is standing
 * @param[in]       phi             angle, the camera is rotated arround x-axis
 * @param[in]       theta           angle, the camera is rotated arround y-axis
 * @param[in]       rho             angle, the camera is rotated arround z-axis
 */
void GLCamera::setCamera(const float& x, const float& y, const float& z, const float& phi, const float& theta, const float& rho)
{
	//first reset camera
	reset();
	
	//rotate cam
	rotateZ(rho);
	rotateY(theta);
	rotateX(phi);
	
	//change distance from center
	changeDistance(sqrt(x*x + y*y + z*z));
}

/**
 * sets the absolute position of the camera
 * @param[in]       x               x position in world coordinates
 * @param[in]       y               y position in world coordinates
 * @param[in]       z               z position in world coordinates
 */
void GLCamera::setPosition(float x, float y, float z)
{
	Vertex temp(x, y, z);
	
	viewPoint = (temp + viewDir*m_distance);
	if (viewPoint.getY() <= CAMERA_HEIGHT_MIN)
	{
		viewPoint.setY(CAMERA_HEIGHT_MIN);
	}
}

/**
 * sets the orientation of the camera
 * @param[in]       phi             angle, the camera is rotated arround x-axis
 * @param[in]       theta           angle, the camera is rotated arround y-axis
 * @param[in]       rho             angle, the camera is rotated arround z-axis
 */
void GLCamera::setAngles(float phi, float theta, float rho)
{
	reset();
	
	rotateZ(rho);
	rotateY(theta);
	rotateX(phi);
}

/**
 * changes the distance of camera
 * @param[in]       distance        camera distance
 */
void GLCamera::setDistance(float distance)
{
	m_distance = distance;
	if (m_distance <= CAMERA_DISTANCE_MIN)
	{
		m_distance = CAMERA_DISTANCE_MIN;
	}
}

/**
 * changes the distance between camera and view-point
 * @param[in]       distance        amount, the distance should raise
 */
void GLCamera::changeDistance(float distance)
{
	m_distance += distance;
	if (m_distance <= CAMERA_DISTANCE_MIN)
	{
		m_distance = CAMERA_DISTANCE_MIN;
		Vertex oldViewPoint = viewPoint + viewDir*m_distance;
		setViewPoint(oldViewPoint);
	}
}

/**
 * get the distance between camera and view-point
 * @return          float           distance of cam to floor
 */
float GLCamera::getDistance()
{
	return m_distance;
}

/**
 * resets the camera to initial-position
 */
void GLCamera::reset()
{
	//Init with standard OGL values:
	viewPoint   = Vertex(0.0, 0.0, 0.0);
	viewDir     = Vertex(0.0, 0.0,-1.0);
	rightVector = Vertex(1.0, 0.0, 0.0);
	upVector    = Vertex(0.0, 1.0, 0.0);
	
	rotatedX = rotatedY = rotatedZ = 0.0;
	
	m_distance = 1.0;
}

/**
 * returns the position of the camera
 * @return          Vertex          Camera-Position
 */
Vertex GLCamera::getPosition()
{
	Vertex position = viewPoint - viewDir*m_distance;
	return position;
}

/**
 * returns the ViewPoint of the camera
 * @return          Vertex          ViewPoint
 */
Vertex GLCamera::getViewPoint()
{
	return viewPoint;
}

/**
 * returns the View-Direction of the camera
 * @return          Vertex          View-Direction
 */
Vertex GLCamera::getViewDir()
{
	return viewDir;
}

/**
 * returns the right-Vector of the camera
 * @return          Vertex          right-Vector
 */
Vertex GLCamera::getRightVector()
{
	return rightVector;
}

/**
 * returns the up-Vector of the camera
 * @return          Vertex          up-Vector
 */
Vertex GLCamera::getUpVector()
{
	return upVector;
}

/**
 * returns the rotation of the camera arround x-axis
 * @return          GLfloat         x-Rotation in Degree
 */
GLfloat GLCamera::getRotatedX()
{
	return rotatedX;
}

/**
 * returns the rotation of the camera arround y-axis
 * @return          GLfloat         y-Rotation in Degree
 */
GLfloat GLCamera::getRotatedY()
{
	return rotatedY;
}

/**
 * returns the rotation of the camera arround z-axis
 * @return          GLfloat         z-Rotation in Degree
 */
GLfloat GLCamera::getRotatedZ()
{
	return rotatedZ;
}

/**
 * sets the View-Point of the camera
 * @param[in]       point           View-Point
 */
void GLCamera::setViewPoint(Vertex point)
{
	if (point.getY() <= CAMERA_HEIGHT_MIN)
	{
		point.setY(CAMERA_HEIGHT_MIN);
	}
	viewPoint = point;
}

/**
 * sets the View-Direction of the camera
 * @param[in]       dir             View-Direction
 */
void GLCamera::setViewDir(Vertex dir)
{
	viewDir = dir;
}

/**
 * sets the right-Vector of the camera
 * @param[in]       right           right-Vector
 */
void GLCamera::setRightVector(Vertex right)
{
	rightVector = right;
}

/**
 * sets the up-Vector of the camera
 * @param[in]       up              up-Vector
 */
void GLCamera::setUpVector(Vertex up)
{
	upVector = up;
}

/**
 * sets the rotation of the camera arround x-axis
 * @param[in]       phi             x-Rotation in Degree
 */
void GLCamera::setRotatedX(GLfloat phi)
{
	rotatedX = phi;
}

/**
 * sets the rotation of the camera arround y-axis
 * @param[in]       theta           y-Rotation in Degree
 */
void GLCamera::setRotatedY(GLfloat theta)
{
	rotatedY = theta;
}

/**
 * sets the rotation of the camera arround z-axis
 * @param[in]       rho             z-Rotation in Degree
 */
void GLCamera::setRotatedZ(GLfloat rho)
{
	rotatedZ = rho;
}

/**
 * destructor of GLCamera
 */
GLCamera::~GLCamera() {}
