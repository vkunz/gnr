#ifndef GNRMathVector3D_H
#define GNRMathVector3D_H

class GNRMathVector3D
{
public:
	//constructors
	GNRMathVector3D(void)	:	x(0.0f), y(0.0f), z(0.0f)
	{}
	
	GNRMathVector3D(float newX, float newY, float newZ)	:	x(newX), y(newY), z(newZ)
	{}
	
	GNRMathVector3D(const float * rhs)	:	x(*rhs), y(*(rhs+1)), z(*(rhs+2))
	{}
	
	GNRMathVector3D(const GNRMathVector3D & rhs)	:	x(rhs.x), y(rhs.y), z(rhs.z)
	{}
	
	~GNRMathVector3D() {}	//empty
	
	void Set(float newX, float newY, float newZ)
	{
		x=newX;
		y=newY;
		z=newZ;
	}
	
	//Accessors kept for compatibility
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
	
	void LoadZero(void)
	{
		x=y=z=0.0f;
	}
	void LoadOne(void)
	{
		x=y=z=1.0f;
	}
	
	//vector algebra
	GNRMathVector3D CrossProduct(const GNRMathVector3D & rhs) const
	{
		return GNRMathVector3D(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
	}
	
	float DotProduct(const GNRMathVector3D & rhs) const
	{
		return x*rhs.x + y*rhs.y + z*rhs.z;
	}
	
	void Normalize();
	GNRMathVector3D GetNormalized() const;
	
	float GetLength() const
	{
		return (float)sqrt((x*x)+(y*y)+(z*z));
	}
	
	float GetSquaredLength() const
	{
		return (x*x)+(y*y)+(z*z);
	}
	
	//rotations
	void RotateX(double angle);
	GNRMathVector3D GetRotatedX(double angle) const;
	void RotateY(double angle);
	GNRMathVector3D GetRotatedY(double angle) const;
	void RotateZ(double angle);
	GNRMathVector3D GetRotatedZ(double angle) const;
	void RotateAxis(double angle, const GNRMathVector3D & axis);
	GNRMathVector3D GetRotatedAxis(double angle, const GNRMathVector3D & axis) const;
	
	//pack to [0,1] for color
	void PackTo01();
	GNRMathVector3D GetPackedTo01() const;
	
	//linear interpolate
	GNRMathVector3D lerp(const GNRMathVector3D & v2, float factor) const
	{
		return (*this)*(1.0f-factor) + v2*factor;
	}
	
	GNRMathVector3D QuadraticInterpolate(const GNRMathVector3D & v2, const GNRMathVector3D & v3, float factor) const
	{
		return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor;
	}
	
	
	//overloaded operators
	//binary operators
	GNRMathVector3D operator+(const GNRMathVector3D & rhs) const
	{
		return GNRMathVector3D(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	
	GNRMathVector3D operator-(const GNRMathVector3D & rhs) const
	{
		return GNRMathVector3D(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	
	GNRMathVector3D operator*(const float rhs) const
	{
		return GNRMathVector3D(x*rhs, y*rhs, z*rhs);
	}
	
	GNRMathVector3D operator/(const float rhs) const
	{
		return (rhs==0.0f) ? GNRMathVector3D(0.0f, 0.0f, 0.0f) : GNRMathVector3D(x / rhs, y / rhs, z / rhs);
	}
	
	//multiply by a float, eg 3*v
	friend GNRMathVector3D operator*(float scaleFactor, const GNRMathVector3D & rhs);
	
	//Add, subtract etc, saving the construction of a temporary
	void Add(const GNRMathVector3D & v2, GNRMathVector3D & result)
	{
		result.x=x+v2.x;
		result.y=y+v2.y;
		result.z=z+v2.z;
	}
	
	void Subtract(const GNRMathVector3D & v2, GNRMathVector3D & result)
	{
		result.x=x-v2.x;
		result.y=y-v2.y;
		result.z=z-v2.z;
	}
	
	bool operator==(const GNRMathVector3D & rhs) const;
	bool operator!=(const GNRMathVector3D & rhs) const
	{
		return !((*this)==rhs);
	}
	
	//self-add etc
	void operator+=(const GNRMathVector3D & rhs)
	{
		x+=rhs.x;
		y+=rhs.y;
		z+=rhs.z;
	}
	
	void operator-=(const GNRMathVector3D & rhs)
	{
		x-=rhs.x;
		y-=rhs.y;
		z-=rhs.z;
	}
	
	void operator*=(const float rhs)
	{
		x*=rhs;
		y*=rhs;
		z*=rhs;
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
		}
	}
	
	
	//unary operators
	GNRMathVector3D operator-(void) const
	{
		return GNRMathVector3D(-x, -y, -z);
	}
	GNRMathVector3D operator+(void) const
	{
		return *this;
	}
	
	//cast to pointer to a (float *) for glVertex3fv etc
	operator float*() const
	{
		return (float*) this;
	}
	operator const float*() const
	{
		return (const float*) this;
	}
	
	//member variables
	float x;
	float y;
	float z;
};

#endif	//GNRMathVector3D_H