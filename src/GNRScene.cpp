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
