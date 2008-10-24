#ifndef GNRASSEMBLYMEDIATOR_H
#define GNRASSEMBLYMEDIATOR_H

#include "GNRMediator.h"
#include "GNREnum.h"

class GNRAssemblyMediator: public GNRMediator
{
public:
	GNRAssemblyMediator();
	void setMode(canvasType canvas_id);
	void translate(GNRGLNotifyEvent& event);
	virtual ~GNRAssemblyMediator();
protected:
private:
};

#endif // GNRASSEMBLYMEDIATOR_H
