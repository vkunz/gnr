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
	
	//set translation type by toolbar button
	void setTranslation(transType translation)
	{
		m_Translation = translation;
	};
	
	//set 3D or 2D mode from canvas_id
	void setMode(canvasType canvas_id)
	{
		m_CanvasID = canvas_id;
	}
	
	//has to be implemented in derived classes
	virtual void setAssemblyID(int assemblyID) = 0;
	virtual void setGLCamera(GNRGLCamera* camera) = 0;
	virtual void initialize(GNRGLNotifyEvent& event) = 0;
	virtual int  translate(GNRGLNotifyEvent& event) = 0;
	
protected:

	canvasType m_CanvasID;
	transType  m_Translation;
	
private:

};

#endif // GNRMEDIATOR_H
