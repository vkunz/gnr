/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * main application is creating the main controller starting the program
 * @name        GNRApp.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/image.h>

#include "GNRApp.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

BEGIN_EVENT_TABLE(GNRApp, wxApp)
	EVT_GNR_NOTIFY(0, GNRApp::OnGNREvent)   //global event for redraw...
	EVT_GL_NOTIFY(0, GNRApp::OnGLEvent)     //event for mouse and move in GL...
END_EVENT_TABLE()

IMPLEMENT_APP(GNRApp);

/**
 * MAIN APP INIT
 */
bool GNRApp::OnInit()
{
	bool wxsOK = true;
	
	wxInitAllImageHandlers();
	
	if (wxsOK)
	{
		//build gui
		initFrames();
		
		//build models
		m_Scene         = new GNRScene();
		m_MouseCtrl     = new GNRMouseController(m_Scene);
		m_TreeCtrlLib   = new wxTreeCtrl();
		m_TreeCtrlScene = new wxTreeCtrl();
		
#if defined(__ATHOS_DEBUG__)
		// Create DebugFrame
		m_DebugFrame = new GNRDebugFrame(0);
		m_DebugFrame->Show(true);
		m_Log = new wxLogTextCtrl(m_DebugFrame->TextCtrl);
		m_Log->SetActiveTarget(m_Log);
#endif
	}
	
	return wxsOK;
}

/**
 * initialize all frames needed
 * @access      public
 */
void GNRApp::initFrames()
{
	m_MainFrame = new GNRMainFrame(0);
	
	//main splitter window
	m_VerticalSplitter = new wxSplitterWindow(m_MainFrame, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME);
	m_VerticalSplitter->SetMinimumPaneSize(200);
	
	//create splitter for left panel with tree and models
	m_HorizontalSplitter_left = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME);
	m_HorizontalSplitter_left->SetMinimumPaneSize(200);
	
	//create splitter for right panel with two canvas
	m_HorizontalSplitter_right = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME);
	m_HorizontalSplitter_right->SetMinimumPaneSize(200);
	
	//show mainframe
	m_MainFrame->Show(true);
	
	//create tree and models panel
	m_TreePanelLibrary = new GNRTreePanelLibrary(m_HorizontalSplitter_left, wxID_ANY);
	m_TreePanelMyScene = new GNRTreePanelMyScene(m_HorizontalSplitter_left, wxID_ANY);
	
	//create two canvas panels
	m_Canvas2D = new GNRGL2DCanvas(m_HorizontalSplitter_right, -1);
	commonCtxt = m_Canvas2D->GetContext();
	m_Canvas3D = new GNRGL3DCanvas(m_HorizontalSplitter_right, commonCtxt, -1);
	
	//initialize left and right splitter
	m_VerticalSplitter->Initialize(m_HorizontalSplitter_left);
	m_VerticalSplitter->Initialize(m_HorizontalSplitter_right);
	
	//initialize both treepanels
	m_HorizontalSplitter_left->Initialize(m_TreePanelLibrary);
	m_HorizontalSplitter_left->Initialize(m_TreePanelMyScene);
	
	//initialize both canvases
	m_HorizontalSplitter_right->Initialize(m_Canvas2D);
	m_HorizontalSplitter_right->Initialize(m_Canvas3D);
	
	//split right splitter in upper (2D) and lower (3D) canvas
	m_HorizontalSplitter_right->SplitHorizontally(m_Canvas2D, m_Canvas3D);
	
	//split left splitter in upper (library) and lower (myscene) treeview
	m_HorizontalSplitter_left->SplitHorizontally(m_TreePanelLibrary, m_TreePanelMyScene);
	
	//split vertical (main) splitter in left and right splitter
	m_VerticalSplitter->SplitVertically(m_HorizontalSplitter_left, m_HorizontalSplitter_right);
}

/**
 * update splitter dimensions
 * @access      public
 */
void GNRApp::updateSplitters()
{
	//update left, right and main splitter
	m_HorizontalSplitter_right->UpdateSize();
	m_HorizontalSplitter_left->UpdateSize();
	m_VerticalSplitter->UpdateSize();
}

/**
 * process GNR-Notify-Event
 */
void GNRApp::OnGNREvent(GNRNotifyEvent& event)
{
	switch (event.getGNREventType())
	{
	case XMLOpen:
//		controller->XMLOpen(event.GetString());
//		controller->glRefresh();
		break;
	case GLRefresh:
		glRefresh();
		break;
	case OBJImport:
//		controller->OBJImport(event.GetString());
//		controller->glRefresh();
		break;
	case NewRoom:
//		controller->newRoom();
//		controller->glRefresh();
		break;
	case ResetCamera:
//		controller->resetCamera();
//		controller->glRefresh();
		break;
	case ToolbarChange:
//		controller->toggleToolbar(event);
		break;
	}
}

/**
 * redirect GL GNR-Notify-Event to specific operations
 */
void GNRApp::OnGLEvent(GNRGLNotifyEvent& event)
{
	//switch mediator to current operation
	if (event.getMouseEvent().ButtonDown())
	{
		m_MouseCtrl->setMediator((buttonType)event.getMouseEvent().GetButton(), event.getCanvasID());
	}
	
	//force mouse controller to translate event to mediator
	if (event.getMouseEvent().ButtonIsDown(-1))
	{
		m_MouseCtrl->activateMediator(event);
	}
	
	glRefresh();
}

/**
 * refresh glcanvas frames (3d/2d)
 * @access      public
 */
void GNRApp::glRefresh()
{
	//update splitter dimensions
	updateSplitters();
	glRefresh2D();
	glRefresh3D();
	glRefresh2D();
}

/**
 * refresh 2D canvas
 * @access      public
 */
void GNRApp::glRefresh2D()
{
	//prepare and draw 2D top view of room
	m_Canvas2D->prepareDraw();
//	m_RootAssembly->draw();
	m_Canvas2D->endDraw();
}

/**
 * refresh 3D canvas
 * @access      public
 */
void GNRApp::glRefresh3D()
{
	//prepare and draw 3D view of room
	m_Canvas3D->prepareDraw();
//	m_GLCamera->render();
//	m_RootAssembly->draw();
	m_Canvas3D->endDraw();
}


// Code unser im Repo,
// bugfrei seien Deine Quellen.
// Dein Commit komme.
// Dein Bild geschehe,
// wie im Repo, so auch lokal.
// Unser taegliches Bild gib uns heute,
// Und vergib uns unsere Fehler,
// wie auch wir vergeben dem Compiler.
// Und fuehre uns nicht in Versuchung,
// sondern erloese uns vom Proprietary.
