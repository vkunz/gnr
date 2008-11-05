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
#include <wx/mstream.h>

#include "GNRApp.h"
#include "GNRGlobalDefine.h"
#include "GNRGLScreenshot.h"
#include "GNRPrimitiveCreator.h"
#include "GNROaxExport.h"
#include "GNROaxImport.h"
#include "GNRObjectImport.h"
#include "GNROpxExport.h"
#include "GNROpxImport.h"
#include "GNRObjOaxConverter.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "GNRMaterialLibrary.h"
GNRMaterialLibrary mtllib;
#warning "INFO: Has to be organized somewhere else?"
//!!quick && dirty!!


BEGIN_EVENT_TABLE(GNRApp, wxApp)
	EVT_GNR_NOTIFY(0, GNRApp::OnGNREvent)   //global event for redraw...
	EVT_GL_NOTIFY(0, GNRApp::OnGLEvent)     //event for mouse and move in GL...
	EVT_GNR_LINE_DRAW(0, GNRApp::OnLineDrawEvent)     //event to draw a line in gl
	EVT_GNR_CREATE_PRIMITIVE(0, GNRApp::OnCreatePrimitiveEvent)     //event to draw a line in gl
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
		
#if defined(__ATHOS_DEBUG__)
		// Create DebugFrame
		m_DebugFrame = new GNRDebugFrame(m_MainFrame);
		m_DebugFrame->Show(true);
		m_Log = new wxLogTextCtrl(m_DebugFrame->TextCtrl);
		m_Log->SetActiveTarget(m_Log);
#endif
		
		//build models
		m_Tests         = new GNRTests();
		m_Scene         = GNRScene::getInstance();
		m_MouseCtrl     = new GNRMouseController(m_Scene);
		
		m_TreeLibCtrl   = new GNRTreeLibraryController(m_TreeCtrlLib);
		m_TreeSceneCtrl = new GNRTreeSceneController(m_TreeCtrlScene);
		m_UndoRedo      = GNRUndoRedo::getInstance();
		
		m_Scene->setCanvas2D(m_Canvas2D);
		m_Scene->setCanvas3D(m_Canvas3D);
		
		//initialize whole menus
		initialSetup();
		
#warning "INFO: Who wants some test?"
		//start tests right here
#if defined(__ATHOS_DEBUG__)
		//m_Tests->sizeXsizeLoopsLoadClean(m_Scene,5,20);
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
	m_VerticalSplitter = new wxSplitterWindow(m_MainFrame, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME|wxSP_LIVE_UPDATE);
	m_VerticalSplitter->SetMinimumPaneSize(305);
	
	//create splitter for left panel with tree and models
	m_HorizontalSplitter_left = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME|wxSP_LIVE_UPDATE);
	m_HorizontalSplitter_left->SetMinimumPaneSize(100);
	
	//create splitter for right panel with two canvas
	m_HorizontalSplitter_right = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME|wxSP_LIVE_UPDATE);
	m_HorizontalSplitter_right->SetMinimumPaneSize(100);
	
	
	//show mainframe
	m_MainFrame->Show(true);
	
	//create tree and models panel
	m_TreePanelLibrary = new GNRTreePanelLibrary(m_HorizontalSplitter_left, wxID_ANY);
	m_TreePanelMyScene = new GNRTreePanelMyScene(m_HorizontalSplitter_left, wxID_ANY);
	
	//create TreeCntr
	m_TreeCtrlLib = new wxTreeCtrl(m_TreePanelLibrary, wxID_ANY, wxPoint(0, 0), m_TreePanelLibrary->GetSize(), wxTR_DEFAULT_STYLE, wxDefaultValidator, wxT("TreePanelLibrary"));
	m_TreeCtrlScene = new GNRTreeSceneCtrl(m_TreePanelMyScene, wxID_ANY, wxPoint(0, 0), m_TreePanelMyScene->GetSize(), wxTR_DEFAULT_STYLE, wxDefaultValidator, wxT("TreePanelMyScene"));
	
	//create two canvas panels
	m_Canvas2D = new GNRGLCanvas2D(m_HorizontalSplitter_right, -1);
	commonCtxt = m_Canvas2D->GetContext();
	m_Canvas3D = new GNRGLCanvas3D(m_HorizontalSplitter_right, commonCtxt, -1);
	
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
	
	m_VerticalSplitter->SetSashPosition(305,true);
	m_HorizontalSplitter_left->SetSashPosition(300,true);
	m_HorizontalSplitter_right->SetSashPosition(200,true);
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

void GNRApp::updateSize()
{
	// update size of m_TreeCtrlLib
	m_TreeCtrlLib->SetSize(m_TreePanelLibrary->GetSize());
	
	// update size of m_TreeCtrlScene
	m_TreeCtrlScene->SetSize(m_TreePanelMyScene->GetSize());
}

