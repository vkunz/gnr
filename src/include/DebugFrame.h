/**
 * DebugFrame
 * @name        DebugFrame.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef DEBUGFRAME_H
#define DEBUGFRAME_H

#include <wx/textctrl.h>
#include <wx/frame.h>

#include <wx/log.h>

class DebugFrame: public wxFrame
{
public:

	DebugFrame(wxWindow* parent);
	virtual ~DebugFrame();
	
	wxTextCtrl* TextCtrl;
	
protected:

	static const long ID_TextCtrl;
	
private:

};

#endif
