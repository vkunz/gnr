/**
 * GNRObjOaxConverter
 * @name        GNRObjOaxConverter.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRObjOaxConverter.h"

// ctor
GNRObjOaxConverter::GNRObjOaxConverter(wxString filename)
{
	// init Frame
	initFrame();
}

// dtor
GNRObjOaxConverter::~GNRObjOaxConverter()
{
	// do nothing
}

void GNRObjOaxConverter::initFrame()
{
	// create frame
	m_frame = new GNRObjOaxConverterFrame(0);
	m_frame->Show(true);
}
