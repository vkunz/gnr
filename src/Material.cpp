/**
 * Material
 * @name        Material.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "Material.h"

#include <GL/gl.h>

#include <iostream>
using std::cout;
using std::endl;

Color::Color():
		m_r(1.0), m_g(1.0), m_b(1.0)
{
}

Color::Color(float r, float g, float b):
		m_r(r), m_g(g), m_b(b)
{
}

Color::Color(const Color& color)
{
	m_r = color.m_r;
	m_g = color.m_g;
	m_b = color.m_b;
}

float Color::getR() const
{
	return m_r;
}
float Color::getG() const
{
	return m_g;
}

float Color::getB() const
{
	return m_b;
}

void Color::setRGB(float r, float g, float b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}

void Color::setR(float r)
{
	m_r = r;
}

void Color::setG(float g)
{
	m_g = g;
}

void Color::setB(float b)
{
	m_b = b;
}

Material::Material():
		m_ambient(0.8, 0.8, 0.8), m_diffuse(0.8, 0.8, 0.8), m_specular(0.5, 0.5, 0.5),
		m_alpha(0.0), m_shininess(0)
{
}

Material::Material(const Material& material)
{
	m_ambient   = material.m_ambient;
	m_diffuse   = material.m_diffuse;
	m_specular  = material.m_specular;
	m_alpha     = material.m_alpha;
	m_shininess = material.m_shininess;
}

const Color& Material::getAmbient() const
{
	return m_ambient;
}

const Color& Material::getDiffuse() const
{
	return m_diffuse;
}

const Color& Material::getSpecular() const
{
	return m_specular;
}

const float& Material::getAlpha() const
{
	return m_alpha;
}

const int& Material::getShininess() const
{
	return m_shininess;
}

void Material::setAmbient(float r, float g, float b)
{
	m_ambient.setRGB(r, g, b);
}

void Material::setDiffuse(float r, float g, float b)
{
	m_diffuse.setRGB(r, g, b);
}

void Material::setSpecular(float r, float g, float b)
{
	m_specular.setRGB(r, g, b);
}

void Material::setAlpha(float a)
{
	m_alpha = a;
}

void Material::setShininess(int s)
{
	m_shininess = s;
}

void Material::set() const
{
// While the ambient, diffuse, specular and emission material parameters
// all have alpha components, only the diffuse alpha component is used in
// the lighting computation.

	float mat[4];
	mat[3] = m_alpha;
	
	mat[0] = m_ambient.getR();
	mat[1] = m_ambient.getG();
	mat[2] = m_ambient.getB();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	
	mat[0] = m_diffuse.getR();
	mat[1] = m_diffuse.getG();
	mat[2] = m_diffuse.getB();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	
	mat[0] = m_specular.getR();
	mat[1] = m_specular.getG();
	mat[2] = m_specular.getB();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	
	glMateriali(GL_FRONT, GL_SHININESS, m_shininess);
}

Material::~Material()
{
}
