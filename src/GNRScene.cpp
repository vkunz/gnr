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
#include "GNRNotifyEvent.h"
#include "GNRGlobalDefine.h"

/**
 * construct scene and two assemblies (scene and grouper) plus
 * two cameras for 2D and 3D
 * @access      public
 */
GNRScene::GNRScene()
{
	initContainers();
	
	m_GLCamera2D    = new GNRGLCamera();
	m_GLCamera3D    = new GNRGLCamera();
	
	resetCamera();
}

/**
 * destruct scene and two assemblies (scene and grouper) plus
 * two cameras for 2D and 3D
 * @access      public
 */
GNRScene::~GNRScene()
{
	destroyContainers();
	
	delete m_GLCamera2D;
	delete m_GLCamera3D;
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
 * init whole world of containers
 * @access      public
 */
void GNRScene::initContainers()
{
	m_Assembly = NULL;
	
	m_RootAssembly  = new GNRAssembly(IS_ROOT,        wxT("scene"));
	m_Selected      = new GNRAssembly(IS_SELECTED,    wxT("selected"));
	
	//put selected assembly in real world
	m_RootAssembly->addPart(m_Selected);
	
	m_Trash         = new GNRAssembly(IS_TRASH,       wxT("trash"));
	m_Hidden        = new GNRAssembly(IS_HIDDEN,      wxT("hidden"));
	m_Duplicator    = new GNRAssembly(IS_DUPLICATOR,  wxT("duplicator"));
}

/**
 * kill whole world of containers
 * @access      public
 */
void GNRScene::destroyContainers()
{
	//selected is killed by root assembly
	delete m_RootAssembly;
	
	//kill all temp containers
	delete m_Trash;
	delete m_Hidden;
	delete m_Duplicator;
}

/**
 * clean up whole world
 * @access      public
 */
void GNRScene::newRoom()
{
	destroyContainers();
	initContainers();
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
	m_GLCamera2D->changeDistance(15);
	
	//reset 3D cam to default
	m_GLCamera3D->reset();
	m_GLCamera3D->rotateX(-40);
	m_GLCamera3D->changeDistance(12);
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
	glRefresh3D();
	glRefresh2D();
}

/**
 * refresh defines canvas with cam and cast shadows
 * @access      private
 */
void GNRScene::glRefreshCanvas()
{
	//prepare and draw 2D top view of room
	m_GLOUT->prepareDraw();
	
	//initialize only light source
	m_GLOUT->initLights();
	
	//set camera for scene
	m_GLCAM->render();
	
	/*NOW PREPARE THE PIXELBUFFER AND DRAW VIRTUAL FLOOR FOR CASTING SHADOWS*/
	
	//prepare pixelbuffer for shadows
	m_GLOUT->preparePixelBuffer();
	
	//draw invisible floor for shadow projection
	m_GLOUT->drawBaseFloor(0.0, 0.0, 0.0, DEFAULT_FLOOR_SIZE);
	
	//turn the color and depth buffers back on
	m_GLOUT->endPixelBuffer();
	
	/*NOW CAST THE SHADOWS ON THE FLOOR AND KEEP IN PIXELBUFFER*/
	
	//draw real floor for casting shadows (1)
	m_GLOUT->drawBaseFloor(0.0, 0.0, 0.0, DEFAULT_FLOOR_SIZE);
	
	//draw all shadows of objects
	glPushMatrix();
	{
		//turn shadows on
		m_GLOUT->shadowColorOn();
		//load shadow projection matrix
		m_GLOUT->loadShadowMatrix();
		//draw shadows on prepainted floor (1)
		glPushMatrix();
		{
			m_RootAssembly->drawShadow();
		}
		glPopMatrix();
		//turn off shadows
		m_GLOUT->shadowColorOff();
	}
	glPopMatrix();
	
	/*NOW DRAW ALL OBJECTS WITHOUT SHADOWS AND BLEND WITH SHADOWS*/
	
	//draw real objects
	glPushMatrix();
	{
		m_GLOUT->initLights();
		m_RootAssembly->draw();
	}
	glPopMatrix();
	
	//finish output and flush
	m_GLOUT->endDraw();
}

/**
 * refresh only 2D canvas
 * @access      public
 */
void GNRScene::glRefresh2D()
{
	m_GLOUT = m_Canvas2D;
	m_GLCAM = m_GLCamera2D;
	glRefreshCanvas();
}

/**
 * refresh only 3D canvas
 * @access      public
 */
void GNRScene::glRefresh3D()
{
	m_GLOUT = m_Canvas3D;
	m_GLCAM = m_GLCamera3D;
	glRefreshCanvas();
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
 * clone all selected assemblies
 * @access      public
 */
void GNRScene::cloneSelectedAssemblies()
{
	list<GNRAssembly*> parts = m_Selected->getPartList();
	
	for (list<GNRAssembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		GNRAssembly* a_copy = (*it)->clone();
		//move selected to world
		m_RootAssembly->addPart((*it));
		//remove selected
		m_Selected->delPart((*it));
		//copy clone in selected
		m_Selected->addPart(a_copy);
	}
}

/**
 * copy all selected assemblies
 * @access      public
 */
void GNRScene::copySelectedAssemblies()
{
	delete m_Duplicator;
	m_Duplicator = new GNRAssembly(IS_DUPLICATOR,  wxT("duplicator"));
	
	list<GNRAssembly*> parts = m_Selected->getPartList();
	
	for (list<GNRAssembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		GNRAssembly* a_copy = (*it)->clone();
		m_Duplicator->addPart(a_copy);
	}
}

/**
 * cut all selected assemblies
 * @access      public
 */
void GNRScene::cutSelectedAssemblies()
{
	delete m_Duplicator;
	m_Duplicator = new GNRAssembly(IS_DUPLICATOR,  wxT("duplicator"));
	
	list<GNRAssembly*> parts = m_Selected->getPartList();
	
	for (list<GNRAssembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		GNRAssembly* a_copy = (*it)->clone();
		m_Duplicator->addPart(a_copy);
		m_Selected->delPart((*it));
	}
}

/**
 * insert all copied assemblies
 * @access      public
 */
void GNRScene::insertCopiedAssemblies()
{
	list<GNRAssembly*> parts = m_Duplicator->getPartList();
	
	for (list<GNRAssembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		GNRAssembly* a_copy = (*it)->clone();
		m_Selected->addPart(a_copy);
	}
}

/**
 * draws a line, specified in the event to the 2D canvas
 * @param   GNRLineDrawEvent    event with information about the line
 * @access      public
 */
void GNRScene::drawLine(GNRLineDrawEvent& event)
{
	//initialize only light source
	m_Canvas2D->initLights();
	
	//prepare and draw 2D top view of room
	m_Canvas2D->prepareDraw();
	
	//set camera for scene
	m_GLCamera2D->render();
	
	/*NOW PREPARE THE PIXELBUFFER AND DRAW VIRTUAL FLOOR FOR CASTING SHADOWS*/
	
	//prepare pixelbuffer for shadows
	m_Canvas2D->preparePixelBuffer();
	
	//draw invisible floor for shadow projection
	m_Canvas2D->drawBaseFloor(0.0, 0.0, 0.0, DEFAULT_FLOOR_SIZE);
	
	//turn the color and depth buffers back on
	m_Canvas2D->endPixelBuffer();
	
	/*NOW CAST THE SHADOWS ON THE FLOOR AND KEEP IN PIXELBUFFER*/
	
	//draw real floor for casting shadows (1)
	m_Canvas2D->drawBaseFloor(0.0, 0.0, 0.0, DEFAULT_FLOOR_SIZE);
	
	//draw all shadows of objects
	glPushMatrix();
	{
		//turn shadows on
		m_Canvas2D->shadowColorOn();
		//load shadow projection matrix
		m_Canvas2D->loadShadowMatrix();
		//draw shadows on prepainted floor (1)
		glPushMatrix();
		{
			m_RootAssembly->drawShadow();
		}
		glPopMatrix();
		//turn off shadows
		m_Canvas2D->shadowColorOff();
	}
	glPopMatrix();
	
	/*NOW DRAW ALL OBJECTS WITHOUT SHADOWS AND BLEND WITH SHADOWS*/
	
	//draw real objects
	glPushMatrix();
	{
		//reinit lights
		m_Canvas2D->initLights();
		m_RootAssembly->draw();
		
		// draw line from start- to end-point
		float lineColor[4] = {1.0, 0.0, 0.0, 0.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lineColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, lineColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lineColor);
		
		//should be like the default wallsize
		glLineWidth(100.0/(float)m_GLCamera2D->getDistance());
		
		glBegin(GL_LINES);
		{
			glVertex3f(event.getStartPoint().getX(), event.getStartPoint().getY(), event.getStartPoint().getZ());
			glVertex3f(event.getEndPoint().getX(), event.getEndPoint().getY(), event.getEndPoint().getZ());
		}
		glEnd();
	}
	glPopMatrix();
	
	//put output to screen
	m_Canvas2D->endDraw();
	
	// calculate length of the line
	float x = event.getEndPoint().getX() - event.getStartPoint().getX();
	float y = event.getEndPoint().getY() - event.getStartPoint().getY();
	float z = event.getEndPoint().getZ() - event.getStartPoint().getZ();
	GNRVertex myvec(x, y, z);
	float length = myvec.length();
	
	// send event to display length
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(DISPLAYLENGTH);
	gnrevent.setFloat(length);
	ProcessEvent(gnrevent);
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
	
	if (parts.size() < 1)
	{
		//no or only one part, don't waste time
		return;
	}
	
	GNRAssembly* group = new GNRAssembly(IS_GROUP, wxT("group"));
	
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
	
	if (sel_parts.size() < 1)
	{
		//no or only one part, don't waste time
		return;
	}
	
	GNRVertex grp_center, grp_rotate, obj_center, ptr_object, ptr_rotate;
	
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
			//save old rotation of whole group
			grp_rotate = (*it)->getRotateVertex();
			
			//correct position of all group members
			for (list<GNRAssembly*>::iterator child_it = grp_parts.begin(); child_it != grp_parts.end(); ++child_it)
			{
				//move assembly from group to IS_SELECTED in (0|0|0)
				m_Selected->addPart((*child_it));
				(*it)->delPart((*child_it));
				
				//save old relative position of child from group center
				ptr_object = (*child_it)->getCenterVertex();
				ptr_rotate = (*child_it)->getRotateVertex();
				
				//restore rotation from group to child around center
				ptr_object.rotate(grp_rotate);
				
				//calculate new position of child relative to (0|0|0)
				obj_center = ptr_object + grp_center;
				
				//rotate child in same way as group and set new center
				(*child_it)->setRotateVertex(grp_rotate + ptr_rotate);
				(*child_it)->setCenterVertex(obj_center);
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
	
	if (grp_parts.size() < 1)
	{
		//no or only one part, don't waste time
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

/**
 * inserts a new assembly to the root-assembly
 * @param   GNRAssembly*    pointer to the assembly, that should be insert
 * @access      public
 */
void GNRScene::insertAssembly(GNRAssembly* assembly)
{
	assembly->putOnGround();
	m_RootAssembly->addPart(assembly);
	glRefresh();
}

/**
 * inserts a new hidden assembly to the hidden assembly
 * @param   GNRAssembly*    pointer to the assembly, that should be insert
 * @access      public
 */
void GNRScene::insertHiddenAssembly(GNRAssembly* assembly)
{
	m_Hidden->addPart(assembly);
}
