#ifndef GNRMathPlane_H
#define GNRMathPlane_H

class GNRMathPlane
{
public:
	GNRMathPlane()	:	normal(VECTOR3D(0.0f, 0.0f, 0.0f)), intercept(0.0f)
	{}
	GNRMathPlane(VECTOR3D newNormal, float newIntercept)	: normal(newNormal), intercept(newIntercept)
	{}
	GNRMathPlane(const GNRMathPlane & rhs)
	{
		normal=rhs.normal;
		intercept=rhs.intercept;
	}
	
	~GNRMathPlane() {}
	
	void SetNormal(const VECTOR3D & rhs)
	{
		normal=rhs;
	}
	void SetIntercept(float newIntercept)
	{
		intercept=newIntercept;
	}
	void SetFromPoints(const VECTOR3D & p0, const VECTOR3D & p1, const VECTOR3D & p2);
	
	void CalculateIntercept(const VECTOR3D & pointOnGNRMathPlane)
	{
		intercept=-normal.DotProduct(pointOnGNRMathPlane);
	}
	
	void Normalize(void);
	
	VECTOR3D GetNormal()
	{
		return normal;
	}
	float GetIntercept()
	{
		return intercept;
	}
	
	//find point of intersection of 3 GNRMathPlanes
	bool Intersect3(const GNRMathPlane & p2, const GNRMathPlane & p3, VECTOR3D & result);
	
	float GetDistance(const VECTOR3D & point) const;
	int ClassifyPoint(const VECTOR3D & point) const;
	
	GNRMathPlane lerp(const GNRMathPlane & p2, float factor);
	
	//operators
	bool operator==(const GNRMathPlane & rhs) const;
	bool operator!=(const GNRMathPlane & rhs) const
	{
		return!((*this)==rhs);
	}
	
	//unary operators
	GNRMathPlane operator-(void) const
	{
		return GNRMathPlane(-normal, -intercept);
	}
	GNRMathPlane operator+(void) const
	{
		return (*this);
	}
	
	//member variables
	VECTOR3D normal;	//X.N+intercept=0
	float intercept;
};

//constants for ClassifyPoint()
const int POINT_ON_GNRMathPlane=0;
const int POINT_IN_FRONT_OF_GNRMathPlane=1;
const int POINT_BEHIND_GNRMathPlane=2;

#endif //GNRMathPlane_H