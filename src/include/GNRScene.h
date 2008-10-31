/**
 * GNRScene
 * @name        GNRScene.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRSCENE_H
#define GNRSCENE_H

#include "GNRAssembly.h"
#include "GNRGLCamera.h"
#include "GNRGLCanvas2D.h"
#include "GNRGLCanvas3D.h"
#include "GNRLineDrawEvent.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

class GNRScene: public wxEvtHandler
{
private:

	//pointer for scene details
	GNRAssembly*    m_RootAssembly;
	
	//pointer to separate containers
	GNRAssembly*    m_Selected;
	GNRAssembly*    m_Trash;
	GNRAssembly*    m_Hidden;
	
	//both cameras
	GNRGLCamera*    m_GLCamera2D;
	GNRGLCamera*    m_GLCamera3D;
	
	//pointer to canvas
	GNRGLCanvas2D*  m_Canvas2D;
	GNRGLCanvas3D*  m_Canvas3D;
	
	//ID of actual selected assembly
	GNRAssembly* m_Assembly;
	
protected:

public:

	GNRAssembly* getRootAssembly();
	GNRAssembly* getAssembly();
	GNRGLCamera* getGLCamera2D();
	GNRGLCamera* getGLCamera3D();
	
	void setAssembly(GNRAssembly* assembly);
	void setCanvas2D(GNRGLCanvas2D* p);
	void setCanvas3D(GNRGLCanvas3D* p);
	GNRGLCanvas2D* getCanvas2D();
	GNRGLCanvas3D* getCanvas3D();
	
	void newRoom();
	void resetCamera();
	
	void glRefresh();
	void glRefresh2D();
	void glRefresh3D();
	
	void drawLine(GNRLineDrawEvent& event);
	
	void deleteSelectedAssemblies();
	void hideSelectedAssemblies();
	void groupSelectedAssemblies();
	void ungroupSelectedAssemblies();
	
	void ungroupOneAssembly(GNRAssembly* assembly);
	void restoreAssembly(GNRAssembly* assembly);
	void showAssembly(GNRAssembly* assembly);
	void selectAssembly(GNRAssembly* assembly);
	void minmax(float& min,float& max,float value);
	
	void insertCuboid(GNRAssembly* cuboid);
	
	GNRScene();
	virtual ~GNRScene();
	
};

#endif // GNRSCENE_H
