#ifndef GNRMathVector4D_H
#define GNRMathVector4D_H

class GNRMathVector4D
{
public:
	//constructors
	GNRMathVector4D(void)	:	x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}
	
	GNRMathVector4D(float newX, float newY, float newZ, float newW)
			:	x(newX), y(newY), z(newZ), w(newW)
	{}
	
	GNRMathVector4D(const float * rhs)	:	x(*rhs), y(*(rhs+1)), z(*(rhs+2)), w(*(rhs+3))
	{}
	
	GNRMathVector4D(const GNRMathVector4D & rhs):	x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
	{}
	
	//convert v3d to v4d
	GNRMathVector4D(const VECTOR3D & rhs):	x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f)
	{}
	
	~GNRMathVector4D() {}	//empty
	
	void Set(float newX, float newY, float newZ, float newW)
	{
		x=newX;
		y=newY;
		z=newZ;
		w=newW;
	}
	
	//accessors kept for compatability
	void SetX(float newX)
	{
		x = newX;
	}
	void SetY(float newY)
	{
		y = newY;
	}
	void SetZ(float newZ)
	{
		z = newZ;
	}
	void SetW(float newW)
	{
		w = newW;
	}
	
	float GetX() const
	{
		return x;    //public accessor functions
	}
	float GetY() const
	{
		return y;    //inline, const
	}
	float GetZ() const
	{
		return z;
	}
	float GetW() const
	{
		return w;
	}
	
	void LoadZero(void)
	{
		x=0.0f;
		y=0.0f;
		z=0.0f;
		w=0.0f;
	}
	
	void LoadOne(void)
	{
		x=1.0f;
		y=1.0f;
		z=1.0f;
		w=1.0f;
	}
	
	//vector algebra
	float DotProduct(const GNRMathVector4D & rhs)
	{
		return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
	}
	
	//rotations
	void RotateX(double angle);
	GNRMathVector4D GetRotatedX(double angle) const;
	void RotateY(double angle);
	GNRMathVector4D GetRotatedY(double angle) const;
	void RotateZ(double angle);
	GNRMathVector4D GetRotatedZ(double angle) const;
	void RotateAxis(double angle, const VECTOR3D & axis);
	GNRMathVector4D GetRotatedAxis(double angle, const VECTOR3D & axis) const;
	
	GNRMathVector4D lerp(const GNRMathVector4D & v2, float factor) const
	{
		return (*this)*(1.0f-factor)+v2*factor;
	}
	
	GNRMathVector4D QuadraticInterpolate(const GNRMathVector4D & v2, const GNRMathVector4D & v3, float factor) const
	{
		return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor;
	}
	
	//binary operators
	GNRMathVector4D operator+(const GNRMathVector4D & rhs) const
	{
		return GNRMathVector4D(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
	}
	
	GNRMathVector4D operator-(const GNRMathVector4D & rhs) const
	{
		return GNRMathVector4D(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
	}
	
	GNRMathVector4D operator*(const float rhs) const
	{
		return GNRMathVector4D(x*rhs, y*rhs, z*rhs, w*rhs);
	}
	
	GNRMathVector4D operator/(const float rhs) const
	{
		return rhs==0.0f	?	GNRMathVector4D(0.0f, 0.0f, 0.0f, 0.0f)
		       :	GNRMathVector4D(x/rhs, y/rhs, z/rhs, w/rhs);
	}
	
	//multiply by a float, eg 3*v
	friend GNRMathVector4D operator*(float scaleFactor, const GNRMathVector4D & rhs);
	
	bool operator==(const GNRMathVector4D & rhs) const;
	bool operator!=(const GNRMathVector4D & rhs) const
	{
		return !((*this)==rhs);
	}
	
	//self-add etc
	void operator+=(const GNRMathVector4D & rhs)
	{
		x+=rhs.x;
		y+=rhs.y;
		z+=rhs.z;
		w+=rhs.w;
	}
	
	void operator-=(const GNRMathVector4D & rhs)
	{
		x-=rhs.x;
		y-=rhs.y;
		z-=rhs.z;
		w-=rhs.w;
	}
	
	void operator*=(const float rhs)
	{
		x*=rhs;
		y*=rhs;
		z*=rhs;
		w*=rhs;
	}
	
	void operator/=(const float rhs)
	{
		if (rhs==0.0f)
			return;
		else
		{
			x/=rhs;
			y/=rhs;
			z/=rhs;
			w/=rhs;
		}
	}
	
	//unary operators
	GNRMathVector4D operator-(void) const
	{
		return GNRMathVector4D(-x, -y, -z, -w);
	}
	GNRMathVector4D operator+(void) const
	{
		return (*this);
	}
	
	//cast to pointer to float for glVertex4fv etc
	operator float*() const
	{
		return (float*) this;
	}
	operator const float*() const
	{
		return (const float*) this;
	}
	
	operator VECTOR3D();							//convert v4d to v3d
	
	//member variables
	float x;
	float y;
	float z;
	float w;
};

#endif	//VECTOR3D_H