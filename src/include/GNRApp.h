/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRApp
 * @name        GNRApp.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRAPP_H
#define GNRAPP_H

#include <wx/app.h>
#include <wx/glcanvas.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/wfstream.h>

#include "GNRGLCanvas2D.h"
#include "GNRGLCanvas3D.h"
#include "GNRGLNotifyEvent.h"
#include "GNRMainFrame.h"
#include "GNRMouseController.h"
#include "GNRNotifyEvent.h"
#include "GNROaxImport.h"
#include "GNRScene.h"
#include "GNRTreeLibraryController.h"
#include "GNRTreePanelLibrary.h"
#include "GNRTreePanelMyScene.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#include "GNRDebugFrame.h"
#endif

class GNRApp : public wxApp
{
private:

	//eventhandler
	void OnGNREvent(GNRNotifyEvent& event);
	void OnGLEvent(GNRGLNotifyEvent& event);
	
	//functions
	void glRefresh();
	void glRefresh2D();
	void glRefresh3D();
	void initFrames();
	void updateSplitters();
	void updateSize();
	
	// MainFrame Menu-functions
	void OPXOpen(wxString filename);
	void OPXSave(wxString filename);
	void OAXImport(wxString filename);
	void OAXExport(wxString filename);
	void OBJImport(wxString filename);
	void OBJExport(wxString filename);
	
	//attributes
	wxTreeCtrl* m_TreeCtrlLib;
	//wxTreeCtrl* m_TreeCtrlScene;
	GNRTreeLibraryController* m_TreeLibCtrl;
	
	GNRTreePanelLibrary* m_TreePanelLibrary;
	GNRTreePanelMyScene* m_TreePanelMyScene;
	
	GNRScene* m_Scene;
	GNRMouseController* m_MouseCtrl;
	GNRMainFrame* m_MainFrame;
	
	GNRGLCanvas2D* m_Canvas2D;
	GNRGLCanvas3D* m_Canvas3D;
	wxGLContext* commonCtxt;
	
	wxSplitterWindow* m_HorizontalSplitter_left;
	wxSplitterWindow* m_HorizontalSplitter_right;
	wxSplitterWindow* m_VerticalSplitter;
	
#if defined(__ATHOS_DEBUG__)
	GNRDebugFrame* m_DebugFrame;
	wxLog* m_Log;
#endif
	
	DECLARE_EVENT_TABLE();
	
public:

	virtual bool OnInit();
	
};

#endif // GNRAPP_H
