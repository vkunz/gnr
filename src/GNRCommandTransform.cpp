/**
 * This class handels all the information, needed to undo/redo a translation to an assembly
 * and also performs these operations
 * @name        GNRCommandTransform.cpp
 * @date        2008-10-29
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRCommandTransform.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GNRCommandTransform

 */
GNRCommandTransform::GNRCommandTransform() {}

/**
 * destructor of GNRCommandTransform

 */
GNRCommandTransform::~GNRCommandTransform() {}

/**
 * Performes the redo-operation and moves the object back to the new position

 */
void GNRCommandTransform::execute()
{
	m_usedAssembly->setX(new_x);
	m_usedAssembly->setY(new_y);
	m_usedAssembly->setZ(new_z);
	
	m_usedAssembly->setPhi(new_phi);
	m_usedAssembly->setTheta(new_theta);
	m_usedAssembly->setRho(new_rho);
}

/**
 * Performes the undo-operation and moves the object back to the originally position

 */
void GNRCommandTransform::unexecute()
{
	m_usedAssembly->setX(old_x);
	m_usedAssembly->setY(old_y);
	m_usedAssembly->setZ(old_z);
	
	m_usedAssembly->setPhi(old_phi);
	m_usedAssembly->setTheta(old_theta);
	m_usedAssembly->setRho(old_rho);
}

/**
 * sets the assembly, the transformation is done with
 * @param   GNRAssembly*    assembly, the transformation is done with

 */
void GNRCommandTransform::setAssembly(GNRAssembly* assembly)
{
	m_usedAssembly = assembly;
}

/**
 * sets the old position of the assembly, before the transformation
 * @param   GNRVertex&  old position of the assembly

 */
void GNRCommandTransform::setOldPosition(GNRVertex& old_pos)
{
	old_x = old_pos.getX();
	old_y = old_pos.getY();
	old_z = old_pos.getZ();
}

/**
 * sets the old rotations of the assembly, before the transformation
 * @param   GNRVertex&  old angles of assembly

 */
void GNRCommandTransform::setOldAngles(GNRVertex& old_angles)
{
	old_phi     = old_angles.getX();
	old_theta   = old_angles.getY();
	old_rho     = old_angles.getZ();
}

/**
 * sets the new position of the assembly, after the transformation
 * @param   GNRVertex&  new position of assembly

 */
void GNRCommandTransform::setNewPosition(GNRVertex& new_pos)
{
	new_x = new_pos.getX();
	new_y = new_pos.getY();
	new_z = new_pos.getZ();
}

/**
 * sets the new rotations of the assembly, after the transformation
 * @param   GNRVertex&  new angles of assembly

 */
void GNRCommandTransform::setNewAngles(GNRVertex& new_angles)
{
	new_phi     = new_angles.getX();
	new_theta   = new_angles.getY();
	new_rho     = new_angles.getZ();
}
