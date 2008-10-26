#ifndef GNRMEDIATOR_H
#define GNRMEDIATOR_H

#include "GNRGLNotifyEvent.h"
#include "GNRGLCamera.h"
#include "GNREnum.h"

class GNRMediator
{
public:

	GNRMediator();
	virtual ~GNRMediator();
	
	//global setting of stranslation type and active canvas
	void setTranslation(transType translation);
	void setMode(canvasType canvas_id);
	
	//has to be implemented in derived classes
	virtual void setAssemblyID(int assemblyID) = 0;
	virtual void setGLCamera(GNRGLCamera* camera) = 0;
	virtual void initialize(GNRGLNotifyEvent& event) = 0;
	virtual int  translate(GNRGLNotifyEvent& event) = 0;
	
protected:

	static canvasType m_CanvasID;
	static transType  m_Translation;
	
private:

};

#endif // GNRMEDIATOR_H
