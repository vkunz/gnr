/**
 * obj file importer for reading and parsing obj-files
 * @name        ObjectImport.h
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

#include "Assembly.h"
#include "ImportFile.h"
#include "Vertex.h"
#include "MaterialLibrary.h"

#include <string>
#include <fstream>

using std::ifstream;

class ObjectImport : public ImportFile
{
public:
	// ctor
	ObjectImport();
	ObjectImport(const wxString& filename);
	ObjectImport(wxInputStream* inStream, std::map<wxString, wxString>* mtl);
	
	// dtor
	virtual ~ObjectImport();
	
	// return filelist
	std::list<wxString> getFileList();
	
	// return assembly
	Assembly* getAssembly();
	
	// return x - offset
	float getOffsetX();
	
	// return y - offset
	float getOffsetY();
	
	// return z - offset
	float getOffsetZ();
	
	// return wrapper
	Assembly* getWrapper();
	
private:

	//access to default values
	MaterialLibrary m_matlib;
	
	// attributes
	// set if load from filesystem, else load as wxinputstream
	bool m_AsString;
	
	// wxString to store the filepath
	wxString m_path;
	
	// list of files which are needed by .obj-file
	std::list<wxString> m_listFiles;
	
	// pointer to map, where mtl and textures are stored in
	std::map<wxString, wxString>* m_mtl;
	
	// pointer to Assembly
	Assembly* m_root;
	
	// pointer to actual Assembly
	Assembly* m_act;
	
	// pointer to Assembly - wrapper
	Assembly* m_wrapper;
	
	// double to store the x - offfset
	float m_offsetX;
	
	// double to store the x - offfset
	float m_offsetY;
	
	// double to store the x - offfset
	float m_offsetZ;
	
	// functions
	// LoadMtl
	void LoadMtl();
	
	// parse material
	void ParseMtl(wxString& mtl);
	
	// read content and create assembly
	void read(const wxString& content);
	
	void getF();
	void getO();
	void getU();
	void getVs();
	void getV();
	void getVN();
	void getVT();
	
	void minmax(float& min,float& max,float value);
	void addAtomic(const string& name);
	
	vector<Vertex> m_vertex, m_normal;
	vector<TCoord> m_tcoord;
	string m_matname;
	
	ifstream m_ifs;
	string m_buf;
	
	float m_xmin, m_xmax, m_ymin, m_ymax, m_zmin, m_zmax;
};

#endif // _GNROBJECTIMPORT_H_
