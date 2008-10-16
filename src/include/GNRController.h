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

#ifndef _GNRCONTROLLER_H_
#define _GNRCONTROLLER_H_

#include <wx/splitter.h>
#include <wx/glcanvas.h>
#include <wx/msgdlg.h>

#include "GNRAssembly.h"
#include "GNRAssemblyProxy.h"
#include "GNRMainFrame.h"
#include "GNRGL2DCanvas.h"
#include "GNRGL3DCanvas.h"
#include "GNRObjectImport.h"
#include "GNRTreePanel.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#include "GNRDebugFrame.h"
#endif

class GNRController
{
private:
	GNRAssembly* m_RootAssembly;
	GNRAssemblyProxy* m_AssemblyProxy;
	GNRMainFrame* m_MainFrame;
	GNRGL2DCanvas* m_Canvas2D;
	GNRGL3DCanvas* m_Canvas3D;
	GNRTreePanel* m_TreePanelLibrary;
	GNRTreePanel* m_TreePanelMyScene;
	wxGLContext* commonCtxt;
	
	wxSplitterWindow* m_HorizontalSplitter_left;
	wxSplitterWindow* m_HorizontalSplitter_right;
	wxSplitterWindow* m_VerticalSplitter;
	
#if defined(__ATHOS_DEBUG__)
	GNRDebugFrame* m_DebugFrame;
	wxLog* m_Log;
#endif
	
public:
	//starts refreshing the both canvas frames
	void glRefresh();
	
	GNRController();
	~GNRController();
};

#endif // _GNRCONTROLLER_H_
