#include "Maths.h"

void GNRMathVector4D::RotateX(double angle)
{
	(*this)=GetRotatedX(angle);
}

GNRMathVector4D GNRMathVector4D::GetRotatedX(double angle) const
{
	VECTOR3D v3d(x, y, z);
	
	v3d.RotateX(angle);
	
	return GNRMathVector4D(v3d.x, v3d.y, v3d.z, w);
}

void GNRMathVector4D::RotateY(double angle)
{
	(*this)=GetRotatedY(angle);
}

GNRMathVector4D GNRMathVector4D::GetRotatedY(double angle) const
{
	VECTOR3D v3d(x, y, z);
	
	v3d.RotateY(angle);
	
	return GNRMathVector4D(v3d.x, v3d.y, v3d.z, w);
}

void GNRMathVector4D::RotateZ(double angle)
{
	(*this)=GetRotatedZ(angle);
}

GNRMathVector4D GNRMathVector4D::GetRotatedZ(double angle) const
{
	VECTOR3D v3d(x, y, z);
	
	v3d.RotateZ(angle);
	
	return GNRMathVector4D(v3d.x, v3d.y, v3d.z, w);
}

void GNRMathVector4D::RotateAxis(double angle, const VECTOR3D & axis)
{
	(*this)=GetRotatedAxis(angle, axis);
}

GNRMathVector4D GNRMathVector4D::GetRotatedAxis(double angle, const VECTOR3D & axis) const
{
	VECTOR3D v3d(x, y, z);
	
	v3d.RotateAxis(angle, axis);
	
	return GNRMathVector4D(v3d.x, v3d.y, v3d.z, w);
}


GNRMathVector4D operator*(float scaleFactor, const GNRMathVector4D & rhs)
{
	return rhs*scaleFactor;
}

bool GNRMathVector4D::operator==(const GNRMathVector4D & rhs) const
{
	if (x==rhs.x && y==rhs.y && z==rhs.z && w==rhs.w)
		return true;
		
	return false;
}

GNRMathVector4D::operator VECTOR3D()
{
	if (w==0.0f || w==1.0f)
		return VECTOR3D(x, y, z);
	else
		return VECTOR3D(x/w, y/w, z/w);
}
