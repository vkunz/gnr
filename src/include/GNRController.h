/**
 * GNRController
 * @name        GNRController.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRCONTROLLER_H_
#define _GNRCONTROLLER_H_

#include <wx/splitter.h>
#include <wx/glcanvas.h>
#include <wx/msgdlg.h>

#include "GNRAssembly.h"
#include "GNRAssemblyTranslater.h"
#include "GNRMainFrame.h"
#include "GNRGLCanvas2D.h"
#include "GNRGLCanvas3D.h"
#include "GNRTreePanelLibrary.h"
#include "GNRTreePanelMyScene.h"
#include "GNRGLNotifyEvent.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#include "GNRDebugFrame.h"
#endif

class GNRController
{
private:

	GNRAssembly* m_RootAssembly;
	GNRAssemblyTranslater* m_AssemblyTranslater;
	GNRGLCamera* m_GLCamera;
	GNRMainFrame* m_MainFrame;
	GNRGLCanvas2D* m_Canvas2D;
	GNRGLCanvas3D* m_Canvas3D;
	GNRTreePanelLibrary* m_TreePanelLibrary;
	GNRTreePanelMyScene* m_TreePanelMyScene;
	wxGLContext* commonCtxt;
	
	wxSplitterWindow* m_HorizontalSplitter_left;
	wxSplitterWindow* m_HorizontalSplitter_right;
	wxSplitterWindow* m_VerticalSplitter;
	
	void updateSplitters();
	void glRefresh2D();
	void glRefresh3D();
	
	int m_init;
	canvasType m_activeCanvas;
	
#if defined(__ATHOS_DEBUG__)
	GNRDebugFrame* m_DebugFrame;
	wxLog* m_Log;
#endif
	
public:
	//starts refreshing the both canvas frames
	void glRefresh();
	void initFrames();
	void newRoom();
	void resetCamera();
	void processGLMouse(GNRGLNotifyEvent& event);
	void XMLOpen(wxString filename);
	void OBJImport(wxString filename);
	void toggleToolbar(wxNotifyEvent& event);
	
	GNRController();
	~GNRController();
};

#endif // _GNRCONTROLLER_H_
