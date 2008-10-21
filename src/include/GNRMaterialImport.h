/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRMaterialImport
 * @name        GNRMaterialImport.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRMATERIALIMPORT_H_
#define _GNRMATERIALIMPORT_H_

#include "GNRMaterial.h"

#include <map>
#include <string>
#include <fstream>

using std::map;
using std::string;
using std::ifstream;

class GNRMaterialImport
{
public:
	GNRMatLib* read(const string& fname);
	
private:
	bool getData();
	bool getName();
	void parseData();
	
	ifstream m_ifs;
	string m_buf;
	
	GNRMatLib* m_root;
	string m_matname;
	GNRMaterial* m_material;
};

#endif // _GNRMATERIALIMPORT_H_
