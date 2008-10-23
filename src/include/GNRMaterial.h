/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRMaterial
 * @name        GNRMaterial.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRMATERIAL_H_
#define _GNRMATERIAL_H_

#include "GNRMaterial.h"

#include <string>
#include <map>

using std::string;
using std::map;

class GNRColor
{
public:
	GNRColor(float r, float g, float b);
	
	float getR() const;
	float getG() const;
	float getB() const;
	
	void  setR(float r);
	void  setG(float g);
	void  setB(float b);
	
	void getRGB(float&r, float& g, float& b) const;
	void setRGB(float r, float g, float b);
	
private:
	float  m_r, m_g, m_b;
};

class GNRMaterial
{
public:
	GNRMaterial();
	
	const GNRColor& getAmbient() const;
	const GNRColor& getDiffuse() const;
	const GNRColor& getSpecular() const;
	
	void setAmbient(float r, float g, float b);
	void setAmbient(const GNRColor& c);
	void setDiffuse(float r, float g, float b);
	void setDiffuse(const GNRColor& c);
	void setSpecular(float r, float g, float b);
	void setSpecular(const GNRColor& c);
	
	const float& getAlpha() const;
	const float& getShininess() const;
	
	void setAlpha(float a);
	void setShininess(float s);
	
	void draw() const;
	
private:
	GNRColor m_ambient, m_diffuse, m_specular;
	float m_alpha;
	float m_shininess;
};

#endif // _GNRMATERIAL_H_
