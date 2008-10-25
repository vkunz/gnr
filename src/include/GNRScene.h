#ifndef GNRSCENE_H
#define GNRSCENE_H

#include "GNRAssembly.h"
#include "GNRGLCamera.h"
#include "GNRMaterial.h"
#include "GNRGLCanvas2D.h"
#include "GNRGLCanvas3D.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

class GNRScene
{
private:

	//pointer for scene details
	GNRAssembly*    m_RootAssembly;
	GNRGLCamera*    m_GLCamera;
	//pointer to canvas
	GNRGLCanvas2D*  m_Canvas2D;
	GNRGLCanvas3D*  m_Canvas3D;
	
	//ID of actual selected assembly
	int m_AssemblyID;
	
protected:

public:

	GNRAssembly* getRootAssembly();
	GNRAssembly* getAssembly();
	GNRGLCamera* getGLCamera();
	
	void setAssemblyID(int assemblyID);
	void setCanvas2D(GNRGLCanvas2D* p);
	void setCanvas3D(GNRGLCanvas3D* p);
	GNRGLCanvas2D* getCanvas2D();
	GNRGLCanvas3D* getCanvas3D();
	
	void newRoom();
	void resetCamera();
	
	void glRefresh();
	void glRefresh2D();
	void glRefresh3D();
	
	GNRScene();
	virtual ~GNRScene();
	
};

#endif // GNRSCENE_H
