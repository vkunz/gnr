/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRMaterial
 * @name        GNRMaterial.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRMaterial.h"

#include <GL/gl.h>

#include <iostream>

using std::cout;
using std::endl;

GNRColor::GNRColor(float r, float g, float b):
		m_r(r), m_g(g), m_b(b)
{
}

float GNRColor::getR() const
{
	return m_r;
}
float GNRColor::getG() const
{
	return m_g;
}

float GNRColor::getB() const
{
	return m_b;
}

void GNRColor::setRGB(float r, float g, float b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}

void GNRColor::setR(float r)
{
	m_r = r;
}

void GNRColor::setG(float g)
{
	m_g = g;
}

void GNRColor::setB(float b)
{
	m_b = b;
}

GNRMaterial::GNRMaterial():
		m_ambient(0.2, 0.2, 0.2), m_diffuse(0.8, 0.8, 0.8), m_specular(0.0, 0.0, 0.0),
		m_alpha(1.0), m_shininess(0.0)
{
}

const GNRColor& GNRMaterial::getAmbient() const
{
	return m_ambient;
}

const GNRColor& GNRMaterial::getDiffuse() const
{
	return m_diffuse;
}

const GNRColor& GNRMaterial::getSpecular() const
{
	return m_specular;
}

const float& GNRMaterial::getAlpha() const
{
	return m_alpha;
}

const float& GNRMaterial::getShininess() const
{
	return m_shininess;
}

void GNRMaterial::setAmbient(float r, float g, float b)
{
	m_ambient.setRGB(r, g, b);
}

void GNRMaterial::setDiffuse(float r, float g, float b)
{
	m_diffuse.setRGB(r, g, b);
}

void GNRMaterial::setSpecular(float r, float g, float b)
{
	m_specular.setRGB(r, g, b);
}

void GNRMaterial::setAlpha(float a)
{
	m_alpha = a;
}

void GNRMaterial::setShininess(float s)
{
	m_shininess = s;
}

void GNRMaterial::draw() const
{
	float mat[4];
	mat[3] = m_alpha;
	
	mat[0] = m_ambient.getR();
	mat[1] = m_ambient.getG();
	mat[2] = m_ambient.getB();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
//    cout << "ambient: " << mat[0] << " " << mat[1] << " " << mat[2] << endl;

	mat[0] = m_diffuse.getR();
	mat[1] = m_diffuse.getG();
	mat[2] = m_diffuse.getB();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
//    cout << "diffuse: " << mat[0] << " " << mat[1] << " " << mat[2] << endl;

	mat[0] = m_specular.getR();
	mat[1] = m_specular.getG();
	mat[2] = m_specular.getB();
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
//    cout << "specular: " << mat[0] << " " << mat[1] << " " << mat[2] << endl;


	glMateriali(GL_FRONT, GL_SHININESS, m_shininess);
}

