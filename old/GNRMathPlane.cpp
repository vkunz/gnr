#include "Maths.h"

void GNRMathPlane::SetFromPoints(const VECTOR3D & p0, const VECTOR3D & p1, const VECTOR3D & p2)
{
	normal=(p1-p0).CrossProduct(p2-p0);
	
	normal.Normalize();
	
	CalculateIntercept(p0);
}

void GNRMathPlane::Normalize()
{
	float normalLength=normal.GetLength();
	normal/=normalLength;
	intercept/=normalLength;
}

bool GNRMathPlane::Intersect3(const GNRMathPlane & p2, const GNRMathPlane & p3, VECTOR3D & result)//find point of intersection of 3 GNRMathPlanes
{
	float denominator=normal.DotProduct((p2.normal).CrossProduct(p3.normal));
	//scalar triple product of normals
	if (denominator==0.0f)									//if zero
		return false;										//no intersection
		
	VECTOR3D temp1, temp2, temp3;
	temp1=(p2.normal.CrossProduct(p3.normal))*intercept;
	temp2=(p3.normal.CrossProduct(normal))*p2.intercept;
	temp3=(normal.CrossProduct(p2.normal))*p3.intercept;
	
	result=(temp1+temp2+temp3)/(-denominator);
	
	return true;
}

float GNRMathPlane::GetDistance(const VECTOR3D & point) const
{
	return point.x*normal.x + point.y*normal.y + point.z*normal.z + intercept;
}

int GNRMathPlane::ClassifyPoint(const VECTOR3D & point) const
{
	float distance=point.x*normal.x + point.y*normal.y + point.z*normal.z + intercept;
	
	if (distance>EPSILON)	//==0.0f is too exact, give a bit of room
		return POINT_IN_FRONT_OF_GNRMathPlane;
		
	if (distance<-EPSILON)
		return POINT_BEHIND_GNRMathPlane;
		
	return POINT_ON_GNRMathPlane;	//otherwise
}

GNRMathPlane GNRMathPlane::lerp(const GNRMathPlane & p2, float factor)
{
	GNRMathPlane result;
	result.normal=normal*(1.0f-factor) + p2.normal*factor;
	result.normal.Normalize();
	
	result.intercept=intercept*(1.0f-factor) + p2.intercept*factor;
	
	return result;
}

bool GNRMathPlane::operator ==(const GNRMathPlane & rhs) const
{
	if (normal==rhs.normal && intercept==rhs.intercept)
		return true;
		
	return false;
}
