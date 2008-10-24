#ifndef GNRMEDIATOR_H
#define GNRMEDIATOR_H

#include "GNRGLNotifyEvent.h"
#include "GNRGLCamera.h"
#include "GNREnum.h"

class GNRMediator
{
public:
	GNRMediator() {};
	virtual ~GNRMediator() {};
	void setTranslation(transType translation)
	{
		m_Translation = translation;
	};
	virtual void setAssemblyID(int assemblyID) = 0;
	virtual void setGLCamera(GNRGLCamera* camera) = 0;
	virtual void setMode(canvasType canvas_id) = 0;
	virtual void translate(GNRGLNotifyEvent& event) = 0;
protected:
	canvasType m_CanvasID;
	transType  m_Translation;
private:
};

#endif // GNRMEDIATOR_H
