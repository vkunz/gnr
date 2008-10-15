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

GNRController::GNRController()
{
#if defined(__ATHOS_DEBUG__)
	// Create DebugFrame
	m_DebugFrame = new GNRDebugFrame(0);
	m_DebugFrame->Show(true);
	m_Log = new wxLogTextCtrl(m_DebugFrame->TextCtrl);
	m_Log->SetActiveTarget(m_Log);
#endif
	
	m_RootAssembly  = new GNRAssembly();
	m_AssemblyProxy = new GNRAssemblyProxy();
	m_MainFrame     = new GNRMainFrame(0);
	
	//main splitter window
	m_VerticalSplitter = new wxSplitterWindow(m_MainFrame, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxRAISED_BORDER);
	m_VerticalSplitter->SetMinimumPaneSize(200);
	
	//create splitter for left panel with tree and models
	m_HorizontalSplitter_left = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxRAISED_BORDER);
	m_HorizontalSplitter_left->SetMinimumPaneSize(200);
	
	//create tree and models panel
	m_TreePanelLibrary = new GNRTreePanel(m_HorizontalSplitter_left, wxID_ANY);
	m_TreePanelMyScene = new GNRTreePanel(m_HorizontalSplitter_left, wxID_ANY);
	
	//initialize tree (top) and models (bottom)
	m_HorizontalSplitter_left->Initialize(m_TreePanelLibrary);
	m_HorizontalSplitter_left->Initialize(m_TreePanelMyScene);
	m_HorizontalSplitter_left->SplitHorizontally(m_TreePanelLibrary, m_TreePanelMyScene);
	
	//create splitter for right panel with two canvas
	m_HorizontalSplitter_right = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxRAISED_BORDER);
	m_HorizontalSplitter_right->SetMinimumPaneSize(200);
	
	//split left and right splitters
	m_VerticalSplitter->SplitVertically(m_HorizontalSplitter_left, m_HorizontalSplitter_right);
	
	//create two canvas panels
	m_Canvas2D = new GNRGL2DCanvas(m_HorizontalSplitter_right, -1);
	//show mainframe
	m_MainFrame->Show(true);
	//shared context
	commonCtxt = m_Canvas2D->GetContext();
	m_Canvas3D = new GNRGL3DCanvas(m_HorizontalSplitter_right, commonCtxt, -1);
	
	//initialize top an bottom canvas
	m_HorizontalSplitter_right->Initialize(m_Canvas2D); //upper
	m_HorizontalSplitter_right->Initialize(m_Canvas3D); //lower
	m_HorizontalSplitter_right->SplitHorizontally(m_Canvas2D, m_Canvas3D);
}

GNRController::~GNRController()
{
}

void GNRController::OnImport(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT("Select OBJ-File..."), wxT(""), wxT(""), wxT(""), wxT("OBJ-Files (*.obj)|*.obj"));
	
	if (!filename.IsEmpty())
	{
		GNRObjectImport ObjImport(filename);
		m_RootAssembly->addChildAssembly(ObjImport.GetAssembly());
	}
}

void GNRController::OnExport(wxCommandEvent& event)
{
}
