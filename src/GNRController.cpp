/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRController (singleton)
 * @name        GNRController.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRController.h"
#include "GNRAssembly.h"
#include "GNRMaterial.h"
#include "GNROaxImport.h"
#include "GNRObjectImport.h"
#include "GNRXmlImport.h"
#include "wx/wx.h"

// quick && dirty
#include "GNRMaterialLibrary.h"
GNRMaterialLibrary mtllib;

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <wx/txtstrm.h>
#include <wx/xml/xml.h>
#endif

/**
 * constructor
 * @access      public
 */

GNRController::GNRController()
{
	//create root assembly, proxy and mainframe
	m_RootAssembly      = new GNRAssembly("scene");
	m_GLCamera          = new GNRGLCamera();
	m_AssemblyTranslater= new GNRAssemblyTranslater(m_GLCamera);
	m_MainFrame         = new GNRMainFrame(0);
	m_activeCanvas      = NONE;
	
	
#if defined(__ATHOS_DEBUG__)
	// Create DebugFrame
	m_DebugFrame = new GNRDebugFrame(0);
	m_DebugFrame->Show(true);
	m_Log = new wxLogTextCtrl(m_DebugFrame->TextCtrl);
	m_Log->SetActiveTarget(m_Log);
#endif
	
}

/**
 * destructor
 * @access      public
 */
GNRController::~GNRController()
{
	delete m_Canvas3D;
	delete m_Canvas2D;
	delete m_HorizontalSplitter_right;
	delete m_TreePanelMyScene;
	delete m_TreePanelLibrary;
	delete m_HorizontalSplitter_left;
	delete m_VerticalSplitter;
#if defined(__ATHOS_DEBUG__)
	delete m_Log;
	delete m_DebugFrame;
#endif
	delete m_MainFrame;
	delete m_AssemblyTranslater;
	delete m_RootAssembly;
}

/**
 * initialize all frames needed
 * @access      public
 */
void GNRController::initFrames()
{
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
	glRefresh();
}

/**
 * update splitter dimensions
 * @access      public
 */
void GNRController::updateSplitters()
{
	//update left, right and main splitter
	m_HorizontalSplitter_right->UpdateSize();
	m_HorizontalSplitter_left->UpdateSize();
	m_VerticalSplitter->UpdateSize();
}

/**
 * refresh glcanvas frames (3d/2d)
 * @access      public
 */
void GNRController::glRefresh()
{
	//update splitter dimensions
	updateSplitters();
	
	if (m_activeCanvas == 3)
	{
		glRefresh2D();
	}
	
	glRefresh3D();
	
	if (m_activeCanvas == 2)
	{
		glRefresh2D();
	}
}

/**
 * refresh 2d canvas
 * @access      public
 */
void GNRController::glRefresh2D()
{
	//prepare and draw 2D top view of room
	m_Canvas2D->prepareDraw();
	m_RootAssembly->draw();
	m_Canvas2D->endDraw();
}

/**
 * refresh 2d canvas
 * @access      public
 */
void GNRController::glRefresh3D()
{
	//prepare and draw 3D view of room
	m_Canvas3D->prepareDraw();
	m_GLCamera->render();
	m_RootAssembly->draw();
	m_Canvas3D->endDraw();
}

/**
 * handle mouse events (buttons and movement)
 * @param       GNRGLNotifyEvent        our event
 * @access      public
 */
void GNRController::processGLMouse(GNRGLNotifyEvent& event)
{
	if (event.getMouseEvent().ButtonDown())
	{
		// mouse button pressed --> get controll of assembly
		if (event.getMouseEvent().ButtonIsDown(1))
		{
			int selectedAssemblyID, m_x, m_y;
			
			//get mouse coords
			m_x = event.getMouseEvent().m_x;
			m_y = event.getMouseEvent().m_y;
			selectedAssemblyID = 0;
			
			//if from 2D canvas, redraw only this one
			if (event.getCanvasID() == 2)
			{
				selectedAssemblyID = m_Canvas2D->selection(m_RootAssembly, NULL, m_x, m_y);
			}
			else
			{
				selectedAssemblyID = m_Canvas3D->selection(m_RootAssembly, m_GLCamera, m_x, m_y);
			}
			
#if defined(__ATHOS_DEBUG__)
			wxString msg;
			msg << event.getCanvasID() << _("D:") << _(" ID=") << selectedAssemblyID << _(" X=") << m_x << _(" Y=") << m_y;
			wxLogMessage(msg);
#endif
			
			if (selectedAssemblyID > 0)
			{
				m_AssemblyTranslater->setAssembly((GNRAssembly*)selectedAssemblyID);
				m_AssemblyTranslater->setWindow(event);
				m_AssemblyTranslater->getControl(event);
			}
		}
		else if (event.getMouseEvent().ButtonIsDown(2) && event.getCanvasID() == 3)
		{
			m_AssemblyTranslater->setWindow(event);
			m_AssemblyTranslater->getControl(event);
		}
	}
	else if (event.getMouseEvent().ButtonUp())
	{
		m_AssemblyTranslater->dropControl(event);
	}
	else if (event.getMouseEvent().Entering())
	{
		m_activeCanvas = event.getCanvasID();
	}
	else if (event.getMouseEvent().Leaving())
	{
		m_AssemblyTranslater->dropControl(event);
	}
	else if (event.getMouseEvent().Dragging())
	{
		m_AssemblyTranslater->ObjectTransform(event);
	}
	else if (event.getMouseEvent().GetWheelRotation())
	{
		m_GLCamera->changeDistance(event.getMouseEvent().GetWheelRotation() / 600.0);
	}
}

