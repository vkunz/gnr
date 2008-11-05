#include "Maths.h"

void GNRMathVector3D::Normalize()
{
	float length=GetLength();
	
	if (length==1 || length==0)			//return if length is 1 or 0
		return;
		
	float scalefactor = 1.0f/length;
	x *= scalefactor;
	y *= scalefactor;
	z *= scalefactor;
}

GNRMathVector3D GNRMathVector3D::GetNormalized() const
{
	GNRMathVector3D result(*this);
	
	result.Normalize();
	
	return result;
}

GNRMathVector3D GNRMathVector3D::GetRotatedX(double angle) const
{
	if (angle==0.0)
		return (*this);
		
	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);
	
	return GNRMathVector3D(x,
	                       y*cosAngle - z*sinAngle,
	                       y*sinAngle + z*cosAngle);
}

void GNRMathVector3D::RotateX(double angle)
{
	(*this)=GetRotatedX(angle);
}

GNRMathVector3D GNRMathVector3D::GetRotatedY(double angle) const
{
	if (angle==0.0)
		return (*this);
		
	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);
	
	return GNRMathVector3D(x*cosAngle + z*sinAngle,
	                       y,
	                       -x*sinAngle + z*cosAngle);
}

void GNRMathVector3D::RotateY(double angle)
{
	(*this)=GetRotatedY(angle);
}

GNRMathVector3D GNRMathVector3D::GetRotatedZ(double angle) const
{
	if (angle==0.0)
		return (*this);
		
	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);
	
	return GNRMathVector3D(x*cosAngle - y*sinAngle,
	                       x*sinAngle + y*cosAngle,
	                       z);
}

void GNRMathVector3D::RotateZ(double angle)
{
	(*this)=GetRotatedZ(angle);
}

GNRMathVector3D GNRMathVector3D::GetRotatedAxis(double angle, const GNRMathVector3D & axis) const
{
	if (angle==0.0)
		return (*this);
		
	GNRMathVector3D u=axis.GetNormalized();
	
	GNRMathVector3D rotMatrixRow0, rotMatrixRow1, rotMatrixRow2;
	
	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);
	float oneMinusCosAngle=1.0f-cosAngle;
	
	rotMatrixRow0.x=(u.x)*(u.x) + cosAngle*(1-(u.x)*(u.x));
	rotMatrixRow0.y=(u.x)*(u.y)*(oneMinusCosAngle) - sinAngle*u.z;
	rotMatrixRow0.z=(u.x)*(u.z)*(oneMinusCosAngle) + sinAngle*u.y;
	
	rotMatrixRow1.x=(u.x)*(u.y)*(oneMinusCosAngle) + sinAngle*u.z;
	rotMatrixRow1.y=(u.y)*(u.y) + cosAngle*(1-(u.y)*(u.y));
	rotMatrixRow1.z=(u.y)*(u.z)*(oneMinusCosAngle) - sinAngle*u.x;
	
	rotMatrixRow2.x=(u.x)*(u.z)*(oneMinusCosAngle) - sinAngle*u.y;
	rotMatrixRow2.y=(u.y)*(u.z)*(oneMinusCosAngle) + sinAngle*u.x;
	rotMatrixRow2.z=(u.z)*(u.z) + cosAngle*(1-(u.z)*(u.z));
	
	return GNRMathVector3D(this->DotProduct(rotMatrixRow0),
	                       this->DotProduct(rotMatrixRow1),
	                       this->DotProduct(rotMatrixRow2));
}

void GNRMathVector3D::RotateAxis(double angle, const GNRMathVector3D & axis)
{
	(*this)=GetRotatedAxis(angle, axis);
}


void GNRMathVector3D::PackTo01()
{
	(*this)=GetPackedTo01();
}

GNRMathVector3D GNRMathVector3D::GetPackedTo01() const
{
	GNRMathVector3D temp(*this);
	
	temp.Normalize();
	
	temp=temp*0.5f+GNRMathVector3D(0.5f, 0.5f, 0.5f);
	
	return temp;
}

GNRMathVector3D operator*(float scaleFactor, const GNRMathVector3D & rhs)
{
	return rhs*scaleFactor;
}

bool GNRMathVector3D::operator==(const GNRMathVector3D & rhs) const
{
	if (x==rhs.x && y==rhs.y && z==rhs.z)
		return true;
		
	return false;
}

