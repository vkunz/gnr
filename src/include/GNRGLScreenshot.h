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
