#ifndef __MATERIAL_LIB__H__
#define __MATERIAL_LIB__H__

#include "Material.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using std::istream;
using std::iostream;
using std::ifstream;
using std::string;
using std::map;
using std::pair;

class MaterialLibrary
{
public:
	friend ostream& operator<< (ostream& out, const MaterialLibrary& m);
	
	typedef map<string, Material> matlib_type;
	typedef matlib_type::const_iterator mat_citer;
	
	static MaterialLibrary* getInstance();
	static void destroy();
	
	mat_citer get(const string& name) const;
	
	void insert(const string& name, const Material& mat);
	void insert(const Color color);
	
	void import(const string& fname);
	void import(istream& is);
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
	
	string m_buf, m_matname;
	Material* m_material;
	istream* m_is;
};

#endif

