/**
 * Scene
 * @name        Scene.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "Scene.h"
#include "NotifyEvent.h"
#include "GlobalDefine.h"
#include "TreeSceneItemData.h"

// initialize pointer
Scene* Scene::pinstance = 0;

/**
 * construct scene and two assemblies (scene and grouper) plus
 * two cameras for 2D and 3D
 */
Scene::Scene()
{
	m_shadows = SHADOWS_DEFAULT;
	
	initContainers();
	
	m_GLCamera2D    = new GLCamera();
	m_GLCamera3D    = new GLCamera();
	
	m_canvas2DActive = true;
	
	resetCamera();
}

/**
 * destruct scene and two assemblies (scene and grouper) plus
 * two cameras for 2D and 3D
 */
Scene::~Scene()
{
	destroyContainers();
	
	delete m_GLCamera2D;
	delete m_GLCamera3D;
}

/**
 * creates a new class if not instantiated or returns a pointer to the object if already
 * instantiated before
 * two cameras for 2D and 3D
 */
Scene* Scene::getInstance()
{
	if (pinstance == 0)
	{
		pinstance = new Scene;
	}
	return pinstance;
}

/**
 * set actual hit assembly id
 * @param[in]		assembly			pointer to assembly
 */
void Scene::setAssembly(Assembly* assembly)
{
	m_Assembly = assembly;
}

/**
 * get actual assembly pointer
 * @return      Assembly*    pointer to act. assembly
 */
Assembly* Scene::getAssembly()
{
	return m_Assembly;
}

/**
 * get root assembly pointer
 * @return      Assembly*    pointer to root assembly
 */
Assembly* Scene::getRootAssembly()
{
	return m_RootAssembly;
}

/**
 * get pointer to 2D cam
 * @return      Assembly*    pointer to 2D cam
 */
GLCamera* Scene::getGLCamera2D()
{
	return m_GLCamera2D;
}

/**
 * get pointer to 3D cam
 * @return      Assembly*    pointer to 3D cam
 */
GLCamera* Scene::getGLCamera3D()
{
	return m_GLCamera3D;
}


/**
 * toggles shadows on and off
 * @param[in]		status			boolean status of shadows active
 */
void Scene::toggleShadows(bool status)
{
	m_shadows = status;
}

/**
 * init whole world of containers
 */
void Scene::initContainers()
{
	m_Assembly = NULL;
	
	m_RootAssembly  = new Assembly(IS_ROOT,        wxT("scene"));
	m_Selected      = new Assembly(IS_SELECTED,    wxT("selected"));
	
	//put selected assembly in real world
	m_RootAssembly->addPart(m_Selected);
	
	m_Trash         = new Assembly(IS_TRASH,       wxT("trash"));
	m_Duplicator    = new Assembly(IS_DUPLICATOR,  wxT("duplicator"));
	m_Originals     = new Assembly(IS_ORIGINAL,    wxT("originals"));
}

/**
 * kill whole world of containers
 */
void Scene::destroyContainers()
{
	//disconnect selected part
	m_RootAssembly->delPart(m_Selected);
	
	//selected is killed, then root
	delete m_Selected;
	delete m_RootAssembly;
	
	//kill all temp containers
	delete m_Trash;
	delete m_Duplicator;
	delete m_Originals;
}

/**
 * clean up whole world
 */
