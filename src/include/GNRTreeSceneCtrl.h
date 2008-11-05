#ifndef _GNRTREESCENECTRL_H_
#define _GNRTREESCENECTRL_H_

#include <wx/treectrl.h>

class GNRTreeSceneCtrl: public wxTreeCtrl
{
public:
	GNRTreeSceneCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
	                 const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTreeCtrlNameStr);
	virtual ~GNRTreeSceneCtrl();
protected:
private:
	void OnItemRClick(wxTreeEvent& event);
	
	DECLARE_EVENT_TABLE()
};

#endif // _GNRTREESCENECTRL_H_
