#include <wx/msgdlg.h>
#include "GNROaxImport.h"
#include "GNRTests.h"

GNRTests::GNRTests()
{
	//ctor
}

GNRTests::~GNRTests()
{
	//dtor
}

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