/**
 * handle xml import
 * @param       wxString        filename
 * @access      public
 */
void GNRController::XMLOpen(wxString filename)
{
	wxLogDebug(wxT("Hier angekommen"));
	//wxLogDebug(filename);
	wxString file = wxT("D:\\Devel\\Projects\\Praxisprojekt\\data\\Reference-oax\\31696c04-386a-4407-8f3e-c3f6e92d91ca.oax");
	
	wxFFileInputStream stream(file);
	
	// test as stream
	GNROaxImport oax_2(stream);
	
	// test as file
	GNROaxImport oax(file);
	
	
	
	
	
	
	
	
	
	//GNRXmlImport xmlImport(file);
	
//    wxLogDebug(wxT("Zip erstellen..."));

//    wxFFileOutputStream out(file);
//    wxZipOutputStream zipout(out);
//    wxTextOutputStream txtout(zipout);
//    wxString sep(wxFileName::GetPathSeparator());

//    zipout.PutNextEntry(_T("entry1.txt"));
//    txtout << _T("Some text for entry1.txt\n");

//    zipout.PutNextEntry(_T("subdir") + sep + _T("entry2.txt"));
//    txtout << _T("Some text for subdir/entry2.txt\n");

//    log << wxT("Datei: ") << file << wxT(" erstellt!");

//    wxLogDebug(log);

//    file = wxT("D:\\Devel\\Projects\\Praxisprojekt\\data\\Reference-opx\\ExampleProject.opx");

//    wxLogDebug(wxT("Zip auslesen..."));

//    wxZipEntry* entry;
//    wxFFileInputStream in(file);
//    wxZipInputStream zipin(in);
//    wxTextInputStream txtin(zipin);
//    wxXmlDocument xml;
//    wxXmlNode* child;
//    wxXmlProperty* prop;

	// iterate through all entrys
//    while(entry = zipin.GetNextEntry())
//    {
	// filter directories
//        if(!entry->IsDir())
//        {
	// filter xml
//            if(entry->GetName().Matches(wxT("*.xml")))
//            {
//                log = entry->GetName();
//                wxLogDebug(log);
//                log = wxT("");

//                xml.Load(zipin);
//                log << wxT("content.xml -> Version: ") <<  xml.GetVersion() << wxT("\tcontent.xml -> Encoding: ") << xml.GetFileEncoding();
//                wxLogDebug(log);
//                log = wxT("");

	// opxml
//                child = xml.GetRoot();

	// projectinformation
//                child = child->GetChildren();

	// data
//                child = child->GetNext();

	// camera
//                child = child->GetChildren();

	// lightsource
//                child = child->GetNext();

	// scene
//                child = child->GetNext();

	// assembly
//                child = child->GetChildren();

	// go through all scene-tags
//                while(child)
//                {
	// filter assembly
//                    if(child->GetName() == wxT("assembly"))
//                    {
//                        prop = child->GetProperties();

//                        log += wxT("Properties: ");
//                        while(prop)
//                        {
//                            log += prop->GetName();
//                            log += wxT(" ");
//                            log += prop->GetValue();
//                            log += wxT(" ");

//                            prop = prop->GetNext();
//                        }
//                        wxLogDebug(log);
//                        log = wxT("");
//                    }

//                    child = child->GetNext();
//                }

//                while(child)
//                {
//                    log = child->GetNodeContent();
//                    wxLogDebug(log);

	// next child
//                    child = child->GetNext();
//                }
//            }
//        }
//    }
}

/**
 * handle obj import
 * @param       wxString        filename
 * @access      public
 */
void GNRController::OBJImport(wxString filename)
{
	// generate new Importer, parse file
	GNRObjectImport oi;
	m_RootAssembly->addPart(oi.read((string)filename.mb_str()));
}

/**
 * clean up whole world
 * @access      public
 */
void GNRController::newRoom()
{
	delete m_RootAssembly;
	m_RootAssembly = new GNRAssembly("scene");
	m_GLCamera->reset();
}

void GNRController::resetCamera()
{
	m_GLCamera->reset();
}

/**
 * toggle toolbar button clicks and set translation direction
 * @param       wxNotifyEvent        button event
 * @access      public
 */
void GNRController::toggleToolbar(wxNotifyEvent& event)
{
	switch ((transType)event.GetInt())
	{
	case MOVEXZ:
		m_AssemblyTranslater->setDirection(MOVEXZ);
		break;
	case MOVEXY:
		m_AssemblyTranslater->setDirection(MOVEXY);
		break;
	case ROTATEXY:
		m_AssemblyTranslater->setDirection(ROTATEXY);
		break;
	case ROTATEXZ:
		m_AssemblyTranslater->setDirection(ROTATEXZ);
		break;
	default:
		m_AssemblyTranslater->setDirection(MOVEXZ);
		break;
	}
}
