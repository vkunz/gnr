#ifndef GNRMathVector2D_H
#define GNRMathVector2D_H

class GNRMathVector2D
{
public:
	//constructors
	GNRMathVector2D(void)	:	x(0.0f), y(0.0f)
	{}
	
	GNRMathVector2D(float newX, float newY):	x(newX), y(newY)
	{}
	
	GNRMathVector2D(const float * rhs)		:	x(*rhs), y((*rhs)+1)
	{}
	
	GNRMathVector2D(const GNRMathVector2D & rhs)	:	x(rhs.x), y(rhs.y)
	{}
	
	~GNRMathVector2D() {}	//empty
	
	void Set(float newX, float newY)
	{
		x=newX;
		y=newY;
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
	
	float GetX() const
	{
		return x;    //public accessor functions
	}
	float GetY() const
	{
		return y;    //inline, const
	}
	
	void LoadZero(void);
	void LoadOne(void);					//fill with (1, 1)
	
	void Normalize();
	GNRMathVector2D GetNormalized() const;
	
	float GetLength() const
	{
		return (float)sqrt((x*x)+(y*y));
	}
	
	float GetSquaredLength() const
	{
		return (x*x)+(y*y);
	}
	
	//linear interpolate
	GNRMathVector2D lerp(const GNRMathVector2D & v2, float factor) const
	{
		return (*this)*(1.0f-factor) + v2*factor;
	}
	
	GNRMathVector2D QuadraticInterpolate(const GNRMathVector2D & v2, const GNRMathVector2D & v3, float factor) const
	{
		return (*this)*(1.0f-factor)*(1.0f-factor) + 2*v2*factor*(1.0f-factor) + v3*factor*factor;
	}
	
	//overloaded operators
	//binary operators
	GNRMathVector2D operator+(const GNRMathVector2D & rhs) const
	{
		return GNRMathVector2D(x + rhs.x, y + rhs.y);
	}
	
	GNRMathVector2D operator-(const GNRMathVector2D & rhs) const
	{
		return GNRMathVector2D(x - rhs.x, y - rhs.y);
	}
	
	GNRMathVector2D operator*(const float rhs) const
	{
		return GNRMathVector2D(x*rhs, y*rhs);
	}
	
	GNRMathVector2D operator/(const float rhs) const
	{
		return (rhs==0) ? GNRMathVector2D(0.0f, 0.0f) : GNRMathVector2D(x / rhs, y / rhs);
	}
	
	//multiply by a float, eg 3*v
	friend GNRMathVector2D operator*(float scaleFactor, const GNRMathVector2D & rhs);
	
	bool operator==(const GNRMathVector2D & rhs) const;
	bool operator!=(const GNRMathVector2D & rhs) const
	{
		return !((*this)==rhs);
	}
	
	//self-add etc
	void operator+=(const GNRMathVector2D & rhs)
	{
		x+=rhs.x;
		y+=rhs.y;
	}
	
	void operator-=(const GNRMathVector2D & rhs)
	{
		x-=rhs.x;
		y-=rhs.y;
	}
	
	void operator*=(const float rhs)
	{
		x*=rhs;
		y*=rhs;
	}
	
	void operator/=(const float rhs)
	{
		if (rhs==0.0f)
			return;
		else
		{
			x/=rhs;
			y/=rhs;
		}
	}
	
	
	//unary operators
	GNRMathVector2D operator-(void) const
	{
		return GNRMathVector2D(-x, -y);
	}
	GNRMathVector2D operator+(void) const
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
};

#endif	//GNRMathVector2D_H