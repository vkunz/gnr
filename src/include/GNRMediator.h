/**
 * GNRMediator
 * @name        GNRMediator.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRMEDIATOR_H
#define GNRMEDIATOR_H

#include "GNRGLNotifyEvent.h"
#include "GNRGLCamera.h"
#include "GNRNotifyEvent.h"

class GNRMediator
{
public:

	GNRMediator();
	virtual ~GNRMediator();
	
	//global setting of stranslation type and active canvas
	void setTranslation(transType translation);
	transType getTranslation();
	void setSnapfunction(GNRNotifyEvent& event);
	void setMode(canvasType canvas_id);
	void doSnapMove(float& value);
	void doSnapRotate(float& value);
	
	//has to be implemented in derived classes
	virtual void setAssemblyID(int assemblyID) = 0;
	virtual void setGLCamera(GNRGLCamera* camera) = 0;
	virtual void initialize(GNRGLNotifyEvent& event) = 0;
	virtual int  translate(GNRGLNotifyEvent& event) = 0;
	virtual void finalize() = 0;
	
protected:

	static canvasType m_CanvasID;
	static transType  m_Translation;
	static int m_SnapGrid;
	static int m_SnapAngle;
	
private:

};

#endif // GNRMEDIATOR_H
