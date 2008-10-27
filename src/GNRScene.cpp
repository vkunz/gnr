#include "GNRScene.h"

GNRScene::GNRScene()
{
	m_RootAssembly  = new GNRAssembly("scene");
	m_GLCamera2D    = new GNRGLCamera();
	m_GLCamera3D    = new GNRGLCamera();
	m_GLCamera2D->rotateX(-90);
	m_GLCamera2D->changeDistance(3);
}

GNRScene::~GNRScene()
{
	delete m_GLCamera2D;
	delete m_GLCamera3D;
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

GNRGLCamera* GNRScene::getGLCamera2D()
{
	return m_GLCamera2D;
}

GNRGLCamera* GNRScene::getGLCamera3D()
{
	return m_GLCamera3D;
}

/**
 * clean up whole world
 * @access      public
 */
void GNRScene::newRoom()
{
	delete m_RootAssembly;
	m_RootAssembly = new GNRAssembly("scene");
	resetCamera();
}

/**
 * resets the camera to initial state
 * @access      public
 */
void GNRScene::resetCamera()
{
	m_GLCamera3D->reset();
	m_GLCamera2D->reset();
}

void GNRScene::setCanvas2D(GNRGLCanvas2D* p)
{
	m_Canvas2D = p;
}

void GNRScene::setCanvas3D(GNRGLCanvas3D* p)
{
	m_Canvas3D = p;
}

GNRGLCanvas2D* GNRScene::getCanvas2D()
{
	return m_Canvas2D;
}

GNRGLCanvas3D* GNRScene::getCanvas3D()
{
	return m_Canvas3D;
}

/**
 * refresh glcanvas frames (3d/2d)
 * @access      public
 */
void GNRScene::glRefresh()
{
	glRefresh2D();
	glRefresh3D();
}

/**
 * refresh only 2D canvas
 * @access      public
 */
void GNRScene::glRefresh2D()
{
	//prepare and draw 2D top view of room
	m_Canvas2D->prepareDraw();
	m_GLCamera2D->render();
	m_RootAssembly->draw();
	m_Canvas2D->endDraw();
}

/**
 * refresh only 3D canvas
 * @access      public
 */
void GNRScene::glRefresh3D()
{
	//prepare and draw 3D view of room
	m_Canvas3D->prepareDraw();
	m_GLCamera3D->render();
	m_RootAssembly->draw();
	m_Canvas3D->endDraw();
}
