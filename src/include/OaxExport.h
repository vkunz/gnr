/**
 * OaxExport
 * @name        OaxExport
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _OAXEXPORT_H_
#define _OAXEXPORT_H_

#include <wx/wfstream.h>
#include <wx/xml/xml.h>
#include <wx/zipstrm.h>

class AssemblyData;

class OaxExport
{
public:

	// ctor
	OaxExport(AssemblyData* data, wxOutputStream* outStream);

	// dtor
	virtual ~OaxExport();

protected:

private:
	// attributes
	bool m_saveToFileSystem;

	// create pointer to xmlnode
	wxXmlNode* m_node;

	// create pointer to xmlnode to store actual parent
	wxXmlNode* m_actual;

	// create pointer to xmlproperty
	wxXmlProperty* m_prop;

	// container to store data
	AssemblyData* m_assemblyData;

	// pointer to wxZipOutputStream
	wxZipOutputStream* m_outZip;

	// pointer to wxOutputStream
	wxOutputStream* m_outStream;

	// functions
	// create xml zip entry
	void createXmlEntry();

	// create oax zip outputstream
	void createOaxStream();
};

#endif // _OAXEXPORT_H_
