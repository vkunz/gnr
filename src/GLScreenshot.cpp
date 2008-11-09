/**
 * The GLScreenshot class implements the functionality to read out pixel-data
 * from the GL frame-buffer and save it into a picture-format supported by WX
 * @note        [DONE]
 * @name        GLScreenshot.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GLScreenshot.h"
#include <GL/gl.h>
#include <wx/filedlg.h>
#include <wx/image.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GLScreenshot
 * @param[in]       filename        Filename, the picture should be stored to
 */
GLScreenshot::GLScreenshot(wxString filename)
{
	//ctor
	m_filename = filename;
	m_bytesPerPixel = 3;  //RGB
	create();
}

/**
 * Read out pixels from GL and save it to a picture
 */
void GLScreenshot::create()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	// read out viewport-size
	m_width = viewport[2];
	m_height = viewport[3];
	
	const size_t imageSizeInBytes = m_bytesPerPixel * size_t(m_width) * size_t(m_height);
	
	// Allocate with malloc, because the data will be managed by wxImage
	unsigned char* pPicData = static_cast<unsigned char*>(malloc(imageSizeInBytes));
	
	// read pixels from GL
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, pPicData);
	
	swapPixels(pPicData);
	
	// create an image and save it
	wxImage mypic(m_width, m_height, pPicData);
	mypic.SaveFile(m_filename);
}

/**
 * Reverse pixels, given from bottom-left to top right by glReadPixels
 * @param[in]       pPicData      Pointer to picture-data-array
 */
void GLScreenshot::swapPixels(unsigned char* pPicData)
{
	for (int y = 0; y < m_height / 2; y++)
	{
		const int swapY = m_height - y - 1;
		for (int x = 0; x < m_width; x++)
		{
			const int offset = int(m_bytesPerPixel) * (x + y * m_width);
			const int swapOffset = int(m_bytesPerPixel) * (x + swapY * m_width);
			
			// Swap R, G and B of the 2 pixels
			std::swap(pPicData[offset + 0], pPicData[swapOffset + 0]);
			std::swap(pPicData[offset + 1], pPicData[swapOffset + 1]);
			std::swap(pPicData[offset + 2], pPicData[swapOffset + 2]);
		}
	}
}

/**
 * destructor of GLScreenshot
 */
GLScreenshot::~GLScreenshot()
{
	//dtor
}
