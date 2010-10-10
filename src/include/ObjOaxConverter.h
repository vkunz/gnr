/**
 * ObjOaxConverter
 * @name        ObjOaxConverter.h
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _OBJOAXCONVERTER_H_
#define _OBJOAXCONVERTER_H_

#include <vector>
#include <wx/string.h>

#include "GlobalDefine.h"

class Assembly;
class AssemblyData;
class GLCanvas;
class GLCanvasPreview;
class ObjOaxConverterFrame;

class ObjOaxConverter
{
public:
	// ctor
	ObjOaxConverter(wxString filename);

	// dtor
	virtual ~ObjOaxConverter();

protected:

private:
	// attributes
	// Frame
	ObjOaxConverterFrame* m_frame;

	// pointer to Assembly
	Assembly* m_assembly;

	// pointer to frameData
	AssemblyData* m_assemblyData;

	// pointer to canvas
	GLCanvasPreview* m_canvas;

	// functions
	// initialize gui
	void initFrame();

	// fill frame with data
	void fillFrame();

	// load ObjectImporter
	void Load(wxString filename);
};

#endif // _OBJOAXCONVERTER_H_
