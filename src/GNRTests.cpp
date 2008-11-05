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
	for (int h = -loops/2; h<loops/2; ++h)
	{
		for (int i = -size/2; i<=size/2; ++i)
		{
			for (int j = -size/2; j<=size/2; ++j)
			{
				//build importer and load jumbo
				GNROaxImport in(wxT("data\\cube_green_1x1.oax"));
				// get assembly
				GNRAssembly* dummy = in.getAssembly();
				//insert in scene
				scene->insertAssembly(dummy);
				//move dummy around
				dummy->setX(i*1.5);
				dummy->setZ(j*1.5);
			}
		}
		scene->newRoom();
	}
}
