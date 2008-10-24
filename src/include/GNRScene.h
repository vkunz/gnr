#ifndef GNRSCENE_H
#define GNRSCENE_H

#include "GNRAssembly.h"
#include "GNRGLCamera.h"
#include "GNRMaterial.h"
#include "GNRGL2DCanvas.h"
#include "GNRGL3DCanvas.h"

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
	GNRGL2DCanvas*  m_Canvas2D;
	GNRGL3DCanvas*  m_Canvas3D;
	
	//ID of actual selected assembly
	int m_AssemblyID;
	
	void glRefresh2D();
	void glRefresh3D();
	
protected:

public:

	GNRAssembly* getRootAssembly();
	GNRAssembly* getAssembly();
	GNRGLCamera* getGLCamera();
	
	void setAssemblyID(int assemblyID);
	void setCanvas2D(GNRGL2DCanvas* p);
	void setCanvas3D(GNRGL3DCanvas* p);
	
	void newRoom();
	void resetCamera();
	
	void glRefresh();
	
	GNRScene();
	virtual ~GNRScene();
	
};

#endif // GNRSCENE_H
