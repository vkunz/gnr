/**
 * GNRObjOaxConverter
 * @name        GNRObjOaxConverter.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <vector>
#include <wx/string.h>

#include "GNRObjectImport.h"
#include "GNRObjOaxConverter.h"

// ctor
GNRObjOaxConverter::GNRObjOaxConverter(wxString filename, std::vector<wxString>* ptrVec)
{
	// asign ptrVec
	m_ptrVec = ptrVec;
	
	// load ObjectImporter
	Load(filename);
	
	// init Frame
	initFrame();
}

// dtor
GNRObjOaxConverter::~GNRObjOaxConverter()
{
	delete m_frame;
}

void GNRObjOaxConverter::initFrame()
{
	// create frame
	m_frame = new GNRObjOaxConverterFrame(0);
	m_frame->Show(true);
	
	// fillFrame
	fillFrame();
}

void GNRObjOaxConverter::fillFrame()
{
	// set frameData
	m_frame->setFrameData(m_frameData);
	
	// setData
	m_frame->setData();
	
	// get canvas
	m_canvas = m_frame->getCanvasPointer();
	
	// set assembly into canvas
	m_canvas->setAssembly(m_assembly);
	
	// set categories
	m_frame->setAllCategories(m_ptrVec);
}

void GNRObjOaxConverter::Load(wxString filename)
{
	// create ObjectImporter - object
	GNRObjectImport import(filename);
	
	// get Assembly
	m_assembly = import.getAssembly();
	
	// create new FrameData
	m_frameData = new GNRFrameData();
	
	// get x - offset and store into frameData
	m_frameData->m_offsetX = import.getOffsetX();
	
	// get y - offset and store into frameData
	m_frameData->m_offsetY = import.getOffsetY();
	
	// get z - offset and store into frameData
	m_frameData->m_offsetZ = import.getOffsetZ();
	
	// tmp list
	std::list<wxString> list;
	
	// temp iterator
	std::list<wxString>::iterator it;
	
	// get list
	list = import.getFileList();
	
	// get all files from GNRObjectImport -> m_listFiles and stor to GNRFrameData -> m_listFiles
	for (it = list.begin(); it != list.end(); it++)
	{
		m_frameData->m_listFiles.push_back(*it);
	}
	
	// set name
	m_frameData->m_name = wxString(m_assembly->getName().c_str(), wxConvUTF8);
	
	// set width
	m_frameData->m_width = (int)(m_assembly->getWidth() * 1000);
	
	// set depth
	m_frameData->m_depth = (int)(m_assembly->getDepth() * 1000);
	
	// set heigh
	m_frameData->m_height = (int)(m_assembly->getHeight() * 1000);
}
