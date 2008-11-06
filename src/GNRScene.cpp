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
#include "GNRSceneTreeNode.h"
#include "GNRTreeSceneItemData.h"

// initialize pointer
GNRScene* GNRScene::pinstance = 0;

/**
 * construct scene and two assemblies (scene and grouper) plus
 * two cameras for 2D and 3D
 * @access      protected
 */
GNRScene::GNRScene()
{
	m_shadows = true;
	
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
 * creates a new class if not instantiated or returns a pointer to the object if already
 * instantiated before
 * two cameras for 2D and 3D
 * @access      public
 */
GNRScene* GNRScene::getInstance()
{
	if (pinstance == 0)
	{
		pinstance = new GNRScene;
	}
	return pinstance;
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
 * toggles shadows on and off
 * @access      public
 */
void GNRScene::toggleShadows(bool status)
{
	m_shadows = status;
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
	m_Duplicator    = new GNRAssembly(IS_DUPLICATOR,  wxT("duplicator"));
}

/**
 * kill whole world of containers
 * @access      public
 */
void GNRScene::destroyContainers()
{
	//disconnect selected part
	m_RootAssembly->delPart(m_Selected);
	
	//selected is killed, then root
	delete m_Selected;
	delete m_RootAssembly;
	
	//kill all temp containers
	delete m_Trash;
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
	
	// send event to refresh Scene-Tree
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
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
	
	//set camera for scene
	m_GLCAM->render();
	
	/*NOW PREPARE THE PIXELBUFFER AND DRAW VIRTUAL FLOOR FOR CASTING SHADOWS*/
	if (m_shadows)
	{
		//initialize only light source
		m_GLOUT->initLights();
		
		//prepare pixelbuffer for shadows
		m_GLOUT->preparePixelBuffer();
		
		//draw invisible floor for shadow projection
		m_GLOUT->drawBaseFloor(0.0, 0.0, 0.0, DEFAULT_FLOOR_SIZE);
		
		//turn the color and depth buffers back on
		m_GLOUT->endPixelBuffer();
		
		/*NOW CAST THE SHADOWS ON THE FLOOR AND KEEP IN PIXELBUFFER*/
		
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
	}
	
	//draw real objects
	glPushMatrix();
	{
		m_GLOUT->initLights();
		
		if (! m_shadows)
		{
			m_GLOUT->drawBaseFloor(0.0, 0.0, 0.0, DEFAULT_FLOOR_SIZE);
		}
		
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
	
	// send event to refresh Scene-Tree
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
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
		//clone assembly from selected
		GNRAssembly* a_copy = (*it)->clone();
		//move selected to world
		m_RootAssembly->addPart((*it));
		//remove selected
		m_Selected->delPart((*it));
		//copy clone in selected
		m_Selected->addPart(a_copy);
		//move assembly one width right
		a_copy->move(GNRVertex(a_copy->getWidthMeters()+0.5,0.0,0.0));
	}
	
	// send event to refresh Scene-Tree
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
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
	
	// send event to refresh Scene-Tree
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * draws a line, specified in the event to the 2D canvas
 * @param   GNRLineDrawEvent    event with information about the line
 * @access      public
 */
void GNRScene::drawLine(GNRLineDrawEvent& event)
{
	m_GLOUT = m_Canvas2D;
	m_GLCAM = m_GLCamera2D;
	
	//prepare and draw 2D top view of room
	m_GLOUT->prepareDraw();
	
	//set camera for scene
	m_GLCAM->render();
	
	/*NOW PREPARE THE PIXELBUFFER AND DRAW VIRTUAL FLOOR FOR CASTING SHADOWS*/
	if (m_shadows)
	{
		//initialize only light source
		m_GLOUT->initLights();
		
		//prepare pixelbuffer for shadows
		m_GLOUT->preparePixelBuffer();
		
		//draw invisible floor for shadow projection
		m_GLOUT->drawBaseFloor(0.0, 0.0, 0.0, DEFAULT_FLOOR_SIZE);
		
		//turn the color and depth buffers back on
		m_GLOUT->endPixelBuffer();
		
		/*NOW CAST THE SHADOWS ON THE FLOOR AND KEEP IN PIXELBUFFER*/
		
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
	}
	
	/*NOW DRAW ALL OBJECTS WITHOUT SHADOWS AND BLEND WITH SHADOWS*/
	
	//draw real objects
	glPushMatrix();
	{
		glPushMatrix();
		{
			m_GLOUT->initLights();
			
			if (! m_shadows)
			{
				m_GLOUT->drawBaseFloor(0.0, 0.0, 0.0, DEFAULT_FLOOR_SIZE);
			}
			
			m_RootAssembly->draw();
		}
		glPopMatrix();
		
		// draw line from start- to end-point
		float lineColor[4] = {1.0, 0.0, 0.0, 0.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  lineColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  lineColor);
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
	m_GLOUT->endDraw();
	
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
		m_RootAssembly->addPart((*it));
		m_Selected->delPart((*it));
		(*it)->setVisible(false);
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
	
	// send event to refresh Scene-Tree
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
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
	
	// send event to refresh Scene-Tree
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
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
	assembly->setVisible(true);
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
	
	// send event to refresh Scene-Tree
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * inserts a new hidden assembly to the hidden assembly
 * @param   GNRAssembly*    pointer to the assembly, that should be insert
 * @access      public
 */
void GNRScene::insertHiddenAssembly(GNRAssembly* assembly)
{
	//TODO
}

GNRSceneTreeNode* GNRScene::createSceneTree()
{
	// create scene tree
	GNRSceneTreeNode* scene = new GNRSceneTreeNode;
	scene->setName(wxT("Szene"));
	createSceneTree(m_RootAssembly, scene);
	
	// create trash tree
	GNRSceneTreeNode* trash = new GNRSceneTreeNode;
	trash->setName(wxT("Papierkorb"));
	createSceneTree(m_Trash, trash);
	
	// create root-Node and insert all other trees
	GNRSceneTreeNode* root = new GNRSceneTreeNode;
	root->addTreeNode(scene);
	root->addTreeNode(trash);
	return root;
}

void GNRScene::createSceneTree(GNRAssembly* assembly, GNRSceneTreeNode* node)
{
	if (assembly->getType() == IS_OBJECT || assembly->getType() == IS_PRIMITIVE)
	{
		GNRTreeSceneItemData* data = new GNRTreeSceneItemData;
		data->setName(assembly->getName());
		data->setAssembly(assembly);
		node->addTreeItem(data);
	}
	else if (assembly->getType() == IS_GROUP)
	{
		GNRSceneTreeNode* newNode = new GNRSceneTreeNode;
		newNode->setName(assembly->getName());
		node->addTreeNode(newNode);
		list<GNRAssembly*> parts = assembly->getPartList();
		for (list<GNRAssembly*>::const_iterator it = parts.begin(); it != parts.end(); ++it)
		{
			createSceneTree((*it), newNode);
		}
	}
	else if (assembly->getType() == IS_ROOT || assembly->getType() == IS_TRASH || assembly->getType() == IS_SELECTED)
	{
		list<GNRAssembly*> parts = assembly->getPartList();
		for (list<GNRAssembly*>::const_iterator it = parts.begin(); it != parts.end(); ++it)
		{
			createSceneTree((*it), node);
		}
	}
}
