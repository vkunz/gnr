#include "GNRCommandAssembly.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

GNRCommandAssembly::GNRCommandAssembly()
{
	//ctor
}

GNRCommandAssembly::~GNRCommandAssembly()
{
	//dtor
}

void GNRCommandAssembly::execute()
{
	m_usedAssembly->setX(new_x);
	m_usedAssembly->setY(new_y);
	m_usedAssembly->setZ(new_z);
	
	m_usedAssembly->setPhi(new_phi);
	m_usedAssembly->setTheta(new_theta);
	m_usedAssembly->setRho(new_rho);
}

void GNRCommandAssembly::unexecute()
{
	m_usedAssembly->setX(old_x);
	m_usedAssembly->setY(old_y);
	m_usedAssembly->setZ(old_z);
	
	m_usedAssembly->setPhi(old_phi);
	m_usedAssembly->setTheta(old_theta);
	m_usedAssembly->setRho(old_rho);
}

void GNRCommandAssembly::setAssembly(GNRAssembly* assembly)
{
	m_usedAssembly = assembly;
}

void GNRCommandAssembly::setOldPosition(GNRVertex& old_pos)
{
	old_x = old_pos.getX();
	old_y = old_pos.getY();
	old_z = old_pos.getZ();
}

void GNRCommandAssembly::setOldAngles(GNRVertex& old_angles)
{
	old_phi     = old_angles.getX();
	old_theta   = old_angles.getY();
	old_rho     = old_angles.getZ();
}

void GNRCommandAssembly::setNewPosition(GNRVertex& new_pos)
{
	new_x = new_pos.getX();
	new_y = new_pos.getY();
	new_z = new_pos.getZ();
}

void GNRCommandAssembly::setNewAngles(GNRVertex& new_angles)
{
	new_phi     = new_angles.getX();
	new_theta   = new_angles.getY();
	new_rho     = new_angles.getZ();
}
