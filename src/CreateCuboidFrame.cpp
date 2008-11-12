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
const long CreateCuboidFrame::idPanColor = wxNewId();
const long CreateCuboidFrame::idSpcRed = wxNewId();
const long CreateCuboidFrame::idSpcGreen = wxNewId();
const long CreateCuboidFrame::idSpcBlue = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT5 = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT6 = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT7 = wxNewId();


BEGIN_EVENT_TABLE(CreateCuboidFrame,wxFrame)
	EVT_SPINCTRL(idSpcRed, CreateCuboidFrame::OnSpcColorChange)
	EVT_SPINCTRL(idSpcGreen, CreateCuboidFrame::OnSpcColorChange)
	EVT_SPINCTRL(idSpcBlue, CreateCuboidFrame::OnSpcColorChange)
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
	SetClientSize(wxSize(382,260));
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
	
	StaticText4 = new wxStaticText(m_panel, ID_STATICTEXT4, _("Farbe"), wxPoint(32,157), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	m_panColor = new wxPanel(m_panel, idPanColor, wxPoint(80,151), wxSize(24,24), wxTAB_TRAVERSAL, _T("idPanColor"));
	m_panColor->SetOwnBackgroundColour(wxColour(255, 255, 255));
	
	StaticText5 = new wxStaticText(m_panel, ID_STATICTEXT5, _("R"), wxPoint(115,157), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	m_spcRed = new wxSpinCtrl(m_panel, idSpcRed, _T("255"), wxPoint(128,153), wxSize(55,21), 0, 0, 255, 255, _T("idSpcRed"));
	
	StaticText6 = new wxStaticText(m_panel, ID_STATICTEXT6, _("G"), wxPoint(195,157), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	m_spcGreen = new wxSpinCtrl(m_panel, idSpcGreen, _T("255"), wxPoint(208,153), wxSize(56,21), 0, 0, 255, 255, _T("idSpcGreen"));
	
	StaticText7 = new wxStaticText(m_panel, ID_STATICTEXT7, _("B"), wxPoint(275,157), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	
	m_spcBlue = new wxSpinCtrl(m_panel, idSpcBlue, _T("255"), wxPoint(288,153), wxSize(56,21), 0, 0, 255, 255, _T("idSpcBlue"));
	
	m_buCreate = new wxButton(m_panel, idBtnCreate, _("Erstellen"), wxPoint(56,208), wxSize(88,23), 0, wxDefaultValidator, _T("idBuCreate"));
	m_buCancel = new wxButton(m_panel, idBtnCancel, _("Abbrechen"), wxPoint(232,208), wxSize(88,23), 0, wxDefaultValidator, _T("idBuCancel"));
	
	// connect events to catch Enter press
	Connect(idSpcRed,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&CreateCuboidFrame::OnSpcColorChange);
	Connect(idSpcGreen,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&CreateCuboidFrame::OnSpcColorChange);
	Connect(idSpcBlue,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&CreateCuboidFrame::OnSpcColorChange);
}

/**
 * destructor of CreateCuboidFrame
 */
CreateCuboidFrame::~CreateCuboidFrame() {}

/**
 * changes the color of the preview-panel to setted color
 * @param[in]       WXUNUSED        unused event of spinctrl
 */
void CreateCuboidFrame::OnSpcColorChange(wxSpinEvent& WXUNUSED(event))
{
	m_panColor->SetOwnBackgroundColour(wxColour(m_spcRed->GetValue(), m_spcGreen->GetValue(), m_spcBlue->GetValue()));
	m_panColor->Refresh();
}

/**
 * fetches the button click and prepares creating a new cuboid
 * @param[in]       WXUNUSED        unused button-event
 */
void CreateCuboidFrame::OnCreate(wxCommandEvent& WXUNUSED(event))
{

}

/**
 * closes the window and cancels cuboid-creation
 * @param[in]       WXUNUSED        unused button-event
 */
void CreateCuboidFrame::OnCancel(wxCommandEvent& WXUNUSED(event))
{
	Destroy();
}
