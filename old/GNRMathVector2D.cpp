#include "Maths.h"

void GNRMathVector2D::Normalize()
{
	float length;
	float scalefactor;
	length=GetLength();
	
	if (length==1 || length==0)			//return if length is 1 or 0
		return;
		
	scalefactor = 1.0f/length;
	x *= scalefactor;
	y *= scalefactor;
}

GNRMathVector2D GNRMathVector2D::GetNormalized() const
{
	GNRMathVector2D result(*this);
	
	result.Normalize();
	
	return result;
}

GNRMathVector2D operator*(float scaleFactor, const GNRMathVector2D & rhs)
{
	return rhs*scaleFactor;
}

bool GNRMathVector2D::operator==(const GNRMathVector2D & rhs) const
{
	if (x==rhs.x && y==rhs.y)
		return true;
		
	return false;
}



