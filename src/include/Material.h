#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Color.h"

#include <string>

using std::string;

class Material
{
public:
	friend ostream& operator<< (ostream& out, const Material &m);
	
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
