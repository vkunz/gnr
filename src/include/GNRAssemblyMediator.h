#ifndef GNRASSEMBLYMEDIATOR_H
#define GNRASSEMBLYMEDIATOR_H

#include "GNRMediator.h"
#include "GNRAssembly.h"

class GNRAssemblyMediator: public GNRMediator
{
public:

	GNRAssemblyMediator();
	void setMode(canvasType canvas_id);
	void setAssemblyID(int assemblyID);         //set selected assembly id
	void setGLCamera(GNRGLCamera* camera) {};   //not needed in assembly mediator
	void translate(GNRGLNotifyEvent& event);    //perform translation to assembly
	virtual ~GNRAssemblyMediator();
	
protected:

private:
	GNRAssembly* m_Assembly;
	
};

#endif // GNRASSEMBLYMEDIATOR_H
