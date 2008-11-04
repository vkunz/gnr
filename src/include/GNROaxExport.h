/**
 * GNROaxExport
 * @name        GNROaxExport
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNROAXEXPORT_H_
#define _GNROAXEXPORT_H_

#include <wx/wfstream.h>
#include <wx/xml/xml.h>
#include <wx/zipstrm.h>

#include "GNRAssembly.h"
#include "GNRAssemblyData.h"
#include "GNROaxExport.h"

class GNROaxExport
{
public:

	// ctor
	GNROaxExport(GNRAssemblyData* data);
	
	GNROaxExport(GNRAssembly* assembly);
	
	// dtor
	virtual ~GNROaxExport();
	
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
	GNRAssemblyData* m_assemblyData;
	
	// pointer to wxZipOutputStream
	wxZipOutputStream* m_outZip;
	
	// pointer to wxOutputStream
	wxFFileOutputStream* m_outStream;
	
	// functions
	// create xml zip entry
	void createXmlEntry();
	
	// create oax zip outputstream
	void createOaxStream();
};

#endif // _GNROAXEXPORT_H_
