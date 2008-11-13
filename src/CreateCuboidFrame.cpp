/**
 * This frame is used to allow the user to create a new cuboid-primitive
 * @note        [DONE]
 * @name        CreateCuboidFrame.cpp
 * @date        2008-11-11
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "include/CreateCuboidFrame.h"

#include <wx/colour.h>
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/textctrl.h>

#include "GlobalDefine.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "resources/gnr_icon.xpm"
#endif

const long CreateCuboidFrame::idSpcWidth = wxNewId();
const long CreateCuboidFrame::idSpcHeight = wxNewId();
const long CreateCuboidFrame::idSpcDepth = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT1 = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT2 = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT3 = wxNewId();
const long CreateCuboidFrame::idBtnCreate = wxNewId();
const long CreateCuboidFrame::idBtnCancel = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT4 = wxNewId();
const long CreateCuboidFrame::idColourPicker = wxNewId();


BEGIN_EVENT_TABLE(CreateCuboidFrame,wxFrame)
	EVT_BUTTON(idBtnCreate, CreateCuboidFrame::OnCreate)
	EVT_BUTTON(idBtnCancel, CreateCuboidFrame::OnCancel)
END_EVENT_TABLE()

/**
 * constructor of AssemblyDataFrame; creates the frame with its controls and connects needed events
 * @param[in]       parent          parent of this frame
 * @param[in]       id              id of this frame
 * @param[in]       pos             position of this frame
 * @param[in]       size            size of this frame
 */
CreateCuboidFrame::CreateCuboidFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	Create(parent, wxID_ANY, wxT("Kubus erstellen"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetClientSize(wxSize(382,230));
	CenterOnParent();
	SetBackgroundColour(wxNullColour);
	SetIcon(wxICON(gnr_icon));
	//MakeModal();
	
	m_panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(382,260), wxTAB_TRAVERSAL);
	
	wxString minSize;
	minSize << SIZE_MINIMUM_VALUE;
	
	StaticText1 = new wxStaticText(m_panel, ID_STATICTEXT1, _("Breite"), wxPoint(56,30), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	m_spcWidth = new wxSpinCtrl(m_panel, idSpcWidth, minSize, wxPoint(128,25), wxSize(168,24), 0, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE, _T("idSpcWidth"));
	
	StaticText2 = new wxStaticText(m_panel, ID_STATICTEXT2, _("H" ouml "he"), wxPoint(56,65), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	m_spcHeight = new wxSpinCtrl(m_panel, idSpcHeight, minSize, wxPoint(128,60), wxSize(168,21), 0, 0, 100, 0, _T("idSpcHeight"));
	
	StaticText3 = new wxStaticText(m_panel, ID_STATICTEXT3, _("Tiefe"), wxPoint(56,100), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	m_spcDepth = new wxSpinCtrl(m_panel, idSpcDepth, minSize, wxPoint(128,95), wxSize(168,21), 0, 0, 100, 0, _T("idSpcDepth"));
	
	StaticText4 = new wxStaticText(m_panel, ID_STATICTEXT4, _("Farbe"), wxPoint(56,147), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	m_colourPicker = new wxColourPickerCtrl(m_panel, idColourPicker, wxColour(107,122,254), wxPoint(128, 142), wxSize(24,24));
	
	m_buCreate = new wxButton(m_panel, idBtnCreate, _("Erstellen"), wxPoint(56,188), wxSize(88,23), 0, wxDefaultValidator, _T("idBuCreate"));
	m_buCancel = new wxButton(m_panel, idBtnCancel, _("Abbrechen"), wxPoint(232,188), wxSize(88,23), 0, wxDefaultValidator, _T("idBuCancel"));
}

/**
 * destructor of CreateCuboidFrame
 */
CreateCuboidFrame::~CreateCuboidFrame() {}

/**
 * changes the color of the preview-panel to setted color
 * @param[in]       WXUNUSED        unused event of spinctrl
 */
void CreateCuboidFrame::OnColorChange(wxColourPickerEvent& event)
{

}

/**
 * fetches the button click and prepares creating a new cuboid
 * @param[in]       WXUNUSED        unused button-event
 */
void CreateCuboidFrame::OnCreate(wxCommandEvent& WXUNUSED(event))
{
	//m_colourPicker->GetColour().Red();
}

/**
 * closes the window and cancels cuboid-creation
 * @param[in]       WXUNUSED        unused button-event
 */
void CreateCuboidFrame::OnCancel(wxCommandEvent& WXUNUSED(event))
{
	Destroy();
}
