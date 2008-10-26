#include "GNRMediator.h"

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
	m_SnapGrid  = event.getSnapToGrid();
	m_SnapAngle = event.getSnapToAngle();
}

/**
 * calculate snap to grid moving value
 * @param       float       value to round for snapping
 * @access      public
 */
void GNRMediator::doSnapMove(float& value)
{
	//maximum snapping 1000 mm
	value = round(value*(1000/m_SnapGrid))/(1000/m_SnapGrid);
}

/**
 * calculate snap to angle rotating value
 * @param       float       value to round for snapping
 * @access      public
 */
void GNRMediator::doSnapRotate(float& value)
{
	//maximum snapping 90 degree
	value = round(value/m_SnapAngle)*m_SnapAngle;
}
