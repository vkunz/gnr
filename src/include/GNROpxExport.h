/**
 * GNROpxExport
 * @name        GNROpxExport.h
 * @date        2008-11-02
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNROPXEXPORT_H_
#define _GNROPXEXPORT_H_

#include <wx/string.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>
#include <wx/zipstrm.h>

#include "GNRScene.h"

class GNROpxExport
{
public:
	// ctor
	GNROpxExport();
	
	GNROpxExport(GNRScene* scene, wxString filename);
	
	// dtor
	virtual ~GNROpxExport();
	
protected:

private:
	// attributes
	// pointer to scene
	GNRScene* m_scene;
	
	// create pointer to xmlnode
	wxXmlNode* m_node;
	
	// create pointer to xmlnode to store actual parent
	wxXmlNode* m_actual;
	
	// create pointer to xmlproperty
	wxXmlProperty* m_prop;
	
	// pointer to wxZipOutputStream
	wxZipOutputStream* m_outZip;
	
	// pointer to wxOutputStream
	wxFFileOutputStream* m_outStream;
	
	// functions
	// create xml zip entry
	void createXmlEntry();
	
	// create oax zip outputstream
	void createOpxStream();
};

#endif // _GNROPXEXPORT_H_