void Scene::newRoom()
{
	destroyContainers();
	initContainers();
	resetCamera();
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * resets the camera to initial state
 */
void Scene::resetCamera()
{
	//reset 2D cam to default (DONT SET Z TO ZERO!)
	m_GLCamera2D->setCamera(0.001,12.0,0.001,-90.0,0.0,0.0);
	
	//reset 3D cam to default
	m_GLCamera3D->setCamera(0.0,4.0,10.0,-25.0,0.0,0.0);
}

void Scene::setCanvas2D(GLCanvas2D* p)
{
	m_Canvas2D = p;
}

void Scene::setCanvas3D(GLCanvas3D* p)
{
	m_Canvas3D = p;
}

GLCanvas2D* Scene::getCanvas2D()
{
	return m_Canvas2D;
}

GLCanvas3D* Scene::getCanvas3D()
{
	return m_Canvas3D;
}

/**
 * refresh glcanvas frames (3d/2d)
 */
void Scene::glRefresh()
{
	glRefresh3D();
	if (m_canvas2DActive == true)
	{
		glRefresh2D();
	}
}

/**
 * refresh defines canvas with cam and cast shadows
 */
void Scene::glRefreshCanvas()
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
 */
void Scene::glRefresh2D()
{
	m_GLOUT = m_Canvas2D;
	m_GLCAM = m_GLCamera2D;
	glRefreshCanvas();
}

/**
 * refresh only 3D canvas
 */
void Scene::glRefresh3D()
{
	m_GLOUT = m_Canvas3D;
	m_GLCAM = m_GLCamera3D;
	glRefreshCanvas();
}

/**
 * delete all selected assemblies (move to trash container)
 */
void Scene::deleteSelectedAssemblies()
{
	list<Assembly*> parts = m_Selected->getPartList();
	
	for (list<Assembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		m_Trash->addPart((*it));
		m_Selected->delPart((*it));
	}
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * reset selected assemblies on ground
 */
void Scene::resetSelectedAssemblies()
{
	list<Assembly*> parts = m_Selected->getPartList();
	
	for (list<Assembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		(*it)->resetOnGround();
	}
}

/**
 * empty trash bin
 */
void Scene::deleteTrashAssemblies()
{
	list<Assembly*> trash = m_Trash->getPartList();
	
	for (list<Assembly*>::iterator it = trash.begin(); it != trash.end(); ++it)
	{
		//it is an original and there are some clones in the scene
		if ((*it)->getOrigin() == NULL && m_RootAssembly->findCloneOf((*it)))
		{
			//save original, will be killed in
			// destructor or on new room
			m_Originals->addPart((*it));
			m_Trash->delPart((*it));
		}
	}
	
	//delete trash and create new one
	delete m_Trash;
	
	m_Trash = new Assembly(IS_TRASH, wxT("trash"));
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * query originals, trash and scene for original object
 * @param[in]		hash			  double md5 hash of assembly
 * @return      		Assembly*        found original or NULL
 */
Assembly* Scene::getOrigialFromHash(const wxString hash)
{
	Assembly* original;
	
	//first query all originals for pointer
	original = m_Originals->getHashOriginal(hash);
	
	if (original != NULL)
	{
		return original;
	}
	
	//second query trash for pointer
	original = m_Trash->getHashOriginal(hash);
	
	if (original != NULL)
	{
		return original;
	}
	
	//and last query root for pointer
	original = m_RootAssembly->getHashOriginal(hash);
	
	//return pointer or NULL from assembly
	return original;
}

/**
 * delete a given assembly (move to trash container)
 * @param[in]		assembly			pointer to assembly
 */
void Scene::deleteAssembly(Assembly* assembly)
{
	// delete assembly from parent
	assembly->getParent()->delPart(assembly);
	
	m_Trash->addPart(assembly);
	
	glRefresh();
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * clone all selected assemblies
 */
void Scene::cloneSelectedAssemblies()
{
	list<Assembly*> parts = m_Selected->getPartList();
	
	for (list<Assembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		//clone assembly from selected
		Assembly* a_copy = (*it)->clone();
		//move selected to world
		m_RootAssembly->addPart((*it));
		//remove selected
		m_Selected->delPart((*it));
		//copy clone in selected
		m_Selected->addPart(a_copy);
		//move assembly one width right
		a_copy->move(Vertex(a_copy->world_dimension().getX(), 0.0f, 0.0f));
	}
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * copy all selected assemblies
 */
void Scene::copySelectedAssemblies()
{
	delete m_Duplicator;
	m_Duplicator = new Assembly(IS_DUPLICATOR,  wxT("duplicator"));
	
	list<Assembly*> parts = m_Selected->getPartList();
	
	for (list<Assembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		Assembly* a_copy = (*it)->clone();
		m_Duplicator->addPart(a_copy);
	}
}

/**
 * cut all selected assemblies
 */
void Scene::cutSelectedAssemblies()
{
	delete m_Duplicator;
	m_Duplicator = new Assembly(IS_DUPLICATOR,  wxT("duplicator"));
	
	list<Assembly*> parts = m_Selected->getPartList();
	
	for (list<Assembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		Assembly* a_copy = (*it)->clone();
		m_Duplicator->addPart(a_copy);
		m_Selected->delPart((*it));
	}
}

/**
 * insert all copied assemblies
 */
void Scene::insertCopiedAssemblies()
{
	list<Assembly*> parts = m_Duplicator->getPartList();
	
	for (list<Assembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		Assembly* a_copy = (*it)->clone();
		m_Selected->addPart(a_copy);
	}
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * draws a line, specified in the event to the 2D canvas
 * @param[in]   	event    	event with information about the line
 */
void Scene::drawLine(LineDrawEvent& event)
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
			//should be like the default wallsize
			float line_width = 100.0/(float)m_GLCamera2D->getDistance();
			
			//set line width in gl
			glLineWidth(line_width);
			
			//draw wall with lines
			if (event.GetInt() == 1)
			{
				//draw wall from start- to end-point 2 colored
				float lineColor1[4] = {0.3, 0.0, 0.0, 0.0};
				float lineColor2[4] = {1.0, 0.0, 0.0, 0.0};
				
				glMaterialfv(GL_FRONT, GL_EMISSION, lineColor1);
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lineColor1);
				glBegin(GL_LINES);
				{
					glVertex3f(event.getStartPoint().getX(), event.getStartPoint().getY(), event.getStartPoint().getZ());
					glVertex3f(event.getEndPoint().getX(), event.getEndPoint().getY(), event.getEndPoint().getZ());
					glVertex3f(event.getEndPoint().getX(), event.getEndPoint().getY(), event.getEndPoint().getZ());
					glMaterialfv(GL_FRONT, GL_EMISSION, lineColor2);
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lineColor2);
					glVertex3f(event.getEndPoint().getX(), event.getEndPoint().getY()+WALLHEIGHT, event.getEndPoint().getZ());
				}
				glEnd();
				
				//draw line from start to end
				glMaterialfv(GL_FRONT, GL_EMISSION, lineColor2);
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lineColor2);
				glBegin(GL_LINES);
				{
					glVertex3f(event.getEndPoint().getX(), event.getEndPoint().getY()+WALLHEIGHT, event.getEndPoint().getZ());
					glVertex3f(event.getStartPoint().getX(), event.getStartPoint().getY()+WALLHEIGHT, event.getStartPoint().getZ());
					glVertex3f(event.getStartPoint().getX(), event.getStartPoint().getY()+WALLHEIGHT, event.getStartPoint().getZ());
					glMaterialfv(GL_FRONT, GL_EMISSION, lineColor1);
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lineColor1);
					glVertex3f(event.getStartPoint().getX(), event.getStartPoint().getY(), event.getStartPoint().getZ());
				}
				glEnd();
			}
			//draw line only (measure)
			else
			{
				//draw wall from start- to end-point 2 colored
				float lineColor1[4] = {0.0, 1.0, 0.0, 0.0};
				
				glMaterialfv(GL_FRONT, GL_EMISSION, lineColor1);
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lineColor1);
				glBegin(GL_LINES);
				{
					glVertex3f(event.getStartPoint().getX(), event.getStartPoint().getY(), event.getStartPoint().getZ());
					glVertex3f(event.getEndPoint().getX(), event.getEndPoint().getY(), event.getEndPoint().getZ());
				}
				glEnd();
			}
			
			//turn on lights
			m_GLOUT->initLights();
			
			//if shadows disabled draw floor again
			if (! m_shadows)
			{
				m_GLOUT->drawBaseFloor(0.0, 0.0, 0.0, DEFAULT_FLOOR_SIZE);
			}
			
			//draw world
			m_RootAssembly->draw();
		}
		glPopMatrix();
	}
	glPopMatrix();
	
	//put output to screen
	m_GLOUT->endDraw();
	
	// calculate length of the line
	float x = event.getEndPoint().getX() - event.getStartPoint().getX();
	float y = event.getEndPoint().getY() - event.getStartPoint().getY();
	float z = event.getEndPoint().getZ() - event.getStartPoint().getZ();
	Vertex myvec(x, y, z);
	int length = (int)floor(1000.0 * myvec.length());
	
	//create string for statusbar
	wxString str;
	str << wxT("L" auml "nge: ") << length << wxT(" mm");
	
	// send event to display length
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(DISPLAYLENGTH);
	gnrevent.SetString(str);
	ProcessEvent(gnrevent);
}

