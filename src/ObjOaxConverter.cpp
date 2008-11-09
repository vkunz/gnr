/**
 * ObjOaxConverter
 * @name        ObjOaxConverter.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <vector>
#include <wx/string.h>

#include "ObjectImport.h"
#include "ObjOaxConverter.h"

// ctor
ObjOaxConverter::ObjOaxConverter(wxString filename, std::vector<wxString>* ptrVec)
{
	// asign ptrVec
	m_ptrVec = ptrVec;
	
	// load ObjectImporter
	Load(filename);
	
	// init Frame
	initFrame();
}

// dtor
ObjOaxConverter::~ObjOaxConverter()
{
	delete m_frame;
}

void ObjOaxConverter::initFrame()
{
	// create frame
	m_frame = new ObjOaxConverterFrame(0);
	m_frame->Show(true);
	
	// fillFrame
	fillFrame();
}

void ObjOaxConverter::fillFrame()
{
	// set frameData
	m_frame->setAssemblyData(m_assemblyData);
	
	// setData
	m_frame->setData();
	
	// get canvas
	m_canvas = m_frame->getCanvasPointer();
	
	// set assembly into canvas
	m_canvas->setAssembly(m_assembly);
	
	// reshape canvas to adjust viewport
	m_canvas->reshape();
	
	// draw the assembly
	m_canvas->draw();
	
	// set categories
	m_frame->setAllCategories(m_ptrVec);
}

void ObjOaxConverter::Load(wxString filename)
{
	// create ObjectImporter - object
	ObjectImport import(filename);
	
	// get Assembly
	m_assembly = import.getAssembly();
	
	// create new FrameData
	m_assemblyData = new AssemblyData();
	
	// get x - offset and store into frameData
	m_assemblyData->m_offsetX = import.getOffsetX();
	
	// get y - offset and store into frameData
	m_assemblyData->m_offsetY = import.getOffsetY();
	
	// get z - offset and store into frameData
	m_assemblyData->m_offsetZ = import.getOffsetZ();
	
	// tmp list
	std::list<wxString> list;
	
	// temp iterator
	std::list<wxString>::iterator it;
	
	// get FileList
	list = import.getFileList();
	
	// get all files from ObjectImport -> m_listFiles and stor to FrameData -> m_listFiles
	for (it = list.begin(); it != list.end(); it++)
	{
		m_assemblyData->m_listFiles.push_back(*it);
	}
	
	// set one tag
	m_assemblyData->m_tags.push_back(wxT("gnr"));
	
	// set name
	m_assemblyData->m_name = wxString(m_assembly->getName().c_str(), wxConvUTF8);
	
	// set width
	m_assemblyData->m_width = (int)(m_assembly->getWidth() * 1000.0);
	
	// set depth
	m_assemblyData->m_depth = (int)(m_assembly->getDepth() * 1000.0);
	
	// set heigh
	m_assemblyData->m_height = (int)(m_assembly->getHeight() * 1000.0);
}
