/**
 * Material
 * @name        Material.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRMATERIAL_H_
#define _GNRMATERIAL_H_

#include <GL/gl.h>

#include "Material.h"

#include <string>
#include <map>

using std::string;
using std::map;

class Color
{
public:
	Color();
	Color(float r, float g, float b);
	Color(const Color& color);
	
	float getR() const;
	float getG() const;
	float getB() const;
	
	void  setR(float r);
	void  setG(float g);
	void  setB(float b);
	
	void getRGB(float& r, float& g, float& b) const;
	void setRGB(float r, float g, float b);
	
private:
	float  m_r, m_g, m_b;
};

class Material
{
public:
	Material();
	Material(const Material& material);
	~Material();
	
	const Color& getAmbient() const;
	const Color& getDiffuse() const;
	const Color& getSpecular() const;
	
	void setAmbient(float r, float g, float b);
	void setAmbient(const Color& c);
	void setDiffuse(float r, float g, float b);
	void setDiffuse(const Color& c);
	void setSpecular(float r, float g, float b);
	void setSpecular(const Color& c);
	
	const float& getAlpha() const;
	const int& getShininess() const;
	
	void setAlpha(float a);
	void setShininess(int s);
	
	void set() const;
	
private:
	Color m_ambient, m_diffuse, m_specular;
	float m_alpha;
	int m_shininess;
};

#endif // _GNRMATERIAL_H_
