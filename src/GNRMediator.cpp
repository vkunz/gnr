#include "GNRMediator.h"

//global static storage for all mediators
canvasType GNRMediator::m_CanvasID;
transType  GNRMediator::m_Translation;

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
