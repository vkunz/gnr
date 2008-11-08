/**
 * GNRTests
 * @name        GNRTests.cpp
 * @date        2008-11-08
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/msgdlg.h>
#include "GNROaxImport.h"
#include "GNRTests.h"

GNRTests::GNRTests()
{
}

GNRTests::~GNRTests()
{
}

/**
 * start load and clean test
 * @param       int         loops done
 * @param       int         size of cube duplicates (size x size)
 * @access      public
 */
void GNRTests::sizeXsizeLoopsLoadClean(GNRScene* scene, const int loops = 10, const int size = 10)
{
	wxString str;
	str << wxT("Test (sizeXsizeLoopsLoadClean) beginnt!\n");
	str << loops << wxT(" Durchläufe mit ") << size << wxT(" x ") << size << wxT(" Kuben...");
	wxMessageBox(str);
	
	for (int h = -loops/2; h<loops/2+1; ++h)
	{
		for (int i = -size/2; i<size/2+1; ++i)
		{
			for (int j = -size/2; j<size/2+1; ++j)
			{
				//build importer and load jumbo
				//GNROaxImport in(wxT("data\\apple-ibook-2001.oax"));
				GNROaxImport in(wxT("data\\cube_green_1x1.oax"));
				//get assembly
				GNRAssembly* dummy = in.getAssembly();
				//move dummy around
				dummy->setX(i*1.0);
				dummy->setZ(j*1.0);
				//insert in scene
				scene->insertAssembly(dummy);
			}
		}
		scene->newRoom();
	}
	
	wxMessageBox(wxT("FERTIG!"));
}
