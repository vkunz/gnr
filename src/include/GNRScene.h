#ifndef GNRSCENE_H
#define GNRSCENE_H

#include "GNRAssembly.h"
#include "GNRGLCamera.h"
#include "GNRMaterial.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

class GNRScene
{
private:

	//pointer for scene details
	GNRAssembly* m_RootAssembly;
	GNRGLCamera* m_GLCamera;
	
	//ID of actual selected assembly
	int m_AssemblyID;
	
protected:

public:

	GNRAssembly* getRootAssembly();
	GNRAssembly* getAssembly();
	GNRGLCamera* getGLCamera();
	
	void setAssemblyID(int assemblyID);
	
	GNRScene();
	virtual ~GNRScene();
	
};

#endif // GNRSCENE_H
