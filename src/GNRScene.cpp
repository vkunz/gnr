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

void GNRScene::drawLine(GNRLineDrawEvent& event)
{
	//prepare and draw 2D top view of room
	m_Canvas2D->prepareDraw();
	m_GLCamera2D->render();
	m_Canvas2D->initLights();
	m_Canvas2D->drawBaseFloor(0.0, 0.0, 0.0, 32);
	m_RootAssembly->draw();
	
	// draw line from start- to end-point
	float lineColor[4] = {1.0, 0.0, 0.0, 0.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lineColor);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex3f(event.getStartPoint().getX(), event.getStartPoint().getY(), event.getStartPoint().getZ());
	glVertex3f(event.getEndPoint().getX(), event.getEndPoint().getY(), event.getEndPoint().getZ());
	glEnd();
	
	m_Canvas2D->endDraw();
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
		//no parts, don't waste time
		return;
	}
	
	GNRAssembly* group = new GNRAssembly(IS_GROUP, "group");
	
	float min[3] = {10000.0,10000.0,10000.0};
	float max[3] = {-10000.0,-10000.0,-10000.0};
	
	//first pass to get maximum cube and new center of group
	for (list<GNRAssembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		//kill possible empty groups in container
		if ((*it)->getPartList().size() < 1)
		{
			m_Selected->delPart(*it);
			continue;
		}
		minmax(min[0], max[0], (*it)->getX());
		minmax(min[1], max[1], (*it)->getY());
		minmax(min[2], max[2], (*it)->getZ());
	}
	
	//build new center as vertex for better calculation
	GNRVertex new_center((max[0]+min[0])/2.0, (max[1]+min[1])/2.0, (max[2]+min[2])/2.0);
	
	//move group center to new center
	group->setCenterVertex(new_center);
	group->setHeight((max[1]+min[1]));
	//store obj center as vertex
	GNRVertex obj_center;
	
	//put all assemblies in the selected container
	for (list<GNRAssembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		//store old center
		obj_center = (*it)->getCenterVertex();
		
		//add part to new group and remove from selection
		group->addPart((*it));
		m_Selected->delPart((*it));
		
		//modify center relative to new center
		obj_center = obj_center - new_center;
		(*it)->setCenterVertex(obj_center);
	}
	
	//put new group in the world
	m_RootAssembly->addPart(group);
	
#warning "INFO: check how to set undo and redo!"
//	GNRCommandAssembly* command = new GNRCommandAssembly;
//	command->setAssembly(group);
//
//	GNRUndoRedo* undo = GNRUndoRedo::getInstance();
//	undo->enqueue(command);
}

/**
 * ungroup selected group and move all parts to selected container
 * @access      public
 */
void GNRScene::ungroupSelectedAssemblies()
{
	list<GNRAssembly*> sel_parts = m_Selected->getPartList();
	list<GNRAssembly*> grp_parts;
	
	if (sel_parts.size() <= 0)
	{
		//no parts, don't waste time
		return;
	}
	
	GNRVertex grp_center;
	GNRVertex obj_center;
	
	//find all groups and free them
	for (list<GNRAssembly*>::iterator it = sel_parts.begin(); it != sel_parts.end(); ++it)
	{
		//only for groups in the selected container
		if ((*it)->isType(IS_GROUP))
		{
			//get partlist iterator
			grp_parts  = (*it)->getPartList();
			//save center of group
			grp_center = (*it)->getCenterVertex();
			
			//correct position of all group members
			for (list<GNRAssembly*>::iterator child_it = grp_parts.begin(); child_it != grp_parts.end(); ++child_it)
			{
				//move assembly from group to IS_SELECTED
				m_Selected->addPart((*child_it));
				(*it)->delPart((*child_it));
				
				//calculate new position to center of IS_SELECTED
				obj_center = (*child_it)->getCenterVertex() + grp_center;
				(*child_it)->setCenterVertex(obj_center);
#warning "INFO: rotation has to be calculated by vertexes!"
				//put the new child on the floor, please
				//(*child_it)->putOnGround();
			}
			//remove group container from his parent
			m_Selected->delPart(*it);
		}
	}
}

/**
 * ungroup selected assembly and move all parts to root
 * @access      public
 */
void GNRScene::ungroupOneAssembly(GNRAssembly* assembly)
{
	list<GNRAssembly*> grp_parts = assembly->getPartList();
	
	if (grp_parts.size() <= 0)
	{
		//no parts, don't waste time
		return;
	}
	
	GNRVertex grp_center = assembly->getCenterVertex();
	GNRVertex obj_center;
	
	//find all groups and free them
	for (list<GNRAssembly*>::iterator child_it = grp_parts.begin(); child_it != grp_parts.end(); ++child_it)
	{
		//move child from group to one level upwards
		(assembly->getParent())->addPart((*child_it));
		//kill part in group now
		assembly->delPart((*child_it));
		//calculate new position relative to center of parent
		obj_center = (*child_it)->getCenterVertex() + grp_center;
		//set new center of child
		(*child_it)->setCenterVertex(obj_center);
	}
	//remove empty group container from parent
	(assembly->getParent())->delPart(assembly);
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
 * toggle selected assembly (later on CTRL
 * @param       GNRAssembly*        pointer to assembly to delete
 * @access      public
 */
void GNRScene::selectAssembly(GNRAssembly* assembly)
{
	if (assembly != NULL && assembly->getParent() != NULL)
	{
		//if parent of assembly is group, highlight
		if (! assembly->getParent()->isType(IS_SELECTED))
		{
			//move assembly in selected container
			m_Selected->addPart(assembly);
			m_RootAssembly->delPart(assembly);
		}
		else if (assembly->getParent()->isType(IS_SELECTED))
		{
			//move assembly in root
			m_RootAssembly->addPart(assembly);
			m_Selected->delPart(assembly);
		}
		//repaint cause of box on floor
		glRefresh();
	}
}

/**
 * calculate min max values
 * @param       float       new minium value
 * @param       float       new maximum value
 * @param       float       value to check for changes
 * @access      public
 */
void GNRScene::minmax(float& min,float& max,float value)
{
	if (max < value)
	{
		max = value;
	}
	if (min > value)
	{
		min = value;
	}
}
