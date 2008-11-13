#ifndef __COLOR_H__
#define __COLOR_H__

#include <iostream>
#include <string>
using std::string;
using std::ostream;

class Color
{
public:
	friend ostream& operator<< (ostream& out, const Color& c);

	Color();
	Color(float r, float g, float b, float a = 1.0f);
	Color(const Color& other);

	virtual ~Color();

	void getAll(float& r, float& g, float& b, float& a) const;
	void getAll(float& r, float& g, float& b) const;
	const float& R() const;
	const float& G() const;
	const float& B() const;
	const float& A() const;

	void setAll(float r, float g, float b, float a);
	void setAll(float r, float g, float b);
	float& R();
	float& G();
	float& B();
	float& A();

    string getHex() const;

private:
	float m_r, m_g, m_b, m_a;
};

#endif

