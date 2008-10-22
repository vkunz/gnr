/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * obj file importer for reading and parsing obj-files
 * @name        GNRObjectImport.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNROBJECTIMPORT_H_
#define _GNROBJECTIMPORT_H_

#include "GNRAssembly.h"
#include "GNRImportFile.h"
#include "GNRVertex.h"
#include "GNRFace.h"

#include <string>
#include <fstream>

using std::ifstream;

class GNRObjectImport : public GNRImportFile
{
public:
	virtual GNRAssembly* read(const string& fname);
	virtual ~GNRObjectImport();
	
private:
	void getF();
	void getO();
	void getU();
	void getVs();
	void getV();
	void getVN();
	void getVT();
	
	vector<GNRVertex> m_vertex, m_normal;
	vector<GNRTCoord> m_tcoord;
	string m_matname;
	
	GNRAssembly* m_root, *m_act;
	
	ifstream m_ifs;
	string m_buf;
	
	float m_xmin, m_xmax, m_ymin, m_ymax, m_zmin, m_zmax;
};

#endif // _GNROBJECTIMPORT_H_
