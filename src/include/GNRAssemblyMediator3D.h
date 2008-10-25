#ifndef GNRASSEMBLYMEDIATOR3D_H
#define GNRASSEMBLYMEDIATOR3D_H

#include "GNRAssembly.h"
#include "GNRAssemblyMediator.h"

class GNRAssemblyMediator3D: public GNRAssemblyMediator
{
public:

	GNRAssemblyMediator3D() {};
	virtual ~GNRAssemblyMediator3D() {};
	
	void MoveXY(int m_x,int m_y);
	void MoveXZ(int m_x,int m_y);
	void RotateXY(int m_x,int m_y);
	void RotateXZ(int m_x,int m_y);
	
protected:

private:

};

#endif // GNRAssemblyMediator3D_H
