/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRAssemblyMediator
 * @name        GNRAssemblyMediator.cpp
 * @date        2008-10-09
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssemblyMediator.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of assembly mediator
 * @access      public
 */
GNRAssemblyMediator::GNRAssemblyMediator()
{
	m_CanvasID = NONE;
	m_Assembly = NULL;
}

/**
 * destructor of assembly mediator
 * @access      public
 */
GNRAssemblyMediator::~GNRAssemblyMediator()
{
}

/**
 * translates mouse event information to the assembly
 * @access      public
 */
void GNRAssemblyMediator::translate(GNRGLNotifyEvent& event)
{
	switch (m_CanvasID)
	{
	case CANVAS2D:
		wxLogDebug(wxT("GNRAssemblyMediator 2D"));
		break;
	case CANVAS3D:
		wxLogDebug(wxT("GNRAssemblyMediator 3D"));
		break;
	default:
		break;
	}
}

void GNRAssemblyMediator::setMode(canvasType canvas_id)
{
	m_CanvasID = canvas_id;
}

void GNRAssemblyMediator::setAssemblyID(int assemblyID)
{
	m_Assembly = (GNRAssembly*)assemblyID;
}