/**
 * process GNR-Notify-Event
 */
void GNRApp::OnGNREvent(GNRNotifyEvent& event)
{
	switch (event.getGNREventType())
	{
	case GLREFRESH:
		updateSplitters();
		m_Scene->glRefresh();
		break;
	case NEWROOM:
		m_Scene->newRoom();
		m_Scene->glRefresh();
		break;
	case OPXOPEN:
		OPXOpen(event.GetString());
		m_Scene->glRefresh();
		break;
	case OPXSAVE:
		OPXSave(event.GetString());
		m_Scene->glRefresh();
		break;
	case OAXIMPORT:
		OAXImport(event.GetString());
		m_Scene->glRefresh();
		break;
	case OAXEXPORT:
		OAXExport(event.getAssemblyDataPointer());
		//m_Scene->glRefresh();
		break;
	case OBJIMPORT:
		OBJImport(event.GetString());
		m_Scene->glRefresh();
		break;
	case OBJEXPORT:
		OBJExport(event.GetString());
		m_Scene->glRefresh();
		break;
	case TOOLBARCHANGE:
		m_MouseCtrl->setTranslation(event);
		break;
	case RESETCAMERA:
		m_Scene->resetCamera();
		m_Scene->glRefresh();
		break;
	case SNAPTOGRID:
		m_MouseCtrl->setSnapfunction(event);
		break;
	case PANELSIZE:
		updateSize();
		break;
	case SCREENSHOT:
		createScreenshot(event.GetString());
		break;
	case UNDO:
		m_UndoRedo->undo();
		m_Scene->glRefresh();
		break;
	case REDO:
		m_UndoRedo->redo();
		m_Scene->glRefresh();
		break;
	case CREATEGROUP:
		m_Scene->groupSelectedAssemblies();
		m_Scene->glRefresh();
		break;
	case MODIFYGROUP:
		m_Scene->ungroupSelectedAssemblies();
		m_Scene->glRefresh();
		break;
	case DELETESELECTED:
		m_Scene->deleteSelectedAssemblies();
		m_Scene->glRefresh();
		break;
	case CLONESELECTED:
		m_Scene->cloneSelectedAssemblies();
		m_Scene->glRefresh();
		break;
	case COPYSELECTED:
		m_Scene->copySelectedAssemblies();
		m_Scene->glRefresh();
		break;
	case CUTSELECTED:
		m_Scene->cutSelectedAssemblies();
		m_Scene->glRefresh();
		break;
	case INSERTCOPY:
		m_Scene->insertCopiedAssemblies();
		m_Scene->glRefresh();
		break;
	case HIDESELECTED:
		m_Scene->hideSelectedAssemblies();
		m_Scene->glRefresh();
		break;
	case SHOWHIDDEN:
//		m_Scene->showAssembly(event.getAssemblyPtr());
//		m_Scene->glRefresh();
		break;
	case UNDOCREATEGROUP:
//		m_Scene->ungroupOneAssembly(event.getAssemblyPtr());
//		m_Scene->glRefresh();
		break;
	case SETUNDOENABLED:
		m_MainFrame->setUndoEnabled(event.GetInt());
		break;
	case SETREDOENABLED:
		m_MainFrame->setRedoEnabled(event.GetInt());
		break;
	case CANCELCONVERTION:
		cancelConvertion();
		break;
	case TOGGLESHADOWS:
		m_Scene->toggleShadows(event.getBoolean());
		m_Scene->glRefresh();
		break;
	case DISPLAYLENGTH:
	{
		int length = (int)floor(1000.0 * event.getFloat());
		wxString str;
		str << wxT("Wandlänge: ") << length << wxT(" mm");
		m_MainFrame->getStatusbar()->SetStatusText(str);
		break;
	}
	case REFRESHSCENETREE:
		GNRSceneTreeNode* tree = m_Scene->createSceneTree();
		m_TreeSceneCtrl->updateTree(tree);
		break;
	}
}

/**
 * redirect GL GNR-Notify-Event to specific operations
 */
void GNRApp::OnGLEvent(GNRGLNotifyEvent& event)
{
	//if button goes down, switch mediator to current operation
	if (event.getMouseEvent().ButtonDClick(-1))
	{
		m_MouseCtrl->setSelected(event);
	}
	//if button goes down, switch mediator to current operation
	else if (event.getMouseEvent().ButtonDown(-1))
	{
		m_MouseCtrl->setMediator(event);
	}
	
	//if button is down, translate event to mediator
	else if (event.getMouseEvent().ButtonIsDown(-1))
	{
		m_MouseCtrl->activateMediator(event);
	}
	
	//if button goes up, create command-object for undo
	else if (event.getMouseEvent().ButtonUp(-1))
	{
		m_MouseCtrl->deactivateMediator();
	}
	
	//if event is scroll-event, translate event to mediator
	else if (event.getMouseEvent().GetWheelRotation())
	{
		m_MouseCtrl->setMediator(event);
		m_MouseCtrl->activateMediator(event);
	}
}

