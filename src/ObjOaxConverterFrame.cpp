/**
 * ObjOaxConverterFrame
 * @name        ObjOaxConverterFrame.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/icon.h>
#include <wx/spinctrl.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "AssemblyData.h"
#include "Enum.h"
#include "GLCanvasPreview.h"
#include "GlobalDefine.h"
#include "NotifyEvent.h"
#include "ObjOaxConverterFrame.h"
#include "resources/gnr_icon.xpm"

const long ObjOaxConverterFrame::idBtnCreate     = wxNewId();
const long ObjOaxConverterFrame::idBtnCancel     = wxNewId();
const long ObjOaxConverterFrame::idCkbProportion = wxNewId();
const long ObjOaxConverterFrame::idSpcWidth      = wxNewId();
const long ObjOaxConverterFrame::idSpcDepth      = wxNewId();
const long ObjOaxConverterFrame::idSpcHeight     = wxNewId();
const long ObjOaxConverterFrame::idStxName       = wxNewId();
const long ObjOaxConverterFrame::idStxWidth      = wxNewId();
const long ObjOaxConverterFrame::idStxDepth      = wxNewId();
const long ObjOaxConverterFrame::idStxHeight     = wxNewId();
const long ObjOaxConverterFrame::idTxcName       = wxNewId();

/**
 * constructor of ObjOaxConverterFrame builds frame for obj import
 */
ObjOaxConverterFrame::ObjOaxConverterFrame(wxWindow* parent, wxWindowID id)
{
	// create Frame
	Create(parent, id, wxT("OBJ importieren"), wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSTATIC_BORDER, wxT("ObjOaxConverter"));

	// set size
	SetClientSize(wxSize(550, 350));

	// make frame modal
	MakeModal();

	// use window color of user
	SetBackgroundColour(wxNullColour);

	//set icon of frame
	SetIcon(wxICON(gnr_icon));

	m_panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(550, 350), wxTAB_TRAVERSAL);

	// StaticText name
	m_stxName       = new wxStaticText(m_panel, idStxName, wxT("Name:"), wxPoint(280,54), wxSize(100,24), 0);
	// TextCtrl name
	m_txcName       = new wxTextCtrl(m_panel, idTxcName, wxT(""), wxPoint(384,50), wxSize(130,24), wxTE_PROCESS_ENTER);

	// StaticText width
	m_stxWidth      = new wxStaticText(m_panel, idStxWidth, wxT("Breite (mm):"), wxPoint(280,134), wxSize(100 ,24), 0);
	// SpinCtrl width
	m_spcWidth      = new wxSpinCtrl(m_panel, idSpcWidth, wxT("1"), wxPoint(384,130), wxSize(130,24), wxTE_PROCESS_ENTER, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE);

	// StaticText depth
	m_stxDepth      = new wxStaticText(m_panel, idStxDepth, wxT("Tiefe (mm):"), wxPoint(280,174), wxSize(100,24), 0);
	// SpinCtrl depth
	m_spcDepth      = new wxSpinCtrl(m_panel, idSpcDepth, wxT("1"), wxPoint(384,170), wxSize(130,24), wxTE_PROCESS_ENTER, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE);

	// StaticText height
	m_stxHeight     = new wxStaticText(m_panel, idStxHeight, wxT("H\u00F6he (mm):"), wxPoint(280,214), wxSize(100,24), 0);
	// SpinCtrl height
	m_spcHeight     = new wxSpinCtrl(m_panel, idSpcHeight, wxT("1"), wxPoint(384,210), wxSize(130,24), wxTE_PROCESS_ENTER, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE);

	// Checkbox proportion
	m_ckbProportion = new wxCheckBox(m_panel, idCkbProportion, wxT("Proportionen behalten"), wxPoint(312,248), wxSize(130,24), 0);
	m_ckbProportion->SetValue(true);

	// Button create
	m_btnCreate     = new wxButton(m_panel, idBtnCreate, wxT("Erstellen"), wxPoint(328,304), wxDefaultSize, 0);
	// Button cancel
	m_btnCancel     = new wxButton(m_panel, idBtnCancel, wxT("Abbrechen"), wxPoint(432,304), wxDefaultSize, 0);

	// connects m_btnCreate with OnBtnCreate()
	Connect(idBtnCreate,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ObjOaxConverterFrame::OnBtnCreate);

	// connects m_btnCancel with OnBtnCancel()
	Connect(idBtnCancel,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ObjOaxConverterFrame::OnBtnCancel);

	// connects Close-Button with OnClose()
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&ObjOaxConverterFrame::OnClose);

	// connects m_spcWidth with OnSpcWidthChanged
	Connect(idSpcWidth,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ObjOaxConverterFrame::OnSpcWidthChanged);

	// connects m_spcDepth with OnSpcDepthChanged
	Connect(idSpcDepth,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ObjOaxConverterFrame::OnSpcDepthChanged);

	// connects m_spcHeight with OnSpcHeightChanged
	Connect(idSpcHeight,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ObjOaxConverterFrame::OnSpcHeightChanged);

	// connects m_spcWidth with OnSpcWidthChanged on press Enter
	Connect(idSpcWidth,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&ObjOaxConverterFrame::OnSpcWidthChanged);

	// connects m_spcDepth with OnSpcDepthChanged on press Enter
	Connect(idSpcDepth,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&ObjOaxConverterFrame::OnSpcDepthChanged);

	// connects m_spcHeight with OnSpcHeightChanged on press Enter
	Connect(idSpcHeight,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&ObjOaxConverterFrame::OnSpcHeightChanged);

	// connects m_txcname with OnTxcNameChanged on press Enter
	Connect(idTxcName,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&ObjOaxConverterFrame::OnTxcNameChanged);

	// create canvas
	m_canvas = new GLCanvasPreview(m_panel, wxID_ANY, wxPoint(50, 50), wxSize(200, 200), wxNO_BORDER);

	// connects m_txcName with OnTxcNameChanged
	Connect(idTxcName,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ObjOaxConverterFrame::OnTxcNameChanged);
}

