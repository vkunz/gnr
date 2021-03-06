/**
 * [TODO]
 *
 * @note        [DONE]
 * @name        CreateCuboidFrame.cpp
 * @date        2008-10-29
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/colour.h>
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "Color.h"
#include "CreateCuboidFrame.h"
#include "CreatePrimitiveEvent.h"
#include "GlobalDefine.h"
#include "Vertex.h"
#include "resources/gnr_icon.xpm"

const long CreateCuboidFrame::idSpcWidth = wxNewId();
const long CreateCuboidFrame::idSpcHeight = wxNewId();
const long CreateCuboidFrame::idSpcDepth = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT1 = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT2 = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT3 = wxNewId();
const long CreateCuboidFrame::idBuCreate = wxNewId();
const long CreateCuboidFrame::idBuCancel = wxNewId();
const long CreateCuboidFrame::ID_STATICTEXT4 = wxNewId();
const long CreateCuboidFrame::idColourPicker = wxNewId();


BEGIN_EVENT_TABLE(CreateCuboidFrame,wxFrame)
	EVT_BUTTON(idBuCreate, CreateCuboidFrame::OnCreate)
	EVT_BUTTON(idBuCancel, CreateCuboidFrame::OnCancel)
END_EVENT_TABLE()

CreateCuboidFrame::CreateCuboidFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	Create(parent, wxID_ANY, wxT("Kubus erstellen"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetClientSize(wxSize(382,230));
	CenterOnParent();
	SetBackgroundColour(wxNullColour);
	SetIcon(wxICON(gnr_icon));

	m_panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(382,260), wxTAB_TRAVERSAL);

	StaticText1 = new wxStaticText(m_panel, ID_STATICTEXT1, _("Breite (mm)"), wxPoint(56,30), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	m_spcWidth = new wxSpinCtrl(m_panel, idSpcWidth, wxT("1000"), wxPoint(128,25), wxSize(168,24), 0, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE, _T("idSpcWidth"));

	StaticText2 = new wxStaticText(m_panel, ID_STATICTEXT2, _("H" ouml "he (mm)"), wxPoint(56,65), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	m_spcHeight = new wxSpinCtrl(m_panel, idSpcHeight, wxT("1000"), wxPoint(128,60), wxSize(168,21), 0, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE, _T("idSpcHeight"));

	StaticText3 = new wxStaticText(m_panel, ID_STATICTEXT3, _("Tiefe (mm)"), wxPoint(56,100), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	m_spcDepth = new wxSpinCtrl(m_panel, idSpcDepth, wxT("1000"), wxPoint(128,95), wxSize(168,21), 0, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE, _T("idSpcDepth"));

	StaticText4 = new wxStaticText(m_panel, ID_STATICTEXT4, _("Farbe"), wxPoint(56,147), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	m_colourPicker = new wxColourPickerCtrl(m_panel, idColourPicker, wxColour(255,255,255), wxPoint(128, 142), wxSize(24,24));

	m_buCreate = new wxButton(m_panel, idBuCreate, _("Erstellen"), wxPoint(56,188), wxSize(88,23), 0, wxDefaultValidator, _T("idBuCreate"));
	m_buCancel = new wxButton(m_panel, idBuCancel, _("Abbrechen"), wxPoint(232,188), wxSize(88,23), 0, wxDefaultValidator, _T("idBuCancel"));
}

CreateCuboidFrame::~CreateCuboidFrame() {}

/**
 * fetches the button click and prepares creating a new cuboid
 * @param[in]       WXUNUSED        unused button-event
 */
void CreateCuboidFrame::OnCreate(wxCommandEvent& WXUNUSED(event))
{
	Vertex middlePoint(0.0, 0.0, 0.0);
	Vertex orientation(0.0, 0.0, 0.0);
	Vertex dimension((float)m_spcWidth->GetValue() / 1000, (float)m_spcHeight->GetValue() / 1000, (float)m_spcDepth->GetValue() / 1000);
	Color color(m_colourPicker->GetColour().Red(), m_colourPicker->GetColour().Green(), m_colourPicker->GetColour().Blue());
	CreatePrimitiveEvent myevent(wxEVT_COMMAND_GNR_CREATE_PRIMITIVE);
	myevent.SetEventObject(this);
	myevent.setPrimitiveType(CUBOID);
	myevent.setPosition(middlePoint);
	myevent.setAngles(orientation);
	myevent.setDimensions(dimension);
	myevent.setColor(color);
	ProcessEvent(myevent);
	Destroy();
}

/**
 * closes the window and cancels cuboid-creation
 * @param[in]       WXUNUSED        unused button-event
 */
void CreateCuboidFrame::OnCancel(wxCommandEvent& WXUNUSED(event))
{
	Destroy();
}
