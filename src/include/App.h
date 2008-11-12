/**
 * App
 * @name        App.h
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef APP_H
#define APP_H

#include <wx/app.h>
#include <wx/glcanvas.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/wfstream.h>

#include "CreatePrimitiveEvent.h"
#include "GLCanvas2D.h"
#include "GLCanvas3D.h"
#include "GLNotifyEvent.h"
#include "LineDrawEvent.h"
#include "ObjOaxConverter.h"
#include "MainFrame.h"
#include "MouseController.h"
#include "NotifyEvent.h"
#include "ProgressFrame.h"
#include "Scene.h"
#include "TreeControlEvent.h"
#include "TreeLibraryController.h"
#include "TreeLibraryCtrl.h"
#include "TreeSceneController.h"
#include "TreePanelLibrary.h"
#include "TreePanelMyScene.h"
#include "TreeSceneCtrl.h"
#include "UndoRedo.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#include "DebugFrame.h"
#include "Tests.h"
#endif

class App : public wxApp
{
private:

	//eventhandler
	void OnGNREvent(NotifyEvent& event);
	void OnGNRTreeEvent(TreeControlEvent& event);
	void OnGLEvent(GLNotifyEvent& event);
	void OnLineDrawEvent(LineDrawEvent& event);
	void OnCreatePrimitiveEvent(CreatePrimitiveEvent& event);
	
	//functions
	void initFrames();
	void updateSplitters();
	void updateSize();
	void initialSetup();
	
	// MainFrame Menu-functions
	void OPXOpen(wxString filename);
	void OPXSave(wxString filename);
	void OAXImport(wxString filename);
	void OAXExport(wxString reference);
	void OBJImport(wxString filename);
	void OBJExport(wxString filename);
	
	void createScreenshot(wxString filename);
	void createPrimitve(NotifyEvent& event);
	
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

#endif // APP_H
