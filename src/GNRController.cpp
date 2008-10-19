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
#include "wx/wx.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

GNRController::GNRController()
{
	//create root assembly, proxy and mainframe
	m_RootAssembly  = new GNRAssembly();
	m_AssemblyProxy = new GNRAssemblyProxy();
	m_GLCamera      = new GNRGLCamera();
	m_MainFrame     = new GNRMainFrame(0);
	m_AssemblyProxy->setGLCamera(m_GLCamera);
	
#if defined(__ATHOS_DEBUG__)
	// Create DebugFrame
	m_DebugFrame = new GNRDebugFrame(0);
	m_DebugFrame->Show(true);
	m_Log = new wxLogTextCtrl(m_DebugFrame->TextCtrl);
	m_Log->SetActiveTarget(m_Log);
#endif
	
}

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
	delete m_AssemblyProxy;
	delete m_RootAssembly;
}

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
	m_TreePanelLibrary = new GNRTreePanel(m_HorizontalSplitter_left, wxID_ANY);
	m_TreePanelMyScene = new GNRTreePanel(m_HorizontalSplitter_left, wxID_ANY);
	
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
	
	//TODO IN EXTRA METHOD, (TEST FOR LIGHTS WITH TIE FIGHTER)
	GNRObjectImport object_importer(_("data/computer/apple-ibook-2001.obj"));
	
	GNRAssembly* test = object_importer.GetAssembly();
	test->setZ(-6.0f);
	
	m_RootAssembly->addChildAssembly(test);
	
	glRefresh();
}

void GNRController::updateSplitters()
{
	//update left, right and main splitter
	m_HorizontalSplitter_right->UpdateSize();
	m_HorizontalSplitter_left->UpdateSize();
	m_VerticalSplitter->UpdateSize();
}

void GNRController::glRefresh()
{
	//update splitter dimensions
	updateSplitters();
	
	//prepare and draw 2D top view of room
	m_Canvas2D->prepareDraw();
	m_RootAssembly->draw();
	m_Canvas2D->endDraw();
	
	//prepare and draw 3D view of room
	m_Canvas3D->prepareDraw();
	m_GLCamera->Render();
	m_RootAssembly->draw();
	m_Canvas3D->endDraw();
}

/**
 * fetches the double click event
 * @param       wxMouseEvent    Mouse-Event of current canvas
 * @access      private
 */
void GNRController::processGLMouse(GNRGLNotifyEvent& event)
{
	if (event.getMouseEvent().ButtonDown())
	{
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
				m_AssemblyProxy->setAssembly((GNRAssembly*)selectedAssemblyID);
				m_AssemblyProxy->setWindow(event);
				m_AssemblyProxy->getControl(event);
			}
		}
		else if (event.getMouseEvent().ButtonIsDown(2))
		{
			m_AssemblyProxy->setWindow(event);
			m_AssemblyProxy->getControl(event);
		}
	}
	else if (event.getMouseEvent().ButtonUp())
	{
		m_AssemblyProxy->dropControl(event);
	}
	else
	{
		m_AssemblyProxy->ObjectTransform(event);
	}
}

void GNRController::XMLOpen(wxString filename)
{
	wxLogDebug(wxT("Hier angekommen"));
	wxLogDebug(filename);
}

void GNRController::OBJImport(wxString filename)
{
	// generate new Importer, parse file
	GNRObjectImport ObjFileImport(filename);
	
	// return pointer to new object
	m_RootAssembly->addChildAssembly(ObjFileImport.GetAssembly());
}

void GNRController::toggleToolbar(wxNotifyEvent& event)
{
	switch (event.GetInt())
	{
	case 1:
		wxLogDebug(_("set MOVEXY"));
		m_AssemblyProxy->setDirection(MOVEXY);
		break;
	case 2:
		wxLogDebug(_("set MOVEXZ"));
		m_AssemblyProxy->setDirection(MOVEXZ);
		break;
	case 3:
		wxLogDebug(_("set ROTATE"));
		m_AssemblyProxy->setDirection(ROTATE);
		break;
	}
}
