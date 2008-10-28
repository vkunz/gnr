/**
 * GNRMaterialLibrary
 * @name        GNRMaterialLibrary.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef __GNRMATERIALLIBRARY_H__
#define __GNRMATERIALLIBRARY_H__

#include "GNRMaterial.h"

#include <map>
#include <string>
#include <iostream>

using std::map;
using std::string;

using std::istream;

class GNRMaterialLibrary
{
public:
	GNRMaterialLibrary();
	
	void importFile(const string& fname);
	
	void import(istream& is);
	
	void selectMaterial(const string& matname) const;
	
	const GNRMaterial& getMaterial(const string& matname) const;
	
private:
	bool getName();
	bool getData();
	void parseData();
	
	map<string, GNRMaterial> m_data;
	
	GNRMaterial* m_material;
	string m_buf, m_matname;
	istream* m_is;
};

#endif
