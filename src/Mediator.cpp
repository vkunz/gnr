/**
 * Mediator
 *
 * @name        Mediator.cpp
 * @date        2008-10-09
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GlobalDefine.h"
#include "Mediator.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

//global static storage for all mediators
canvasType Mediator::m_CanvasID;
transType  Mediator::m_Translation;
int Mediator::m_SnapGrid  = SNAP_IN_DEFAULT_GRID;
int Mediator::m_SnapAngle = SNAP_IN_DEFAULT_ANGLE;

/**
 * constructor of Mediator is useless

 */
Mediator::Mediator() {}

/**
 * destructor of Mediator is useless

 */
Mediator::~Mediator() {}

/**
 * set translation type for all mediators
 * @param       transType       id of translation

 */
void Mediator::setTranslation(transType translation)
{
	m_Translation = translation;
}

/**
 * get translation type for all mediators
 * @return      transType       id of translation

 */
transType Mediator::getTranslation()
{
	return m_Translation;
}

/**
 * set active canvas for all mediators
 * @param       canvasType       id of active canvas

 */
void Mediator::setMode(canvasType canvas_id)
{
	m_CanvasID = canvas_id;
}

/**
 * set active canvas for all mediators
 * @param       NotifyEvent       event from toolbar button

 */
void Mediator::setSnapfunction(NotifyEvent& event)
{
	m_SnapGrid  = 5*event.getSnapToGrid();
	m_SnapAngle = event.getSnapToAngle();
}

/**
 * calculate snap to grid moving value
 * @param       float       value to round for snapping

 */
void Mediator::doSnapMove(float& value)
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

 */
void Mediator::doSnapRotate(float& value)
{
	float new_value = round(value/(float)m_SnapAngle)*(float)m_SnapAngle;
	//if angle reaches about SNAP_APPROACH_PERC (25%) of snapping angle, snap in
	if (fabs(value - new_value)/(float)m_SnapAngle < SNAP_APPROACH_PERC)
	{
		value = new_value;
	}
}