/**
 * GNRTests
 * @name        GNRTests.cpp
 * @date        2008-11-08
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#if defined(__ATHOS_DEBUG__)

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
	str << wxT("Memory Test (sizeXsizeLoopsLoadClean) is starting!\n");
	str << wxT("Prepare Taskmanager now, and wait...\n");
	str << wxT("DO NOT CLICK OVER COVER THE APP!\n\n");
	str << loops << wxT(" loops, cubes ") << size << wxT(" x ") << size;
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
	scene->newRoom();
}

/**
 * start load and clean test
 * @param       int         loops done
 * @param       int         size of cube duplicates (size x size)
 * @access      public
 */
void GNRTests::loadTieFighter(GNRScene* scene, const int loops = 10)
{
	wxString str;
	str << wxT("Memory Test (loadTieFighter) is starting!\n");
	str << wxT("Prepare Taskmanager now, and wait...\n");
	str << wxT("DO NOT CLICK OVER COVER THE APP!\n\n");
	str << loops << wxT(" loops, tie fighters ");
	wxMessageBox(str);
	
	for (int h = 0; h<loops; ++h)
	{
		GNROaxImport in(wxT("data\\Tie Fighter.oax"));
		//get assembly
		GNRAssembly* dummy = in.getAssembly();
		//insert in scene
		scene->insertAssembly(dummy);
		//clean now
		scene->newRoom();
	}
	
	wxMessageBox(wxT("FERTIG!"));
	scene->newRoom();
}

/**
 * dump world structure to debug frame
 * @access      public
 */
void GNRTests::dumpWorldStructure(GNRScene* scene)
{
	wxLogDebug(wxT(""));
	wxLogDebug(wxT("|ROOT"));
	scene->getRootAssembly()->dump(wxT("+"));
	
	wxLogDebug(wxT(""));
	wxLogDebug(wxT("|TRASH"));
	scene->getTrash()->dump(wxT("+"));
}

#endif
