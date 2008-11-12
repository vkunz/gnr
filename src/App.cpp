/**
 * main application is creating the main controller starting the program
 * @note        [DONE]
 * @name        App.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 * @brief       main application is creating the main controller starting the program
 */

/*! \mainpage   GNR 3D Raumplaner - Die Einrichtungssoftware
 *
 *  \section    section_1   Das Vorgehensmodell - XP
 *
 *  Unser gew&auml;hltes Vorgehensmodell - Extreme-Programming im eigentlichen Sinne - l&auml;sst keine detaillierte
 *  Planung vorausgehen. Es ist vielmehr eine agile Programmiermethode die bevorstehende Aufgabe zu l&ouml;sen.
 *  Leider ist unser Team etwas klein geraten, was uns im Punkt "Risikomanagement" dazu gezwungen hat, m&ouml;glichst
 *  schnelle - wenn auch nur suboptimale - L&ouml;sungen zu finden und weiter zu verfolgen.
 *  Im Laufe des Projekts sind auf diese Weise recht brauchbare Ans&auml;tze entstanden, wobei wir auf der anderen
 *  Seite auch enorme Probleme an manchen Stellen produziert haben. Diese Fehler w&auml;hrend der eigentlichen
 *  Entwicklung zu beseitigen ist dabei die gr&ouml;&szlig;te Herausforderung.
 *
 *  \section    section_2   Der 3D Raumplaner
 *
 *  Unsere Aufgabe ist es nun - in knapp sechs Wochen - einen Raumplaner zu entwickeln, der folgende
 *  Anforderungen erf&uuml;llt:
 *  \li Grafische Modellierung von R&auml;umen und Einrichtungskomponenten
 *  \li Realistische 3D-Darstellung
 *  \li Visuelles Platzieren von Einrichtungsgegenst&auml;nden bei freier Wahl des Beobachterstandpunkts
 *  \li Intelligente Modellierungsunterst&uuml;tzung durch Schnappfunktionen
 *  \li Verf&uuml;gbarkeit geeigneter Messwerkzeuge zur exakt ma&szlig;stabsgerechten Modellierung
 *  \li Einlesen und Abspeichern von Einrichtungskomponenten im .obj/.mtl-Format
 *  \li Verlustfreie Speicherung eines Modells in einem propriet&auml;ren XML-Format
 *  \li Export eines Modells im .obj/.mtl-Format
 *  \li Export von 3D-Darstellungen in g&auml;ngigen Grafikformaten
 *  \li Standardisierte Schnittstelle zum Austausch von Modellen und Ansichtsinformationen
 *
 */

#include <wx/filedlg.h>
#include <wx/image.h>
#include <wx/mstream.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>

#include "App.h"
#include "CreateCuboidFrame.h"
#include "GlobalDefine.h"
#include "GLScreenshot.h"
#include "PrimitiveCreator.h"
#include "OaxExport.h"
#include "OaxImport.h"
#include "ObjectImport.h"
#include "OpxExport.h"
#include "OpxImport.h"
#include "ObjOaxConverter.h"
#include "TreeControlEvent.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

BEGIN_EVENT_TABLE(App, wxApp)
	EVT_GNR_TREE_CONTROL(0, App::OnGNRTreeEvent)                 // tree events
	EVT_GNR_NOTIFY(0, App::OnGNREvent)                           //global event for redraw...
	EVT_GL_NOTIFY(0, App::OnGLEvent)                             //event for mouse and move in GL...
	EVT_GNR_LINE_DRAW(0, App::OnLineDrawEvent)                   //event to draw a line in gl
	EVT_GNR_CREATE_PRIMITIVE(0, App::OnCreatePrimitiveEvent)     //event to draw a line in gl
END_EVENT_TABLE()

IMPLEMENT_APP(App);

/**
 * MAIN APP INIT
 */
bool App::OnInit()
{
	bool wxsOK = true;
	
	wxInitAllImageHandlers();
	
	if (wxsOK)
	{
		//build gui
		initFrames();
		
#if defined(__ATHOS_DEBUG__)
		//create DebugFrame
		m_DebugFrame = new DebugFrame(m_MainFrame);
		m_DebugFrame->Show(true);
		m_Log = new wxLogTextCtrl(m_DebugFrame->TextCtrl);
		m_Log->SetActiveTarget(m_Log);
		//build test models
		m_Tests         = new Tests();
#endif
		
		m_Scene         = Scene::getInstance();
		m_MouseCtrl     = new MouseController(m_Scene);
		
		m_TreeLibCtrl   = new TreeLibraryController(m_TreeCtrlLib);
		m_TreeSceneCtrl = new TreeSceneController(m_TreeCtrlScene);
		m_UndoRedo      = UndoRedo::getInstance();
		
		m_Scene->setCanvas2D(m_Canvas2D);
		m_Scene->setCanvas3D(m_Canvas3D);
		
		//initialize whole menus
		initialSetup();
	}
	
	return wxsOK;
}

