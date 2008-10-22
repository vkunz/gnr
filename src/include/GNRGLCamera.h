#ifndef _GNRGLCAMERA_H_
#define _GNRGLCAMERA_H_

#include <GL/glu.h>		// Need to include it here because the GL* types are required
#define PI 3.1415926535897932384626433832795
#define PIdiv180 (PI/180.0)

struct SF3dVector   //Float 3d-vect, normally used
{
	GLfloat x,y,z;
};
struct SF2dVector
{
	GLfloat x,y;
};
SF3dVector F3dVector(GLfloat x, GLfloat y, GLfloat z);

class GNRGLCamera
{
private:

	SF3dVector ViewDir;
	SF3dVector RightVector;
	SF3dVector UpVector;
	SF3dVector Position;
	
	GLfloat RotatedX, RotatedY, RotatedZ;
	
public:
	GNRGLCamera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	void Render(void);	//executes some glRotates and a glTranslate command
	//Note: You should call glLoadIdentity before using Render
	
	void Move(SF3dVector Direction);
	void RotateX(GLfloat Angle);
	void RotateY(GLfloat Angle);
	void RotateZ(GLfloat Angle);
	
	void MoveForward(GLfloat Distance);
	void MoveUpward(GLfloat Distance);
	void StrafeRight(GLfloat Distance);
	
};

#endif // _GNRGLCAMERA_H_