/**
 * hide all selected assemblies (move to hidden container)
 */
void Scene::hideSelectedAssemblies()
{
	list<Assembly*> parts = m_Selected->getPartList();
	
	for (list<Assembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		m_RootAssembly->addPart((*it));
		m_Selected->delPart((*it));
		(*it)->setVisible(false);
	}
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * group all selected assemblies and move to root
 */
void Scene::groupSelectedAssemblies()
{
	list<Assembly*> parts = m_Selected->getPartList();
	
	if (parts.size() < 1)
	{
		//no or only one part, don't waste time
		return;
	}
	
	Assembly* group = new Assembly(IS_GROUP, wxT("Gruppe"));
	
	float min[3] = {SIZE_MAXIMUM_VALUE,SIZE_MAXIMUM_VALUE,SIZE_MAXIMUM_VALUE};
	float max[3] = {-SIZE_MAXIMUM_VALUE,-SIZE_MAXIMUM_VALUE,-SIZE_MAXIMUM_VALUE};
	
	//first pass to get maximum cube and new center of group
	for (list<Assembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		//kill possible empty groups in container
		if ((*it)->getPartList().size() < 1)
		{
			m_Selected->delPart(*it);
			continue;
		}
		minmax(min[0], max[0], (*it)->position().getX());
		minmax(min[1], max[1], (*it)->position().getY());
		minmax(min[2], max[2], (*it)->position().getZ());
	}
	
	//build new center as vertex for better calculation
	Vertex new_center((max[0]+min[0])/2.0, (max[1]+min[1])/2.0, (max[2]+min[2])/2.0);
	
	//move group center to new center
	group->position() = new_center;
	group->dimension().setY(max[1]+min[1]);
	//store obj center as vertex
	Vertex obj_center;
	
	//put all assemblies in the selected container
	for (list<Assembly*>::iterator it = parts.begin(); it != parts.end(); ++it)
	{
		//store old center
		obj_center = (*it)->position();
		
		//add part to new group and remove from selection
		group->addPart((*it));
		m_Selected->delPart((*it));
		
		//modify center relative to new center
		obj_center = obj_center - new_center;
		(*it)->position() = obj_center;
	}
	
	//put new group in the world
	m_RootAssembly->addPart(group);
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * ungroup selected group and move all parts to selected container
 */
void Scene::ungroupSelectedAssemblies()
{
	list<Assembly*> sel_parts = m_Selected->getPartList();
	list<Assembly*> grp_parts;
	
	if (sel_parts.size() < 1)
	{
		//no or only one part, don't waste time
		return;
	}
	
	Vertex grp_center, grp_rotate, obj_center, ptr_object, ptr_rotate;
	
	//find all groups and free them
	for (list<Assembly*>::iterator it = sel_parts.begin(); it != sel_parts.end(); ++it)
	{
		//only for groups in the selected container
		if ((*it)->isType(IS_GROUP))
		{
			//get partlist iterator
			grp_parts  = (*it)->getPartList();
			//save center of group
			grp_center = (*it)->position();
			//save old rotation of whole group
			grp_rotate = (*it)->rotation();
			
			//correct position of all group members
			for (list<Assembly*>::iterator child_it = grp_parts.begin(); child_it != grp_parts.end(); ++child_it)
			{
				//move assembly from group to IS_SELECTED in (0|0|0)
				m_Selected->addPart((*child_it));
				(*it)->delPart((*child_it));
				
				//save old relative position of child from group center
				ptr_object = (*child_it)->position();
				ptr_rotate = (*child_it)->rotation();
				
				//restore rotation from group to child around center
				ptr_object.rotate(grp_rotate);
				
				//calculate new position of child relative to (0|0|0)
				obj_center = ptr_object + grp_center;
				
				//rotate child in same way as group and set new center
				(*child_it)->rotation() = grp_rotate + ptr_rotate;
				(*child_it)->position() = obj_center;
			}
			//remove group container from his parent
			m_Selected->delPart(*it);
		}
	}
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * restore assembly (move from trash container to root)
 * @param[in]		assembly			pointer to assembly
 */
void Scene::restoreAssembly(Assembly* assembly)
{
	if (assembly != NULL)
	{
		m_RootAssembly->addPart(assembly);
		m_Trash->delPart(assembly);
	}
	
	glRefresh();
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * show actual assembly again
 * @param[in]		assembly			pointer to assembly
 */
void Scene::showAssembly(Assembly* assembly)
{
	assembly->setVisible(true);
	
	// redraw scene
	glRefresh();
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * hide actual assembly
 * @param[in]		assembly			pointer to assembly
 */
void Scene::hideAssembly(Assembly* assembly)
{
	assembly->setVisible(false);
	
	// redraw scene
	glRefresh();
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * toggle selected assembly (later on CTRL
 * @param[in]		assembly			pointer to assembly
 */
void Scene::selectAssembly(Assembly* assembly)
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
	
	// send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
}

/**
 * calculate min max values
 * @param       	min       	new minium value
 * @param       	max       	new maximum value
 * @param[in]       	value       	value to check for changes
 */
void Scene::minmax(float& min,float& max,float value)
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
 * @param[in]		assembly			pointer to assembly
 */
void Scene::insertAssembly(Assembly* assembly)
{
	//put new assembly on ground
	assembly->putOnGround();
	
	//add assembly to root node
	m_RootAssembly->addPart(assembly);
	
	
	//refresh both
	refreshTreeAndCanvas();
}

/**
 * refresh tree and canvas
 */
void Scene::refreshTreeAndCanvas()
{
	//refresh canvas
	glRefresh();
	
	//send event to refresh Scene-Tree
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REFRESHSCENETREE);
	ProcessEvent(gnrevent);
	
	glRefresh();
}

/**
 * get pointer to trash container
 * @return		GRNAssembly* 		pointer to trash
 */
Assembly* Scene::getTrash()
{
	return m_Trash;
}

/**
 * sets the canvas 2d active or not
 * @param[in]       bool            bool-status
 */
void Scene::setCanvas2DActive(bool status)
{
	m_canvas2DActive = status;
}