/**
 * handles line-draw-event to display a line in gl canvas
 * @access      private
 */
void GNRApp::OnLineDrawEvent(GNRLineDrawEvent& event)
{
	m_Scene->drawLine(event);
}

/**
 * handles createPrimitiveEvent and creates a new primitive
 * @access      private
 */
void GNRApp::OnCreatePrimitiveEvent(GNRCreatePrimitiveEvent& event)
{
	if (event.getPrimitiveType() == CUBOID)
	{
		GNRVertex origin(0.0,0.0,0.0);
		GNRAssembly* atomic;
		
		GNRPrimitiveCreator creator;
		
		//create smallest part of primitive
		atomic = creator.createCuboid(origin, origin, event.getDimensions());
		atomic->setType(IS_ATOMIC);
		
		//create new parent assembly (group of primitives)
		GNRAssembly* primitive = new GNRAssembly(wxT("wallcube"));
		
		//put information of whole group in parent
		primitive->setType(IS_PRIMITIVE);
		primitive->setCenterVertex(event.getPosition());
		primitive->setRotateVertex(event.getAngles());
		primitive->setWidth(event.getDimensions().getX());
		primitive->setHeight(event.getDimensions().getY());
		primitive->setDepth(event.getDimensions().getZ());
		
		//tell the parent what color his child has got
		primitive->setChildMaterial(atomic, mtllib.getMaterial(DEFAULT_IMPORT_COLOR));
		
		//insert cuboid in parent
		primitive->addPart(atomic);
		
		//put whole in the world
		m_Scene->insertAssembly(primitive);
	}
	
	m_Scene->glRefresh();
}

/**
 * handle opx open
 * @param       wxString        File to open.
 * @access      private
 */
void GNRApp::OPXOpen(wxString filename)
{
	// create importer and execute it
	GNROpxImport import(m_Scene, filename);
#if defined(__ATHOS_DEBUG__)
	wxLogDebug(wxT("Leider noch nicht implementiert!"));
#endif
}

/**
 * handle opx save
 * @param       wxString        File to save as.
 * @access      private
 */
void GNRApp::OPXSave(wxString filename)
{
	// create new opx export object
	GNROpxExport opxExport(m_Scene, filename);
}

/**
 * handle oax import
 * @param       wxString        File to import.
 * @access      private
 */
void GNRApp::OAXImport(wxString filename)
{
	// create importer and procceed
	GNROaxImport in(filename);
	
	// get assembly
	m_Scene->insertAssembly(in.getAssembly());
}

/**
 * handle oax export
 * @param       wxString        File to export to.
 * @access      private
 */
void GNRApp::OAXExport(GNRAssemblyData* data)
{
	// create new memory output stream
	wxMemoryOutputStream memOut;
	
	// pointer to wxOutputStream
	wxOutputStream* outStream = &memOut;
	
	// create new OaxExport - object
	GNROaxExport out(data, outStream);
	
	// create new memory input stream
	wxMemoryInputStream memIn(memOut);
	
	// pointer to wxInputStream
	wxInputStream* inStream = &memIn;
	
	// add new entry
	m_TreeLibCtrl->addEntry(data->m_name, data->m_category, *inStream);
	
	// successfull
	delete m_ObjOaxConv;
}

/**
 * handle obj import
 * @param       wxString        File to import.
 * @access      private
 */
void GNRApp::OBJImport(wxString filename)
{
	// create objoaxconv
	m_ObjOaxConv = new GNRObjOaxConverter(filename, m_TreeLibCtrl->getAllCategories());
}

/**
 * handle obj import
 * @param       wxString        File to export to.
 * @access      private
 */
void GNRApp::OBJExport(wxString filename)
{
#if defined(__ATHOS_DEBUG__)
	wxLogDebug(wxT("Leider noch nicht implementiert!"));
#endif
}

/**
 * handle screenshot-creation
 * @access      private
 */
void GNRApp::createScreenshot(wxString filename)
{
	m_Canvas3D->setActive();
	GNRGLScreenshot scr(filename);
}

/**
   * conververtion canceled
   * @access     private
  */
void GNRApp::cancelConvertion()
{
	delete m_ObjOaxConv;
}

/**
 * throw event for inital setup
 * @access      private
 */
void GNRApp::initialSetup()
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	
	gnrevent.setGNREventType(SNAPTOGRID);
	gnrevent.setSnapToGrid(SNAP_IN_DEFAULT_GRID);
	gnrevent.setSnapToAngle(SNAP_IN_DEFAULT_ANGLE);
	
	m_MouseCtrl->setSnapfunction(gnrevent);
	
	m_Scene->glRefresh();
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
