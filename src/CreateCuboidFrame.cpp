#include "include/CreateCuboidFrame.h"

#include <wx/colour.h>
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>

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
const long CreateCuboidFrame::idBuCreate = wxNewId();
const long CreateCuboidFrame::idBuCancel = wxNewId();
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
END_EVENT_TABLE()

CreateCuboidFrame::CreateCuboidFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	Create(parent, wxID_ANY, wxT("Kubus erstellen"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(382,260));
	SetBackgroundColour(wxNullColour);
	SetIcon(wxICON(gnr_icon));
	
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Breite"), wxPoint(56,30), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	m_spcWidth = new wxSpinCtrl(this, idSpcWidth, _T("0"), wxPoint(128,25), wxSize(168,24), 0, 0, 100, 0, _T("idSpcWidth"));
	
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Höhe"), wxPoint(56,65), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	m_spcHeight = new wxSpinCtrl(this, idSpcHeight, _T("0"), wxPoint(128,60), wxSize(168,21), 0, 0, 100, 0, _T("idSpcHeight"));
	
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Tiefe"), wxPoint(56,100), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	m_spcDepth = new wxSpinCtrl(this, idSpcDepth, _T("0"), wxPoint(128,95), wxSize(168,21), 0, 0, 100, 0, _T("idSpcDepth"));
	
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Farbe"), wxPoint(32,157), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	m_panColor = new wxPanel(this, idPanColor, wxPoint(80,151), wxSize(24,24), wxTAB_TRAVERSAL, _T("idPanColor"));
	m_panColor->SetOwnBackgroundColour(wxColour(255, 255, 255));
	
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("R"), wxPoint(115,157), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	m_spcRed = new wxSpinCtrl(this, idSpcRed, _T("255"), wxPoint(128,153), wxSize(55,21), 0, 0, 255, 255, _T("idSpcRed"));
	
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("G"), wxPoint(195,157), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	m_spcGreen = new wxSpinCtrl(this, idSpcGreen, _T("255"), wxPoint(208,153), wxSize(56,21), 0, 0, 255, 255, _T("idSpcGreen"));
	
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("B"), wxPoint(275,157), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	m_spcBlue = new wxSpinCtrl(this, idSpcBlue, _T("255"), wxPoint(288,153), wxSize(56,21), 0, 0, 255, 255, _T("idSpcBlue"));
	
	m_buCreate = new wxButton(this, idBuCreate, _("Erstellen"), wxPoint(56,208), wxSize(88,23), 0, wxDefaultValidator, _T("idBuCreate"));
	m_buCancel = new wxButton(this, idBuCancel, _("Abbrechen"), wxPoint(232,208), wxSize(88,23), 0, wxDefaultValidator, _T("idBuCancel"));
}

CreateCuboidFrame::~CreateCuboidFrame() {}

void CreateCuboidFrame::OnSpcColorChange(wxSpinEvent& WXUNUSED(event))
{
	m_panColor->SetOwnBackgroundColour(wxColour(m_spcRed->GetValue(), m_spcGreen->GetValue(), m_spcBlue->GetValue()));
	m_panColor->Refresh();
}
