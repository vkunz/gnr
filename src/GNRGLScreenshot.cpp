#include "GNRGLScreenshot.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <wx/filedlg.h>
#include <wx/image.h>
#include <wx/log.h>

GNRGLScreenshot::GNRGLScreenshot(wxString filename)
{
	//ctor
	m_filename = filename;
	m_bytesPerPixel = 3;  //RGB
	create();
}

void GNRGLScreenshot::create()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	m_width = viewport[2];
	m_height = viewport[3];
	
	
	const size_t imageSizeInBytes = m_bytesPerPixel * size_t(m_width) * size_t(m_height);
	
	// Allocate with malloc, because the data will be managed by wxImage
	unsigned char* pPicData = static_cast<unsigned char*>(malloc(imageSizeInBytes));
	
	// read pixels from GL
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, pPicData);
	
	swapPixels(pPicData);
	
	wxImage mypic(m_width, m_height, pPicData);
	mypic.SaveFile(m_filename);
}

// glReadPixels reads the given rectangle from bottom-left to top-right, so we must reverse it
void GNRGLScreenshot::swapPixels(unsigned char* pPicData)
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

GNRGLScreenshot::~GNRGLScreenshot()
{
	//dtor
}
