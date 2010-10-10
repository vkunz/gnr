/**
 * Material
 * @name                Material.h
 * @date                2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <iostream>
#include <string>

#include "Color.h"

class Material
{
public:
	friend std::ostream& operator<<(std::ostream& out, const Material &m);

	Material();
	Material(const Material& other);
	virtual ~Material();

	const Color& Ambient() const;
	const Color& Diffuse() const;
	const Color& Specular() const;

	Color& Ambient();
	Color& Diffuse();
	Color& Specular();

	const int& Shininess() const;
	int& Shininess();

	const float& Alpha() const;
	float& Alpha();

	void set() const;

private:
	Color m_ambient, m_diffuse, m_specular;
	int m_shininess;
	float m_alpha;
};

#endif
