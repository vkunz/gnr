/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRDebugFrame
 * @name        GNRDebugFrame.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRDEBUGFRAME_H
#define GNRDEBUGFRAME_H

//(*Headers(GNRDebugFrame)
#include <wx/frame.h>
class wxTextCtrl;
//*)

#include <wx/log.h>

class GNRDebugFrame: public wxFrame
{
public:

	GNRDebugFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxSize& size=wxDefaultSize);
	virtual ~GNRDebugFrame();
	
	//(*Declarations(GNRDebugFrame)
	wxTextCtrl* TextCtrl;
	//*)
	
protected:

	//(*Identifiers(GNRDebugFrame)
	static const long ID_TextCtrl;
	//*)
	
private:

	//(*Handlers(GNRDebugFrame)
	//*)
	
	DECLARE_EVENT_TABLE()
};

#endif
