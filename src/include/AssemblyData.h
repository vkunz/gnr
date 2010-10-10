/**
 * FrameData
 * @name        FrameData.h
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _FRAMEDATA_H_
#define _FRAMEDATA_H_

#include <list>
//#include <wx/string.h>

struct AssemblyData
{
	wxString m_name;
	wxString m_category;
	unsigned int m_category_id;

	double m_width;
	double m_depth;
	double m_height;

	double m_scaleWidth;
	double m_scaleDepth;
	double m_scaleHeight;

	double m_offsetX;
	double m_offsetY;
	double m_offsetZ;

	std::list<wxString> m_listFiles;
	std::list<wxString> m_tags;
};

#endif // _FRAMEDATA_H_
