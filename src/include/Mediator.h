/**
 * Mediator
 * @name        Mediator.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "GLNotifyEvent.h"
#include "Assembly.h"
#include "GLCamera.h"
#include "NotifyEvent.h"

class Mediator
{
public:

	Mediator();
	virtual ~Mediator();
	
	//global setting of stranslation type and active canvas
	void setTranslation(transType translation);
	transType getTranslation();
	void setSnapfunction(NotifyEvent& event);
	void setMode(canvasType canvas_id);
	void doSnapMove(float& value);
	void doSnapRotate(float& value);
	
	//has to be implemented in derived classes
	virtual void setAssembly(Assembly* assembly) = 0;
	virtual void setGLCamera(GLCamera* camera) = 0;
	virtual void initialize(GLNotifyEvent& event) = 0;
	virtual int  translate(GLNotifyEvent& event) = 0;
	virtual void finalize() = 0;
	
protected:

	static canvasType m_CanvasID;
	static transType  m_Translation;
	static int m_SnapGrid;
	static int m_SnapAngle;
	
private:

};

#endif // MEDIATOR_H
