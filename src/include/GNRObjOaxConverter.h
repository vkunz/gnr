/**
 * GNRObjOaxConverter
 * @name        GNRObjOaxConverter.h
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNROBJOAXCONVERTER_H_
#define _GNROBJOAXCONVERTER_H_

#include <vector>
#include <wx/string.h>

#include "GNRGLCanvasPreview.h"
#include "GNRObjOaxConverterFrame.h"

class GNRObjOaxConverter
{
public:
	// ctor
	GNRObjOaxConverter(wxString filename, std::vector<wxString>* ptrVec);
	
	// dtor
	virtual ~GNRObjOaxConverter();
	
protected:

private:
	// attributes
	// Frame
	GNRObjOaxConverterFrame* m_frame;
	
	// pointer to GNRAssembly
	GNRAssembly* m_assembly;
	
	// pointer to frameData
	GNRAssemblyData* m_assemblyData;
	
	// vector to pointer of all categories
	std::vector<wxString>* m_ptrVec;
	
	// pointer to canvas
	GNRGLCanvasPreview* m_canvas;
	
	// map to store Data needed by m_frame
	//std::map<wxString, wxString>* m_ptrMap;
	
	// functions
	// initialize gui
	void initFrame();
	
	// fill frame with data
	void fillFrame();
	
	// load ObjectImporter
	void Load(wxString filename);
};

#endif // _GNROBJOAXCONVERTER_H_