/**
 * destructor of ObjOaxConverterFrame cleans up pointer
 */
ObjOaxConverterFrame::~ObjOaxConverterFrame()
{
	delete m_canvas;

	delete m_txcName;

	delete m_stxName;
	delete m_stxHeight;
	delete m_stxDepth;
	delete m_stxWidth;

	delete m_spcWidth;
	delete m_spcHeight;
	delete m_spcDepth;

	delete m_ckbProportion;

	delete m_btnCreate;
	delete m_btnCancel;
}

/**
 * set assembly data
 * @param[in]       data        AssemblyData* pointer to data for assembly
 */
void ObjOaxConverterFrame::setAssemblyData(AssemblyData* data)
{
	m_assemblyData = data;
}

/**
 * set data and update frame
 */
void ObjOaxConverterFrame::setData()
{
	// set data
	m_width         = m_assemblyData->m_width;
	m_depth         = m_assemblyData->m_depth;
	m_height        = m_assemblyData->m_height;
	m_name          = m_assemblyData->m_name;

	// if a dimension is greater than SIZE_MAXIMUM_VALUE, rescale
	if (m_width > SIZE_MAXIMUM_VALUE || m_depth > SIZE_MAXIMUM_VALUE || m_height > SIZE_MAXIMUM_VALUE)
	{
		// return max of dimenstions and get scale
		double scale = (max(m_width, m_depth, m_height)) / SIZE_MAXIMUM_VALUE;

		// divide by scale
		m_width = (int)(m_width / scale);
		m_depth = (int)(m_depth / scale);
		m_height = (int)(m_height / scale);
	}

	// update frame
	updateFrame();
}

/**
 * get preview canvas pointer
 * @return       GLCanvasPreview*        pointer to preview canvas
 */
GLCanvasPreview* ObjOaxConverterFrame::getCanvasPointer()
{
	return m_canvas;
}

/**
 * on pressing cancel button
 * @param[in]       WXUNUSED        unused event of button
 */
void ObjOaxConverterFrame::OnBtnCancel(wxCommandEvent& WXUNUSED(event))
{
	// disable modal
	MakeModal(false);

	// create event
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);

	// set eventType
	gnrevent.setGNREventType(CANCELCONVERTION);

	// broadcast event
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * on pressing create button
 * @param[in]       WXUNUSED        unused event of button
 */