/**
 * initialize all frames needed
 */
void App::initFrames()
{
	//create main frame
	m_MainFrame = new MainFrame(0);
	
	//main splitter window
	m_VerticalSplitter = new wxSplitterWindow(m_MainFrame, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME|wxSP_LIVE_UPDATE);
	m_VerticalSplitter->SetMinimumPaneSize(200);
	
	//create splitter for left panel with tree and models
	m_HorizontalSplitter_left = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME|wxSP_LIVE_UPDATE);
	m_HorizontalSplitter_left->SetMinimumPaneSize(100);
	
	//create splitter for right panel with two canvas
	m_HorizontalSplitter_right = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME|wxSP_LIVE_UPDATE);
	m_HorizontalSplitter_right->SetMinimumPaneSize(100);
	
	//create tree and models panel
	m_TreePanelLibrary = new TreePanelLibrary(m_HorizontalSplitter_left, wxID_ANY);
	m_TreePanelMyScene = new TreePanelMyScene(m_HorizontalSplitter_left, wxID_ANY);
	
	//create TreeCntr
	m_TreeCtrlLib = new TreeLibraryCtrl(m_TreePanelLibrary, wxID_ANY);
	m_TreeCtrlScene = new TreeSceneCtrl(m_TreePanelMyScene, wxNewId(), wxPoint(0, 0), m_TreePanelMyScene->GetSize(), wxTR_DEFAULT_STYLE, wxDefaultValidator, wxT("TreePanelMyScene"));
	
	//create two canvas panels
	m_Canvas2D = new GLCanvas2D(m_HorizontalSplitter_right, -1);
	commonCtxt = m_Canvas2D->GetContext();
	m_Canvas3D = new GLCanvas3D(m_HorizontalSplitter_right, commonCtxt, -1);
	
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
	
	m_VerticalSplitter->SetSashPosition(225,true);
	m_HorizontalSplitter_left->SetSashPosition(300,true);
	m_HorizontalSplitter_right->SetSashPosition(225,true);
	
	//show mainframe now, its ready
	m_MainFrame->Show(true);
}

/**
 * update splitter dimensions
 */
void App::updateSplitters()
{
	//update left, right and main splitter
	m_HorizontalSplitter_right->UpdateSize();
	m_HorizontalSplitter_left->UpdateSize();
	m_VerticalSplitter->UpdateSize();
}

/**
 * update sizers
 */
void App::updateSize()
{
	// update size of m_TreeCtrlLib
	m_TreeCtrlLib->SetSize(m_TreePanelLibrary->GetSize());
	
	// update size of m_TreeCtrlScene
	m_TreeCtrlScene->SetSize(m_TreePanelMyScene->GetSize());
}

/**
 * process intern Notify-Event
 * @param[in]       event       internal event with tpye-information
 */
void App::OnGNREvent(NotifyEvent& event)
{
	switch (event.getGNREventType())
	{
	case GLREFRESH:
		updateSplitters();
		m_Scene->glRefresh();
		break;
	case REFRESHSCENETREE:
		m_TreeSceneCtrl->createSceneTree();
		break;
	case NEWROOM:
		m_Scene->newRoom();
		m_Scene->glRefresh();
		break;
	case OPXOPEN:
		OPXOpen(event.GetString());
		break;
	case OPXIMPORTFINISHED:
	{
		m_progFrame->close();
		m_TreeSceneCtrl->createSceneTree();
		// quick and dirty
		int pos = m_VerticalSplitter->GetSashPosition();
		m_VerticalSplitter->SetSashPosition(pos+1,true);
		m_VerticalSplitter->SetSashPosition(pos,true);
	}
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
		OAXExport(event.GetString());
		//m_Scene->glRefresh();
		break;
	case OBJOAXCONVERSION:
		ObjOaxConversion(event.getAssemblyDataPointer());
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
	case RESETOBJECT:
		m_Scene->resetSelectedAssemblies();
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
		m_Scene->glRefresh();
		break;
	case DISPLAYLENGTH:
		m_MainFrame->getStatusbar()->SetStatusText(event.GetString());
		break;
	case EMPTYTRASH:
		m_Scene->deleteTrashAssemblies();
		break;
	case CREATECUBOID:
	{
		CreateCuboidFrame* cubFrame = new CreateCuboidFrame(m_MainFrame);
		cubFrame->Show();
		break;
	}
	
#if defined(__ATHOS_DEBUG__)
	case DEBUG1:
		m_Tests->sizeXsizeLoopsLoadClean(m_Scene,10,10);
		break;
	case DEBUG2:
		m_Tests->loadTieFighter(m_Scene,10);
		break;
	case DEBUG3:
		m_Tests->dumpWorldStructure(m_Scene);
		break;
#endif
	}
}

