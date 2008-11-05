#ifndef GNRTESTS_H
#define GNRTESTS_H

#include "GNRScene.h"

class GNRTests
{
public:
	GNRTests();
	virtual ~GNRTests();
	
	void sizeXsizeLoopsLoadClean(GNRScene* scene, const int loops, const int size);
	
protected:
private:
};

#endif // GNRTESTS_H
