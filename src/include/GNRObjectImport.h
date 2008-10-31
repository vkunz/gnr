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

#include <map>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>

#include "GNRAssembly.h"
#include "GNRImportFile.h"
#include "GNRVertex.h"

#include <string>
#include <fstream>

using std::ifstream;

class GNRObjectImport : public GNRImportFile
{
public:
	// ctor
	GNRObjectImport();
	GNRObjectImport(wxString filename);
	GNRObjectImport(wxInputStream* inStream, std::map<wxString, wxString>* mtl);
	
	// dtor
	virtual ~GNRObjectImport();
	
	virtual GNRAssembly* read(const string& fname);
	
	void read(wxString& content);
	
	GNRAssembly* getAssembly();
	
private:
	// attributes
	// set if load from filesystem, else load as wxinputstream
	bool m_AsString;
	
	// wxString to store the filepath
	wxString m_path;
	
	// wxString to store current line
	wxString m_line;
	
	// pointer to map, where mtl and textures are stored in
	std::map<wxString, wxString>* m_mtl;
	
	// pointer to GNRAssembly
	GNRAssembly* m_root;
	
	// pointer to actual GNRAssembly
	GNRAssembly* m_act;
	
	// pointer to GNRAssembly - wrapper
	GNRAssembly* m_wrapper;
	
	// functions
	// parse string
	void Parse(wxString& file);
	
	// LoadMtl
	void LoadMtl();
	
	// parse material
	void ParseMtl(wxString& mtl);
	
	void getF();
	void getO();
	void getU();
	void getVs();
	void getV();
	void getVN();
	void getVT();
	
	void minmax(float& min,float& max,float value);
	void addAtomic(string name);
	
	vector<GNRVertex> m_vertex, m_normal;
	vector<GNRTCoord> m_tcoord;
	string m_matname;
	
	ifstream m_ifs;
	string m_buf;
	
	float m_xmin, m_xmax, m_ymin, m_ymax, m_zmin, m_zmax;
};

#endif // _GNROBJECTIMPORT_H_
