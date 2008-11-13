#include "Color.h"

#include <sstream>
#include <iostream>

using std::stringstream;
using std::endl;

Color::Color():
		// alpha == 1.0 => opaque, 0.0 => completely transparent
		m_r(0.5f), m_g(0.5f), m_b(0.5f), m_a(1.0f)
{
}

Color::Color(float r, float g, float b, float a):
		m_r(r), m_g(g), m_b(b), m_a(a)
{
}

Color::~Color()
{
}

void Color::getAll(float& r, float& g, float& b, float& a) const
{
	r = m_r;
	g = m_g;
	b = m_b;
	a = m_a;
}

void Color::getAll(float& r, float& g, float& b) const
{
	r = m_r;
	g = m_g;
	b = m_b;
}


void Color::setAll(float r, float g, float b, float a)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

void Color::setAll(float r, float g, float b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}

const float& Color::R() const
{
	return m_r;
}

const float& Color::G() const
{
	return m_g;
}

const float& Color::B() const
{
	return m_b;
}

const float& Color::A() const
{
	return m_a;
}

float& Color::R()
{
	return m_r;
}

float& Color::G()
{
	return m_g;
}

float& Color::B()
{
	return m_b;
}

float& Color::A()
{
	return m_a;
}

ostream& operator<< (ostream& out, const Color& c)
{
	out << c.m_r << " " << c.m_g << " " << c.m_b;
	return out;
}

