/**
 * App
 * @name        App.h
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _APP_H_
#define _APP_H_

#include <wx/app.h>
#include <wx/glcanvas.h>
#include <wx/splitter.h>

/*
#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#include "DebugFrame.h"
#include "Tests.h"
#endif
*/
#if defined(__ATHOS_DEBUG__)
class DebugFrame;
class Tests;
#endif

class AssemblyData;
class CreatePrimitiveEvent;
class GLCanvas2D;
class GLCanvas3D;
class GLKeyEvent;
class GLNotifyEvent;
class KeyController;
class LineDrawEvent;
class MainFrame;
class MouseController;
class NotifyEvent;
class ObjOaxConverter;
class ProgressFrame;
class Scene;
class TreeControlEvent;
class TreeLibraryController;
class TreeLibraryCtrl;
class TreePanelLibrary;
class TreePanelMyScene;
class TreeSceneController;
class TreeSceneCtrl;
class UndoRedo;

class App : public wxApp
{
private:

	//eventhandler
	void OnGNREvent(NotifyEvent& event);
	void OnGNRTreeEvent(TreeControlEvent& event);
	void OnGLEvent(GLNotifyEvent& event);
	void OnLineDrawEvent(LineDrawEvent& event);
	void OnCreatePrimitiveEvent(CreatePrimitiveEvent& event);
	void OnKeyPressed(GLKeyEvent& event);

	//functions
	void initFrames();
	void updateSplitters();
	void updateSize();
	void initialSetup();
	void sashRefresh();

	// MainFrame Menu-functions
	void OPXOpen(wxString filename);
	void OPXSave(wxString filename);
	void OAXImport(wxString filename);
	void OAXExport(wxString reference);
	void OBJImport(wxString filename);
	void OBJExport(wxString filename);

	void createScreenshot(wxString filename);
	void createPrimitive(NotifyEvent& event);

	void cancelConvertion();
	void ObjOaxConversion(AssemblyData* data);

	void setCanvas2DActive(bool status);

	//attributes
	//treectrl
	TreeLibraryCtrl* m_TreeCtrlLib;
	TreeSceneCtrl* m_TreeCtrlScene;

	//manges the treectrl
	TreeLibraryController* m_TreeLibCtrl;
	TreeSceneController* m_TreeSceneCtrl;

	// Pointer to progressFrame
	ProgressFrame* m_progFrame;

	//pointer to ObjOaxConverter
	ObjOaxConverter* m_ObjOaxConv;

	TreePanelLibrary* m_TreePanelLibrary;
	TreePanelMyScene* m_TreePanelMyScene;

	UndoRedo* m_UndoRedo;

	Scene* m_Scene;
	MouseController* m_MouseCtrl;
	KeyController*   m_KeyCtrl;
	MainFrame* m_MainFrame;

	GLCanvas2D* m_Canvas2D;
	GLCanvas3D* m_Canvas3D;
	wxGLContext* commonCtxt;

	wxSplitterWindow* m_HorizontalSplitter_left;
	wxSplitterWindow* m_HorizontalSplitter_right;
	wxSplitterWindow* m_VerticalSplitter;

#if defined(__ATHOS_DEBUG__)
	DebugFrame* m_DebugFrame;
	Tests* m_Tests;
	wxLog* m_Log;
#endif

	DECLARE_EVENT_TABLE();

public:

	virtual bool OnInit();
};

#endif // _APP_H_
