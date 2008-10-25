#include "GNRMediator.h"

canvasType GNRMediator::m_CanvasID;
transType  GNRMediator::m_Translation;

GNRMediator::GNRMediator()
{}

GNRMediator::~GNRMediator()
{}

//set translation type by toolbar button
void GNRMediator::setTranslation(transType translation)
{
	m_Translation = translation;
}

//set 3D or 2D mode from canvas_id
void GNRMediator::setMode(canvasType canvas_id)
{
	m_CanvasID = canvas_id;
}
