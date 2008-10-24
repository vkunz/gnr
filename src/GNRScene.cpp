#include "GNRScene.h"

GNRScene::GNRScene()
{
	m_RootAssembly = new GNRAssembly("scene");
	m_GLCamera     = new GNRGLCamera();
}

GNRScene::~GNRScene()
{
	delete m_GLCamera;
	delete m_RootAssembly;
}

void GNRScene::setAssemblyID(int assemblyID)
{
	m_AssemblyID = assemblyID;
}

GNRAssembly* GNRScene::getAssembly()
{
	return (GNRAssembly*)m_AssemblyID;
}

GNRAssembly* GNRScene::getRootAssembly()
{
	return m_RootAssembly;
}

GNRGLCamera* GNRScene::getGLCamera()
{
	return m_GLCamera;
}

/**
 * clean up whole world
 * @access      public
 */
void GNRScene::newRoom()
{
	delete m_RootAssembly;
	m_RootAssembly = new GNRAssembly("scene");
	m_GLCamera->reset();
}

/**
 * resets the camera to initial state
 * @access      public
 */
void GNRScene::resetCamera()
{
	m_GLCamera->reset();
}

void GNRScene::setCanvas2D(GNRGL2DCanvas* p)
{
	m_Canvas2D = p;
}

void GNRScene::setCanvas3D(GNRGL3DCanvas* p)
{
	m_Canvas3D = p;
}

/**
 * refresh glcanvas frames (3d/2d)
 * @access      public
 */
void GNRScene::glRefresh()
{
	glRefresh2D();
	glRefresh3D();
	glRefresh2D();
	
}

/**
 * refresh 2D canvas
 * @access      private
 */
void GNRScene::glRefresh2D()
{
	//prepare and draw 2D top view of room
	m_Canvas2D->prepareDraw();
	m_RootAssembly->draw();
	m_Canvas2D->endDraw();
}

/**
 * refresh 3D canvas
 * @access      private
 */
void GNRScene::glRefresh3D()
{
	//prepare and draw 3D view of room
	m_Canvas3D->prepareDraw();
	m_GLCamera->render();
	m_RootAssembly->draw();
	m_Canvas3D->endDraw();
}
