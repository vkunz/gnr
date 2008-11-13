/**
 * Tests
 * @name        Tests.cpp
 * @date        2008-11-08
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#if defined(__ATHOS_DEBUG__)

#include <wx/msgdlg.h>
#include "OaxImport.h"
#include "Tests.h"

/**
 * constructor for tests
 */
Tests::Tests()
{
}

/**
 * destructor for tests
 */
Tests::~Tests()
{
}

/**
 * start load and clean test
 * @param[in]       scene       pointer to scene
 * @param[in]       loops       int loops done
 * @param[in]       size        int size of cube duplicates (size x size)
 */
void Tests::sizeXsizeLoopsLoadClean(Scene* scene, const int loops = 10, const int size = 10)
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
				//OaxImport in(wxT("data\\apple-ibook-2001.oax"));
				OaxImport in(wxT("data\\cube_green_1x1.oax"));
				//get assembly
				Assembly* dummy = in.getAssembly();
				//move dummy around
				dummy->position().setXZ(i, j);
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
 * @param[in]       scene       pointer to scene
 * @param[in]       loops       int loops done
 */
void Tests::loadTieFighter(Scene* scene, const int loops = 10)
{
	wxString str;
	str << wxT("Memory Test (loadTieFighter) is starting!\n");
	str << wxT("Prepare Taskmanager now, and wait...\n");
	str << wxT("DO NOT CLICK OVER COVER THE APP!\n\n");
	str << loops << wxT(" loops, tie fighters ");
	wxMessageBox(str);
	
	for (int h = 0; h<loops; ++h)
	{
		OaxImport in(wxT("data\\Tie Fighter.oax"));
		//get assembly
		Assembly* dummy = in.getAssembly();
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
 * @param[in]   scene       pointer to scene
 */
void Tests::dumpWorldStructure(Scene* scene)
{
	wxLogDebug(wxT(""));
	wxLogDebug(wxT("|ROOT"));
	scene->getRootAssembly()->dump(wxT("+"));
	
	wxLogDebug(wxT(""));
	wxLogDebug(wxT("|TRASH"));
	scene->getTrash()->dump(wxT("+"));
}

#endif
