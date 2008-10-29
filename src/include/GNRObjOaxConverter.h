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

#include <wx/string.h>

#include "GNRGLCanvasPreview.h"
#include "GNRObjOaxConverterFrame.h"

class GNRObjOaxConverter
{
public:
	// ctor
	GNRObjOaxConverter(wxString filename);
	
	// dtor
	virtual ~GNRObjOaxConverter();
	
protected:

private:
	// attributes
	// Frame
	GNRObjOaxConverterFrame* m_frame;
	
	// functions
	// initialize gui
	void initFrame();
};

#endif // _GNROBJOAXCONVERTER_H_