/**
 * fetches events, send by scene/library tree in order to perform some action
 * @param[in]       event       send by the tree with extra information
 */
void App::OnGNRTreeEvent(TreeControlEvent& event)
{
	switch (event.getEventType())
	{
	case LIBRARYDELETECAT:
		m_TreeLibCtrl->deleteCategory(event.getCatId());
		break;
	case LIBRARYDELETEENTRY:
		m_TreeLibCtrl->deleteEntry(event.getHash());
		break;
	case LIBRARYPASTE:
		m_TreeLibCtrl->pasteEntry(event.getHash());
		break;
	case LIBRARYEXPORT:
		OAXExport(event.getHash());
		break;
	case LIBRARYNEWCAT:
		m_TreeLibCtrl->addCategory(event.getParentId(), event.getNewName());
		break;
	case LIBRARYMENURENAMEENTRY:
		m_TreeLibCtrl->renameEntry(event.getHash(), event.getNewName());
		break;
	case LIBRARYMENURENAMECAT:
		m_TreeLibCtrl->renameCategory(event.getCatId(), event.getNewName());
		break;
	case SCENEVISIBLE:
		m_Scene->showAssembly(event.getAssembly());
		break;
	case SCENEHIDE:
		m_Scene->hideAssembly(event.getAssembly());
		break;
	case SCENESELECT:
		m_Scene->selectAssembly(event.getAssembly());
		break;
	case SCENEDESELECT:
		m_Scene->selectAssembly(event.getAssembly());
		break;
	case SCENEDELETE:
		m_Scene->deleteAssembly(event.getAssembly());
		break;
	case SCENEUNDELETE:
		m_Scene->restoreAssembly(event.getAssembly());
		break;
	}
}

/**
 * redirect GL -Notify-Event to specific operations
 * @param[in]       event           GLNotifyEvent with information from canvases
 */
