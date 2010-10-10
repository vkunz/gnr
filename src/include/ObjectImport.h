/**
 * obj file importer for reading and parsing obj-files
 * @name        ObjectImport.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _OBJECTIMPORT_H_
#define _OBJECTIMPORT_H_

#include <fstream>
#include <map>
#include <string>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>
#include <wx/filename.h>

#include "ImportFile.h"
#include "Vertex.h"

class Face;

class ObjectImport : public ImportFile
{
public:
	// ctor
	ObjectImport();
	// parse the file filename,
	// I have to fill the datastructure with the mtl's and textures read
	ObjectImport(const wxString& filename);
	// parse the stream inStream, all the mtl's and textures are in the map
	ObjectImport(wxInputStream* inStream, std::map<wxString, wxString>* mtl);

	// dtor
	virtual ~ObjectImport();

	// return filelist
	std::list<wxString> getFileList();

	// return assembly
	Assembly* getAssembly();

	const Vertex& offset() const;

	// return wrapper
	Assembly* getWrapper();

private:
	// pointer to the new Assembly, its wrapper and an actual Assembly
	Assembly *m_root, *m_wrapper, *m_act_part;

	// offset needed to put the midpoint of the Obj to the Origin
	// (makes rotation more meaningfull)
	Vertex m_offset;

	// min-max ranges for X-, Y-, and Z- dimension.
	Vertex m_min, m_max;

	// set if parsing an existing file from FS,
	// else parse wxinputstream
	bool m_from_FS;

	// get filepath
	wxFileName file;

	// wxString to store the filepath
	wxString m_path;

	// list of files which are needed by .obj-file
	std::list<wxString> m_listFiles;

	// pointer to map, where mtl and textures are stored in
	std::map<wxString, wxString>* m_mtl;

	// parse content and create assembly
	void parse(const wxString& content);

	void getO();
	void getF();
	void getU();
	void getVs();
	void getV();
	void getVN();
	void getM();

	Face* getFace(std::istream& is);

	void minmax(float x, float y, float z);
	void addAtomic(const std::string& name);

	std::string m_act_material;

	std::ifstream m_ifs;
	std::string m_buf;
};

#endif // _OBJECTIMPORT_H_
