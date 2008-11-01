/**
 * defines the glscreenshot class
 * @name        GNRGLScreenshot.h
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGLSCREENSHOT_H_
#define _GNRGLSCREENSHOT_H_

#include <wx/string.h>

class GNRGLScreenshot
{
public:
	GNRGLScreenshot(wxString filename);
	virtual ~GNRGLScreenshot();
protected:
private:
	wxString m_filename;
	int m_width;
	int m_height;
	size_t m_bytesPerPixel;
	
	void create();
	void swapPixels(unsigned char* pPicData);
};

#endif // _GNRGLSCREENSHOT_H_
