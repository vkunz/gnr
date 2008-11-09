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

//(*Headers(DebugFrame)
#include <wx/textctrl.h>
#include <wx/frame.h>
//*)

#include <wx/log.h>

class DebugFrame: public wxFrame
{
public:

	DebugFrame(wxWindow* parent,wxWindowID id=wxID_ANY);
	virtual ~DebugFrame();
	
	//(*Declarations(DebugFrame)
	wxTextCtrl* TextCtrl;
	//*)
	
protected:

	//(*Identifiers(DebugFrame)
	static const long ID_TextCtrl;
	//*)
	
private:

	//(*Handlers(DebugFrame)
	//*)
	
	DECLARE_EVENT_TABLE()
};

#endif
