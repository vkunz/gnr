/**
 * GNRScene
 * @name        GNRScene.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRScene.h"

/**
 * construct scene and two assemblies (scene and grouper) plus
 * two cameras for 2D and 3D
 * @access      public
 */
GNRScene::GNRScene()
{
	m_Assembly = NULL;
	
	m_GLCamera2D    = new GNRGLCamera();
	m_GLCamera3D    = new GNRGLCamera();
	
	m_RootAssembly  = new GNRAssembly(IS_ROOT,    "scene");
	m_Selected      = new GNRAssembly(IS_SELECTED,"selected");
	
	m_Trash         = new GNRAssembly(IS_TRASH,   "trash");
	m_Hidden        = new GNRAssembly(IS_HIDDEN,  "hidden");
	
	//put selected assembly in real world
	m_RootAssembly->addPart(m_Selected);
	
	resetCamera();
}

/**
 * destruct scene and two assemblies (scene and grouper) plus
 * two cameras for 2D and 3D
 * @access      public
 */
GNRScene::~GNRScene()
{
	delete m_GLCamera2D;
	delete m_GLCamera3D;
	
	delete m_RootAssembly;
	
	delete m_Trash;
	delete m_Hidden;
}

/**
 * set actual hit assembly id
 * @access      public
 */
void GNRScene::setAssembly(GNRAssembly* assembly)
{
	m_Assembly = assembly;
}

/**
 * get actual assembly pointer
 * @return      GNRAssembly*    pointer to act. assembly
 * @access      public
 */
GNRAssembly* GNRScene::getAssembly()
{
	return m_Assembly;
}

/**
 * get root assembly pointer
 * @return      GNRAssembly*    pointer to root assembly
 * @access      public
 */
GNRAssembly* GNRScene::getRootAssembly()
{
	return m_RootAssembly;
}

/**
 * get pointer to 2D cam
 * @return      GNRAssembly*    pointer to 2D cam
 * @access      public
 */
GNRGLCamera* GNRScene::getGLCamera2D()
{
	return m_GLCamera2D;
}

/**
 * get pointer to 3D cam
 * @return      GNRAssembly*    pointer to 3D cam
 * @access      public
 */
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
	m_Assembly = NULL;
	
	delete m_RootAssembly;
	delete m_Trash;
	delete m_Hidden;
	
	m_RootAssembly  = new GNRAssembly(IS_ROOT,    "scene");
	m_Selected      = new GNRAssembly(IS_SELECTED,"selected");
	
	m_Trash         = new GNRAssembly(IS_TRASH,   "trash");
	m_Hidden        = new GNRAssembly(IS_HIDDEN,  "hidden");
	
	//put selected assembly in real world
	m_RootAssembly->addPart(m_Selected);
	
	resetCamera();
}

/**
 * resets the camera to initial state
 * @access      public
 */
void GNRScene::resetCamera()
{
	//reset 2D cam to default
	m_GLCamera2D->reset();
	m_GLCamera2D->rotateX(-90);
	m_GLCamera2D->changeDistance(4);
	
	//reset 3D cam to default
	m_GLCamera3D->reset();
	m_GLCamera3D->changeDistance(2.5);
	m_GLCamera3D->setAngles(20.0, 0.0, 0.0);
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
	m_Canvas2D->initLights();
	m_Canvas2D->drawBaseFloor(0.0, 0.0, 0.0, 32);
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
	m_Canvas3D->initLights();
	m_Canvas3D->drawBaseFloor(0.0, 0.0, 0.0, 32);
	m_RootAssembly->draw();
	m_Canvas3D->endDraw();
}

/**
 * delete all selected assemblies (move to trash container)
 * @access      public
 */
void GNRScene::deleteSelectedAssemblies()
{
	list<GNRAssembly*> parts = m_Selected->getPartList();
	
	for (list<GNRAssembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		m_Trash->addPart((*it));
		m_Selected->delPart((*it));
	}
}

/**
 * hide all selected assemblies (move to hidden container)
 * @access      public
 */
void GNRScene::hideSelectedAssemblies()
{
	list<GNRAssembly*> parts = m_Selected->getPartList();
	
	for (list<GNRAssembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		m_Hidden->addPart((*it));
		m_Selected->delPart((*it));
	}
}

/**
 * group all selected assemblies and move to root
 * @access      public
 */
void GNRScene::groupSelectedAssemblies()
{
	list<GNRAssembly*> parts = m_Selected->getPartList();
	
	if (parts.size() <= 0)
	{
		return;
	}
	
	GNRAssembly* group = new GNRAssembly(IS_GROUP, "group");
	for (list<GNRAssembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		group->addPart((*it));
		m_Selected->delPart((*it));
	}
	m_RootAssembly->addPart(group);
}

/**
 * restore assembly (move from trash container to root)
 * @param       GNRAssembly*        pointer to assembly to restor
 * @access      public
 */
void GNRScene::restoreAssembly(GNRAssembly* assembly)
{
	if (assembly != NULL)
	{
		m_RootAssembly->addPart(assembly);
		m_Trash->delPart(assembly);
	}
}

/**
 * show actual assembly again (unhide, move out of hidden container)
 * @param       GNRAssembly*        pointer to assembly to show
 * @access      public
 */
void GNRScene::showAssembly(GNRAssembly* assembly)
{

}

/**
 * ungroup selected group and move all parts to selected container
 * @param       GNRAssembly*        pointer to assembly for editing
 * @access      public
 */
void GNRScene::ungroupAssembly(GNRAssembly* assembly)
{

}

/**
 * toggle selected assembly (later on CTRL
 * @param       GNRAssembly*        pointer to assembly to delete
 * @access      public
 */
void GNRScene::selectAssembly(GNRAssembly* assembly)
{
	if (assembly != NULL)
	{
		//is parent of assembly is not the select container
		if (! assembly->getParent()->isType(IS_SELECTED))
		{
			//move assembly in selected container
			m_Selected->addPart(assembly);
			m_RootAssembly->delPart(assembly);
			
			wxString msg;
			msg << (int)assembly << wxT(" moved to IS_SELECTED!");
			wxLogDebug(msg);
		}
		else
		{
			//move assembly in root
			m_RootAssembly->addPart(assembly);
			m_Selected->delPart(assembly);
			
			wxString msg;
			msg << (int)assembly << wxT(" moved to IS_ROOT!");
			wxLogDebug(msg);
		}
		//repaint cause of box on floor
		glRefresh();
	}
}
