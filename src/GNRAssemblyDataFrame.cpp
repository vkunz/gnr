#include "include/GNRAssemblyDataFrame.h"

#include <wx/intl.h>
#include <wx/string.h>
#include <wx/valtext.h>

#include "GNRNotifyEvent.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "resources/gnr_icon.xpm"
#endif

const long GNRAssemblyDataFrame::idtxcName = wxNewId();
const long GNRAssemblyDataFrame::idtxcWidth = wxNewId();
const long GNRAssemblyDataFrame::idtxcHeight = wxNewId();
const long GNRAssemblyDataFrame::idtxcDepth = wxNewId();
const long GNRAssemblyDataFrame::idcbxVisible = wxNewId();
const long GNRAssemblyDataFrame::idcbxProportion = wxNewId();
const long GNRAssemblyDataFrame::idBtnChange = wxNewId();
const long GNRAssemblyDataFrame::idBtnCancel = wxNewId();


BEGIN_EVENT_TABLE(GNRAssemblyDataFrame,wxFrame)
	EVT_CLOSE(GNRAssemblyDataFrame::OnClose)
	EVT_BUTTON(idBtnChange, GNRAssemblyDataFrame::OnChange)
	EVT_BUTTON(idBtnCancel, GNRAssemblyDataFrame::OnCancel)
	EVT_TEXT(idtxcWidth, GNRAssemblyDataFrame::OnWidthChange)
	EVT_TEXT(idtxcHeight, GNRAssemblyDataFrame::OnHeightChange)
	EVT_TEXT(idtxcDepth, GNRAssemblyDataFrame::OnDepthChange)
END_EVENT_TABLE()

GNRAssemblyDataFrame::GNRAssemblyDataFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	Create(parent, id, wxT("Objekt-Eigenschaften"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	MakeModal();
	SetClientSize(wxSize(350, 300));
	SetBackgroundColour(wxNullColour);
	SetIcon(wxICON(GNR_ICON));

	m_stxName = new wxStaticText(this, -1, wxT("Name:"), wxPoint(30,34), wxSize(80,22), 0);
	m_txcName = new wxTextCtrl(this, idtxcName, wxT(""), wxPoint(120,30), wxSize(150,22), 0, wxDefaultValidator);

	m_stxWidth = new wxStaticText(this, -1, wxT("Breite (mm):"), wxPoint(30,84), wxSize(80,22), 0);
	m_txcWidth = new wxTextCtrl(this, idtxcWidth, wxT(""), wxPoint(120,80), wxSize(150,22), 0, wxTextValidator(wxFILTER_NUMERIC));

	m_stxHeight = new wxStaticText(this, -1, wxT("Höhe (mm):"), wxPoint(30,114), wxSize(80,22), 0);
	m_txcHeight = new wxTextCtrl(this, idtxcHeight, wxT(""), wxPoint(120,110), wxSize(150,22), 0, wxTextValidator(wxFILTER_NUMERIC));

	m_stxDepth = new wxStaticText(this, -1, wxT("Tiefe (mm):"), wxPoint(30,144), wxSize(80,22), 0);
	m_txcDepth = new wxTextCtrl(this, idtxcDepth, wxT(""), wxPoint(120,140), wxSize(150,22), 0, wxTextValidator(wxFILTER_NUMERIC));

	m_cbxProportion = new wxCheckBox(this, idcbxProportion, wxT("Proportionen beibehalten"), wxPoint(120, 170), wxSize(160, 22));
	m_cbxProportion->SetValue(true);

	m_stxVisible = new wxStaticText(this, -1, wxT("Sichtbar:"), wxPoint(30,212), wxSize(80,22), 0);
	m_cbxVisible = new wxCheckBox(this, idcbxVisible, wxEmptyString, wxPoint(120, 210), wxSize(80, 22));

	m_btnChange     = new wxButton(this, idBtnChange, wxT("Ändern"), wxPoint(70,255), wxDefaultSize, 0);
	m_btnCancel     = new wxButton(this, idBtnCancel, wxT("Abbrechen"), wxPoint(190,255), wxDefaultSize, 0);
}

GNRAssemblyDataFrame::~GNRAssemblyDataFrame()
{

}

void GNRAssemblyDataFrame::fillFields(GNRAssembly* assembly)
{
	m_assembly = assembly;

	wxString str;

	m_txcName->ChangeValue(assembly->getName());

	str << (int)(assembly->getWidth()*assembly->getScaleX()*1000);
	m_txcWidth->ChangeValue(str);

	str.clear();
	str << (int)(assembly->getHeight()*assembly->getScaleY()*1000);
	m_txcHeight->ChangeValue(str);

	str.clear();
	str << (int)(assembly->getDepth()*assembly->getScaleZ()*1000);
	m_txcDepth->ChangeValue(str);

	m_cbxVisible->SetValue(m_assembly->isVisible());

	m_assemblyWidth = assembly->getWidth() * 1000;
	m_assemblyHeight = assembly->getHeight() * 1000;
	m_assemblyDepth = assembly->getDepth() * 1000;
}

void GNRAssemblyDataFrame::OnChange(wxCommandEvent& WXUNUSED(event))
{
	m_assembly->setName(m_txcName->GetValue());

	double factor = wxAtof(m_txcWidth->GetValue()) / m_assemblyWidth;
	m_assembly->setScaleX(factor);

	factor = wxAtof(m_txcHeight->GetValue()) / m_assemblyHeight;
	m_assembly->setScaleY(factor);

	factor = wxAtof(m_txcDepth->GetValue()) / m_assemblyDepth;
	m_assembly->setScaleZ(factor);

	m_assembly->setVisible(m_cbxVisible->IsChecked());

	m_assembly->putOnGround();

	// send event to refresh canvas
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(GLREFRESH);
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);

	// send event to refresh tree
	myevent.setGNREventType(REFRESHSCENETREE);
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);

	MakeModal(false);
	Destroy();
}

void GNRAssemblyDataFrame::OnCancel(wxCommandEvent& WXUNUSED(event))
{
	MakeModal(false);
	Destroy();
}

void GNRAssemblyDataFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
	MakeModal(false);
	Destroy();
}

void GNRAssemblyDataFrame::OnWidthChange(wxCommandEvent& event)
{
	if (m_cbxProportion->IsChecked() == true)
	{
		wxString str;
		double width = wxAtof(m_txcWidth->GetValue());

		str << (width / m_assemblyWidth) * m_assemblyHeight;
		m_txcHeight->ChangeValue(str);

		str.Clear();
		str << (width / m_assemblyWidth) * m_assemblyDepth;
		m_txcDepth->ChangeValue(str);
	}
}

void GNRAssemblyDataFrame::OnHeightChange(wxCommandEvent& event)
{
	if (m_cbxProportion->IsChecked() == true)
	{
		wxString str;
		double height = wxAtof(m_txcHeight->GetValue());

		str << (height / m_assemblyHeight) * m_assemblyWidth;
		m_txcWidth->ChangeValue(str);

		str.Clear();
		str << (height / m_assemblyHeight) * m_assemblyDepth;
		m_txcDepth->ChangeValue(str);
	}
}

void GNRAssemblyDataFrame::OnDepthChange(wxCommandEvent& event)
{
	if (m_cbxProportion->IsChecked() == true)
	{
		wxString str;
		double depth = wxAtof(m_txcDepth->GetValue());

		str << (depth / m_assemblyDepth) * m_assemblyWidth;
		m_txcWidth->ChangeValue(str);

		str.Clear();
		str << (depth / m_assemblyDepth) * m_assemblyHeight;
		m_txcHeight->ChangeValue(str);
	}
}
