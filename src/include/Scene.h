/**
 * Scene
 * @name        Scene.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _SCENE_H_
#define _SCENE_H_

#include <wx/event.h>
#include <wx/string.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

class Assembly;
class GLCamera;
class GLCanvas;
class GLCanvas2D;
class GLCanvas3D;
class LineDrawEvent;

class Scene: public wxEvtHandler
{
private:
	static Scene* pinstance;

	//pointer for scene details
	Assembly*    m_RootAssembly;

	//pointer to separate containers
	Assembly*    m_Selected;
	Assembly*    m_Trash;
	Assembly*    m_Duplicator;
	Assembly*    m_Originals;

	//both cameras
	GLCamera*    m_GLCamera2D;
	GLCamera*    m_GLCamera3D;

	//pointer to canvas
	GLCanvas2D*  m_Canvas2D;
	GLCanvas3D*  m_Canvas3D;

	bool         m_canvas2DActive;

	GLCanvas*    m_GLOUT;
	GLCamera*    m_GLCAM;

	//ID of actual selected assembly
	Assembly* m_Assembly;

	bool m_shadows;

	void glRefreshCanvas();
	void initContainers();
	void destroyContainers();

protected:
	Scene();

public:
	static Scene* getInstance();

	virtual ~Scene();

	Assembly* getRootAssembly();
	Assembly* getHiddden();
	Assembly* getTrash();
	Assembly* getAssembly();
	Assembly* getOrigialFromHash(const wxString hash);
	GLCamera* getGLCamera2D();
	GLCamera* getGLCamera3D();

	void setAssembly(Assembly* assembly);
	void setCanvas2D(GLCanvas2D* p);
	void setCanvas3D(GLCanvas3D* p);
	void setCanvas2DActive(bool status);
	GLCanvas2D* getCanvas2D();
	GLCanvas3D* getCanvas3D();

	void newRoom();
	void resetCamera();

	void glRefresh();
	void glRefresh2D();
	void glRefresh3D();

	void toggleShadows(bool status);
	void drawLine(LineDrawEvent& event);
	void refreshTreeAndCanvas();

	void deleteSelectedAssemblies();
	void hideSelectedAssemblies();
	void groupSelectedAssemblies();
	void ungroupSelectedAssemblies();
	void cloneSelectedAssemblies();
	void copySelectedAssemblies();
	void insertCopiedAssemblies();
	void cutSelectedAssemblies();
	void deleteTrashAssemblies();
	void resetSelectedAssemblies();

	void showAssembly(Assembly* assembly);
	void hideAssembly(Assembly* assembly);
	void deleteAssembly(Assembly* assembly);
	void restoreAssembly(Assembly* assembly);
	void selectAssembly(Assembly* assembly);
	void minmax(float& min,float& max,float value);

	void insertAssembly(Assembly* assembly);
};

#endif // _SCENE_H_
