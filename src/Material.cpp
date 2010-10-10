/**
 * Material
 * @name        Material.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <sstream>
#include <iostream>
#include <GL/gl.h>

#include "Material.h"

Material::Material():
		m_shininess(80), m_alpha(1.0f)
{
}

Material::Material(const Material& other)
{
	m_ambient = other.m_ambient;
	m_diffuse = other.m_diffuse;
	m_specular = other.m_specular;
	m_shininess = other.m_shininess;
	m_alpha = other.m_alpha;
}

Material::~Material()
{
}

const Color& Material::Ambient() const
{
	return m_ambient;
}

const Color& Material::Diffuse() const
{
	return m_diffuse;
}

const Color& Material::Specular() const
{
	return m_specular;
}

Color& Material::Ambient()
{
	return m_ambient;
}

Color& Material::Diffuse()
{
	return m_diffuse;
}

Color& Material::Specular()
{
	return m_specular;
}

const int& Material::Shininess() const
{
	return m_shininess;
}

int& Material::Shininess()
{
	return m_shininess;
}

const float& Material::Alpha() const
{
	return m_alpha;
}

float& Material::Alpha()
{
	return m_alpha;
}

void Material::set() const
{
	float val[4];
	val[3] = 1.0-m_alpha;

	m_ambient.getAll(val[0], val[1], val[2]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, val);

	m_diffuse.getAll(val[0], val[1], val[2]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, val);

	m_specular.getAll(val[0], val[1], val[2]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, val);

	glMateriali(GL_FRONT, GL_SHININESS, m_shininess);
}

std::ostream& operator<<(std::ostream& out, const Material &m)
{
	out << "Ka " << m.m_ambient << std::endl;
	out << "Kd " << m.m_diffuse << std::endl;
	out << "Ks " << m.m_specular << std::endl;
	out << "d " << m.m_alpha << std::endl;
	out << "Ns " << m.m_shininess << std::endl;

	return out;
}