void ObjOaxConverterFrame::OnBtnCreate(wxCommandEvent& WXUNUSED(event))
{
	// disable modal
	MakeModal(false);

	// prepare data -> store into struct
	// get objName and store into struct
	m_assemblyData->m_name = m_txcName->GetValue();

	// calc width-scale
	m_assemblyData->m_scaleWidth = (((m_width) / m_assemblyData->m_width));

	// calc y-scale
	m_assemblyData->m_scaleDepth = (((m_depth) / m_assemblyData->m_depth));

	// calc z-scale
	m_assemblyData->m_scaleHeight = (((m_height) / m_assemblyData->m_height));

	// get width and store into struct
	m_assemblyData->m_width = (m_spcWidth->GetValue());

	// get depth and store into struct
	m_assemblyData->m_depth = (m_spcDepth->GetValue());

	// get height and store into struct
	m_assemblyData->m_height = (m_spcHeight->GetValue());

	// create event
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);

	// set eventType
	gnrevent.setGNREventType(OBJOAXCONVERSION);

	// set frameData pointer
	gnrevent.setAssemblyDataPointer(m_assemblyData);

	// broadcast event
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * on pressing close button
 * @param[in]       WXUNUSED        unused event of button
 */
void ObjOaxConverterFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
	// disable modal
	MakeModal(false);

	// create event
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);

	// set eventType
	gnrevent.setGNREventType(CANCELCONVERTION);

	// broadcast event
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * on changing width in spincontrol
 * @param[in]       event        wxSpinEvent event of spin control
 */
void ObjOaxConverterFrame::OnSpcWidthChanged(wxSpinEvent& event)
{
	// check if aspect ratio is enabled
	if (m_ckbProportion->GetValue())
	{
		// get scale, calc actual value divide by m_assemblyData-value
		m_scaleWidth = (double)event.GetInt() / m_assemblyData->m_width;

		// set new m_width
		m_width = event.GetInt();

		// set new dimenstions with new scale
		m_depth = (m_scaleWidth * m_assemblyData->m_depth);
		m_height = (m_scaleWidth * m_assemblyData->m_height);

		// update frame
		updateFrame();
	}
	else
	{
		// set new value
		m_width = event.GetInt();

		// update frame
		updateFrame();
	}
}

/**
 * on changing depth in spincontrol
 * @param[in]       event        wxSpinEvent event of spin control
 */
void ObjOaxConverterFrame::OnSpcDepthChanged(wxSpinEvent& event)
{
	// check if aspect ratio is enabled
	if (m_ckbProportion->GetValue())
	{
		// get scale, calc actual value divide by m_assemblyData-value
		m_scaleDepth = (float)event.GetInt() / m_assemblyData->m_depth;

		// set new m_width
		m_depth = event.GetInt();

		// set new dimenstions with new scale
		m_width = (int)(m_scaleDepth * m_assemblyData->m_width);
		m_height = (int)(m_scaleDepth * m_assemblyData->m_height);

		// update frame
		updateFrame();
	}
	else
	{
		// set new value
		m_depth = event.GetInt();

		// update frame
		updateFrame();
	}
}

/**
 * on changing height in spincontrol
 * @param[in]       event        wxSpinEvent event of spin control
 */
void ObjOaxConverterFrame::OnSpcHeightChanged(wxSpinEvent& event)
{
	// check if aspect ratio is enabled
	if (m_ckbProportion->GetValue())
	{
		// get scale, calc actual value divide by m_assemblyData-value
		m_scaleHeight = (float)event.GetInt() / m_assemblyData->m_height;

		// set new m_width
		m_height = event.GetInt();

		// set new dimenstions with new scale
		m_width = (int)(m_scaleHeight * m_assemblyData->m_width);
		m_depth = (int)(m_scaleHeight * m_assemblyData->m_depth);

		// update frame
		updateFrame();
	}
	else
	{
		// set new value
		m_height = event.GetInt();

		// update frame
		updateFrame();
	}
}

/**
 * on name changed set new name
 * @param[in]       WXUNUSED        unused event of button
 */
void ObjOaxConverterFrame::OnTxcNameChanged(wxCommandEvent& WXUNUSED(event))
{
	// get new Value
	m_name = m_txcName->GetValue();
}

/**
 * update whole frame
 */
void ObjOaxConverterFrame::updateFrame()
{
	// update name
	m_txcName->SetValue(m_name);

	// update width
	m_spcWidth->SetValue((int)m_width);

	// update depth
	m_spcDepth->SetValue((int)m_depth);

	// update height
	m_spcHeight->SetValue((int)m_height);
}

/**
 * get max from size of object dimensions
 * @param[in]       width       width of object
 * @param[in]       depth       width of object
 * @param[in]       height      width of object
 * @return          float       maximum of all dimensions
 */
double ObjOaxConverterFrame::max(double width, double depth, double height)
{
	double max = width;

	if (max < depth)
	{
		max = depth;
	}

	if (max < height)
	{
		max = height;
	}

	return max;
}
