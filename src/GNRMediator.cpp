#include "GNRGlobalDefine.h"
#include "GNRMediator.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

//global static storage for all mediators
canvasType GNRMediator::m_CanvasID;
transType  GNRMediator::m_Translation;
int GNRMediator::m_SnapGrid  = 1;
int GNRMediator::m_SnapAngle = 1;

/**
 * constructor of GNRMediator is useless
 * @access      public
 */
GNRMediator::GNRMediator()
{}

/**
 * destructor of GNRMediator is useless
 * @access      public
 */
GNRMediator::~GNRMediator()
{}

/**
 * set translation type for all mediators
 * @param       transType       id of translation
 * @access      public
 */
void GNRMediator::setTranslation(transType translation)
{
	m_Translation = translation;
}

/**
 * set active canvas for all mediators
 * @param       canvasType       id of active canvas
 * @access      public
 */
void GNRMediator::setMode(canvasType canvas_id)
{
	m_CanvasID = canvas_id;
}

/**
 * set active canvas for all mediators
 * @param       GNRNotifyEvent       event from toolbar button
 * @access      public
 */
void GNRMediator::setSnapfunction(GNRNotifyEvent& event)
{
	m_SnapGrid  = 5*event.getSnapToGrid();
	m_SnapAngle = event.getSnapToAngle();
}

/**
 * calculate snap to grid moving value
 * @param       float       value to round for snapping
 * @access      public
 */
void GNRMediator::doSnapMove(float& value)
{
	float new_value = round(value*((float)SNAP_IN_MAXIMUM_UNIT/(float)m_SnapGrid))/((float)SNAP_IN_MAXIMUM_UNIT/(float)m_SnapGrid);
	//if value reaches about SNAP_APPROACH_PERC (25%) of grid value, snap in
	if (fabs(value - new_value)*(float)SNAP_IN_MAXIMUM_UNIT/(float)m_SnapGrid < SNAP_APPROACH_PERC)
	{
		value = new_value;
	}
}

/**
 * calculate snap to angle rotating value
 * @param       float       value to round for snapping
 * @access      public
 */
void GNRMediator::doSnapRotate(float& value)
{
	float new_value = round(value/(float)m_SnapAngle)*(float)m_SnapAngle;
	//if angle reaches about SNAP_APPROACH_PERC (25%) of snapping angle, snap in
	if (fabs(value - new_value)/(float)m_SnapAngle < SNAP_APPROACH_PERC)
	{
		value = new_value;
	}
}
