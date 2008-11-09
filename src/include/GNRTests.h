#ifndef GNRTESTS_H
#define GNRTESTS_H

#if defined(__ATHOS_DEBUG__)

#include "GNRScene.h"

class GNRTests
{
public:
	GNRTests();
	virtual ~GNRTests();
	
	void sizeXsizeLoopsLoadClean(GNRScene* scene, const int loops, const int size);
	void loadTieFighter(GNRScene* scene, const int loops);
	void dumpWorldStructure(GNRScene* scene);
	
protected:
private:
};

#endif // DEBUG

#endif // GNRTESTS_H
