#ifndef GNRASSEMBLYMEDIATOR2D_H
#define GNRASSEMBLYMEDIATOR2D_H

#include "GNRAssembly.h"
#include "GNRAssemblyMediator.h"

class GNRAssemblyMediator2D: public GNRAssemblyMediator
{
public:

	GNRAssemblyMediator2D() {};
	virtual ~GNRAssemblyMediator2D() {};
	
	void MoveXY(int m_x,int m_y);
	void MoveXZ(int m_x,int m_y);
	void RotateXY(int m_x,int m_y);
	void RotateXZ(int m_x,int m_y);
	
protected:

private:

};

#endif // GNRAssemblyMediator2D_H
