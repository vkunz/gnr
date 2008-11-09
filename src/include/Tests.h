#ifndef TESTS_H
#define TESTS_H

#if defined(__ATHOS_DEBUG__)

#include "Scene.h"

class Tests
{
public:
	Tests();
	virtual ~Tests();
	
	void sizeXsizeLoopsLoadClean(Scene* scene, const int loops, const int size);
	void loadTieFighter(Scene* scene, const int loops);
	void dumpWorldStructure(Scene* scene);
	
protected:
private:
};

#endif // DEBUG

#endif // TESTS_H
