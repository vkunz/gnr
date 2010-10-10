/**
 * MaterialLibrary
 * @name        MaterialLibrary.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _MATERIALLIBRARY_H_
#define _MATERIALLIBRARY_H_

#include <iostream>
#include <string>
#include <map>

class Color;
class Material;

class MaterialLibrary
{
public:
	friend std::ostream& operator<< (std::ostream& out, const MaterialLibrary& m);

	typedef std::map<std::string, Material> matlib_type;
	typedef matlib_type::const_iterator mat_citer;

	static MaterialLibrary* getInstance();
	static void destroy();

	mat_citer get(const std::string& name) const;

	void insert(const std::string& name, const Material& mat);
	void insert(const Color color);

	void import(const std::string& fname);
	void import(std::istream& is);
	mat_citer end() const;

private:
	matlib_type m_lib;

	// avoid unwanted things
	MaterialLibrary();
	MaterialLibrary(const MaterialLibrary& other);
	~MaterialLibrary();

	static MaterialLibrary* instance;

	bool getName();
	bool getData();
	void parseData();

	std::string m_buf, m_matname;
	Material* m_material;
	std::istream* m_is;
};

#endif // _MATERIALLIBRARY_H_