void App::OnGLEvent(GLNotifyEvent& event)
{
	//on double click select assembly
	if (event.getMouseEvent().ButtonDClick(LEFT_BUTTON))
	{
		m_MouseCtrl->setSelected(event);
	}
	
	//if any mouse down set mediator and on right down, select too
	else if (event.getMouseEvent().ButtonDown(-1))
	{
		m_MouseCtrl->setMediator(event);
		
		if (event.getMouseEvent().ButtonDown(RIGHT_BUTTON))
		{
			//m_MouseCtrl->setMediator(event);
			m_MouseCtrl->setSelected(event);
			//m_MainFrame->setTranslationXZ(); try to change toolbar here!
		}
	}
	
	//if left or middle mouse button is down, translate event to mediator
	else if (event.getMouseEvent().ButtonIsDown(-1))
	{
		m_MouseCtrl->activateMediator(event);
	}
	
	//if left or middle mouse button goes up, create command-object for undo
	else if (event.getMouseEvent().ButtonUp(LEFT_BUTTON) || event.getMouseEvent().ButtonUp(MIDDLE_BUTTON))
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
 * @param[in]       event       LineDrawEvent that determines the line
 */
void App::OnLineDrawEvent(LineDrawEvent& event)
{
	m_Scene->drawLine(event);
}

/**
 * handles createPrimitiveEvent and creates a new primitive
 * @param[in]       event       CreatePrimitiveEvent with information to the primitve
 */
void App::OnCreatePrimitiveEvent(CreatePrimitiveEvent& event)
{
	if (event.getPrimitiveType() == CUBOID)
	{
		Vertex origin(0.0,0.0,0.0);
		Assembly* atomic;
		
		//get creator instance
		PrimitiveCreator creator;
		
		//create new parent assembly (group of primitives)
		Assembly* primitive = new Assembly(wxT("Wandteil"));
		
		//put information of whole group in parent
		primitive->setType(IS_PRIMITIVE);
		primitive->setPrimitiveType(CUBOID);
		primitive->setCenterVertex(event.getPosition());
		primitive->setRotateVertex(event.getAngles());
		primitive->setWidth(event.getDimensions().getX());
		primitive->setHeight(event.getDimensions().getY());
		primitive->setDepth(event.getDimensions().getZ());
		
		//create smallest part of primitive
		creator.createCuboid(origin, origin, event.getDimensions());
		
		//set color to default
		creator.setMaterial(primitive, DEFAULT_IMPORT_COLOR);
		
		//get the primitive
		atomic = creator.getPrimitive();
		
		//insert 'small' cuboid in parent
		primitive->addPart(atomic);
		
		//put whole in the world
		m_Scene->insertAssembly(primitive);
	}
	
	m_Scene->glRefresh();
}

/**
 * handle opx open
 * @param[in]       filename        File to open.
 */
void App::OPXOpen(wxString filename)
{
	// clean up the actual room
	m_Scene->newRoom();
	
	// create dialog for showing process
	m_progFrame = new ProgressFrame(m_MainFrame);
	m_progFrame->Show();
	
	// create importer-thread
	OpxImport* import = new OpxImport(m_TreeLibCtrl, filename);
	
	// start thread
	import->Create();
	import->Run();
}

/**
 * handle opx save
 * @param[in]       filename        File to save as.
 */
void App::OPXSave(wxString filename)
{
	// create new opx export object
	OpxExport opxExport(m_Scene, filename);
}

/**
 * handle oax import
 * @param[in]       filename        File to import.
 */
void App::OAXImport(wxString filename)
{
	// new filename
	wxFileName file;
	
	// asign filename
	file.Assign(filename);
	
	// create wxFFileInputStream
	wxFFileInputStream inFile(filename);
	
	// create wxMemoryoutputStream
	wxMemoryOutputStream outMem;
	
	// copy data
	inFile.Read(outMem);
	
	// dreate wxMemoryInputStream
	wxMemoryInputStream inMem(outMem);
	
	// wxInputStream pointer
	wxInputStream* input = &inMem;
	
	// add into lib
	m_TreeLibCtrl->addEntry(*input, file.GetName(), 0);
}

/**
 * handle oax export
 * @param[in]      reference        File to export to.
 */
void App::OAXExport(wxString reference)
{
	// filename
	const wxString& filename = wxFileSelector(wxT("Object als OAX exportieren..."), wxT(""), wxT(""), wxT(""), wxT("OaxDatei (*.oax)|*.oax"), wxFD_SAVE);
	
	if (filename.IsEmpty())
	{
		// user canceled, do nothing
		return;
	}
	
	// wxFFileOutputStream
	wxFFileOutputStream outFile(filename);
	
	// wxMemoryOutputStream to store oax data
	wxMemoryOutputStream* memOut;
	
	// get data
	memOut = m_TreeLibCtrl->exportEntry(reference);
	
	// wxMemoryInputStream
	wxMemoryInputStream inMem(*memOut);
	
	// copy data
	inMem.Read(outFile);
	
	// delete memOut
	delete memOut;
}

/**
 * handle obj import
 * @param[in]       filename        File to import.
 */
void App::OBJImport(wxString filename)
{
	// create objoaxconv
	m_ObjOaxConv = new ObjOaxConverter(filename);
}

/**
 * handle obj import
 * @param[in]       filename        File to export to.
 */
void App::OBJExport(wxString filename)
{
	filename << wxT("\n\nLeider noch nicht implementiert!");
	wxMessageBox(filename);
}

/**
 * handle screenshot-creation
 * @param[in]       filename        File to export to.
 */
void App::createScreenshot(wxString filename)
{
	m_Canvas3D->setActive();
	GLScreenshot scr(filename);
}

/**
 * conververtion canceled
 */
void App::cancelConvertion()
{
	delete m_ObjOaxConv;
}

/**
 * Conversion suchessfull, write new entry into library
 * @param[in]	data		pointer to an assembly
 */
void App::ObjOaxConversion(AssemblyData* data)
{
	// create new memory output stream
	wxMemoryOutputStream memOut;
	
	// pointer to wxOutputStream
	wxOutputStream* outStream = &memOut;
	
	// create new OaxExport - object
	OaxExport out(data, outStream);
	
	// create new memory input stream
	wxMemoryInputStream memIn(memOut);
	
	// pointer to wxInputStream
	wxInputStream* inStream = &memIn;
	
	// add new entry
	m_TreeLibCtrl->addEntry(*inStream, data->m_name, 0);
	
	// successfull
	delete m_ObjOaxConv;
}

/**
 * throw event for inital setup
 */
void App::initialSetup()
{
	//build initial snap to grid settings
	NotifyEvent setup_snap(wxEVT_COMMAND_GNR_NOTIFY);
	setup_snap.setGNREventType(SNAPTOGRID);
	setup_snap.setSnapToGrid(SNAP_IN_DEFAULT_GRID);
	setup_snap.setSnapToAngle(SNAP_IN_DEFAULT_ANGLE);
	
	//activate snap function on start
	m_MouseCtrl->setSnapfunction(setup_snap);
	
	//send event to refresh Scene-Tree
	NotifyEvent setup_tree(wxEVT_COMMAND_GNR_NOTIFY);
	setup_tree.setGNREventType(REFRESHSCENETREE);
	
	//process event for tree
	ProcessEvent(setup_tree);
	
	//refresh canvas
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
